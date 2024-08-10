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
//      FUNCTION: Govee [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Constructor
/// @param[in]  parent Qt parent object.
//----------------------------------------------------------------------------------------------------------------------
Govee::Govee(QObject* parent)
    : QObject(parent)
{
	createSockets();
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: scan [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Scan all the network interfaces for Govee devices.
//----------------------------------------------------------------------------------------------------------------------
void Govee::scan() const
{
	json scanMsg;
	scanMsg["msg"]["cmd"]                   = "scan";
	scanMsg["msg"]["data"]["account_topic"] = "reserve";
	std::cout << scanMsg.dump() << std::endl;

	for (auto* socket : m_sockets)
	{
		std::cout << "scanning: " << socket->objectName().toStdString() << std::endl;
		std::string jsonString = scanMsg.dump();
		QByteArray  data(jsonString.c_str(), static_cast<int>(jsonString.length()));
		socket->writeDatagram(data, QHostAddress("239.255.255.250"), 4001);
	}
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: turnOff [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      turn off the device
//----------------------------------------------------------------------------------------------------------------------
void Govee::turnOff() const
{
	json turnOff;
	turnOff["msg"]["cmd"]           = "turn";
	turnOff["msg"]["data"]["value"] = 0;
	qDebug() << turnOff.dump();
	qDebug() << turnOff.dump().size();

	m_sockets[0]->writeDatagram(turnOff.dump().c_str(), static_cast<qint64>(turnOff.dump().size()), QHostAddress("192.168.23.23"), 4003);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: turnOn [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      turn on the device
//----------------------------------------------------------------------------------------------------------------------
void Govee::turnOn() const
{
	json turnOff;
	turnOff["msg"]["cmd"]           = "turn";
	turnOff["msg"]["data"]["value"] = 1;
	qDebug() << turnOff.dump();
	qDebug() << turnOff.dump().size();

	m_sockets[0]->writeDatagram(turnOff.dump().c_str(), static_cast<qint64>(turnOff.dump().size()), QHostAddress("192.168.23.23"), 4003);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: getData [private]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Extract data from Govee JSON message
/// @param[in]  msg json message response
/// @param[in]  field string name of the field to extract
/// @return     value of the field as a QString.
//----------------------------------------------------------------------------------------------------------------------
QString Govee::getData(const nlohmann::json& msg, std::string_view field)
{
	return QString(to_string(msg["msg"]["data"].at(field)).data()).remove("\"");
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: handleScanResponse [private]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Handle scan-response message
/// @param[in]  msg message to handle
//----------------------------------------------------------------------------------------------------------------------
void Govee::handleScanResponse(const nlohmann::json& msg) noexcept(false)
{
	if (msg["msg"]["cmd"] == "scan")
	{
		QString deviceName = getData(msg, "device");

		if (!m_devices.contains(deviceName))
		{
			GoveeDevice device;
			device.setDevice(deviceName);
			device.setSku(getData(msg, "sku"));
			device.setIpAddress(QHostAddress(getData(msg, "ip")));
			device.setBleVersionHard(getData(msg, "bleVersionHard"));
			device.setBleVersionSoft(getData(msg, "bleVersionSoft"));
			device.setWifiVersionHard(getData(msg, "wifiVersionHard"));
			device.setWifiVersionSoft(getData(msg, "wifiVersionSoft"));

			std::cout << device << std::endl;
			m_devices[deviceName] = device;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION:  []
//----------------------------------------------------------------------------------------------------------------------
/// @brief
//----------------------------------------------------------------------------------------------------------------------
void Govee::receiveDatagram()
{
	for (auto* socket : m_sockets)
	{
		while (socket->hasPendingDatagrams())
		{
			QByteArray     data = socket->receiveDatagram().data();
			nlohmann::json msg  = nlohmann::json::parse(data);
			std::cout << socket->objectName().toStdString() << ": " << msg.dump() << std::endl;

			if (msg.contains("msg") && msg["msg"].contains("cmd"))
			{
				handleScanResponse(msg);
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: createSockets [private]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Query all the network interfaces to find Govee devices.
//----------------------------------------------------------------------------------------------------------------------
void Govee::createSockets()
{
	QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

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

					auto ipAddress = getIPv4Address(iface);
					std::cout << "Interface: " << iface.humanReadableName().toStdString() << std::endl;
					auto* socket = new QUdpSocket(this);

					if (!socket->bind(ipAddress, 4002, QUdpSocket::ShareAddress))
					{
						return;
					}

					if (!socket->joinMulticastGroup(QHostAddress("239.255.255.250"), iface))
					{
						return;
					}

					connect(socket, &QUdpSocket::readyRead, this, &Govee::receiveDatagram);

					socket->setObjectName(iface.humanReadableName());
					m_sockets.push_back(socket);
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: getIPv4Address [private]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Get host address of a network interface
/// @param[in]  iface network interface to query
/// @return     IPv4 address associtated with the network interface
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
	return {};
}