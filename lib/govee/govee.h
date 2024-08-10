//
// Created by NHolt on 3/7/2024.
//

#ifndef GOVEE_SYNC_GOVEE_H
#define GOVEE_SYNC_GOVEE_H

//----------------------------
//  INCLUDES
//----------------------------

#include "goveeDevice.h"

#include <QObject>
#include <QUdpSocket>
#include <nlohmann/json.hpp>

//----------------------------------------------------------------------------------------------------------------------
//      CLASS: Govee
//----------------------------------------------------------------------------------------------------------------------
/// @brief
//----------------------------------------------------------------------------------------------------------------------
class Govee : public QObject
{
public:
	explicit Govee(QObject* parent = nullptr);

	//----------------------------
	//  MESSAGES
	//----------------------------

	void scan() const;
	void turnOff() const;
	void turnOn() const;

public slots:
	void receiveDatagram();

private:
	[[nodiscard]] static QHostAddress getIPv4Address(const QNetworkInterface& iface);
	[[nodiscard]] static QString      getData(const nlohmann::json& msg, std::string_view field);

	void createSockets();
	void handleScanResponse(const nlohmann::json& msg) noexcept(false);
signals:

private:
	QList<QUdpSocket*>         m_sockets;
	QMap<QString, GoveeDevice> m_devices;
};

#endif    // GOVEE_SYNC_GOVEE_H