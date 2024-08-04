//
// Created by NHolt on 3/7/2024.
//

//----------------------------
//  INCLUDES
//----------------------------

#include "govee.h"

// Qt
#include <QHostAddress>
#include <QNetworkDatagram>
#include <QNetworkInterface>

// nlohmann
#include <nlohmann/json.hpp>

// std
#include <iostream>

//----------------------------
//  CONSTANTS
//----------------------------

constexpr uint16_t SCAN_PORT = 4002;

//----------------------------
//  USING DECLARATIONS
//----------------------------

using namespace nlohmann;

//======================================================================================================================
//      Member Functions
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
/// @brief
/// @param parent
//----------------------------------------------------------------------------------------------------------------------
Govee::Govee(QObject* parent)
    : QObject(parent)
    , m_socket(new QUdpSocket(this))
{
	// Retrieve the specific network interface named "Ethernet"
	auto primaryNetworkInterface = getPrimaryInterface();
	auto ipAddress = getIPv4Address(primaryNetworkInterface);

	if (!m_socket->bind(ipAddress, 4002, QUdpSocket::ShareAddress))
	{
		qWarning() << "Failed to bind socket:" << m_socket->errorString();
		return;
	}

	if (!m_socket->joinMulticastGroup(QHostAddress("239.255.255.250"), primaryNetworkInterface))
	{
		qWarning() << "Failed to join multicast group:" << m_socket->errorString();
		return;
	}

	connect(m_socket, &QUdpSocket::readyRead, this, &Govee::receiveDatagram);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
///
//----------------------------------------------------------------------------------------------------------------------
void Govee::scan()
{
	json scanMsg;
	scanMsg["msg"]["cmd"]                   = "scan";
	scanMsg["msg"]["data"]["account_topic"] = "reserve";
	std::cout << scanMsg.dump() << std::endl;

	std::string jsonString = scanMsg.dump();
	QByteArray  data(jsonString.c_str(), static_cast<int>(jsonString.length()));
	auto        bytes = m_socket->writeDatagram(data, QHostAddress("239.255.255.250"), 4001);
	std::cout << bytes << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
///
///
//----------------------------------------------------------------------------------------------------------------------
void Govee::turnOff()
{
	json turnOff;
	turnOff["msg"]["cmd"]           = "turn";
	turnOff["msg"]["data"]["value"] = 0;
	qDebug() << turnOff.dump();
	qDebug() << turnOff.dump().size();

	m_socket->writeDatagram(turnOff.dump().c_str(), turnOff.dump().size(), QHostAddress("192.168.23.23"), 4003);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
///
///
//----------------------------------------------------------------------------------------------------------------------
void Govee::turnOn()
{
	json turnOff;
	turnOff["msg"]["cmd"]           = "turn";
	turnOff["msg"]["data"]["value"] = 1;
	qDebug() << turnOff.dump();
	qDebug() << turnOff.dump().size();

	m_socket->writeDatagram(turnOff.dump().c_str(), turnOff.dump().size(), QHostAddress("192.168.23.23"), 4003);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
/// @brief
//----------------------------------------------------------------------------------------------------------------------
void Govee::receiveDatagram()
{
	while (m_socket->hasPendingDatagrams())
		std::cout << m_socket->receiveDatagram().data().toStdString() << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
///
///
//----------------------------------------------------------------------------------------------------------------------
QNetworkInterface Govee::getPrimaryInterface()
{
	QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
	QNetworkInterface        primaryInterface;

	for (const QNetworkInterface& iface : interfaces)
	{
		if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
		    iface.flags().testFlag(QNetworkInterface::IsRunning) &&
		    !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
		{

			for (const QNetworkAddressEntry& entry : iface.addressEntries())
			{
				if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
				{
					primaryInterface = iface;
					return primaryInterface;    // Return the first suitable interface found
				}
			}
		}
	}

	return primaryInterface;    // Will be invalid if no suitable interface is found
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
///
///
//----------------------------------------------------------------------------------------------------------------------
QHostAddress Govee::getIPv4Address(const QNetworkInterface& iface)
{
	for (const QNetworkAddressEntry& entry : iface.addressEntries())
	{
		if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
		{
			return entry.ip();
		}
	}
	return QHostAddress();
}