//
// Created by NHolt on 3/7/2024.
//

#ifndef GOVEE_SYNC_GOVEE_H
#define GOVEE_SYNC_GOVEE_H

//----------------------------
//  INCLUDES
//----------------------------

#include <QObject>
#include <QUdpSocket>

//----------------------------------------------------------------------------------------------------------------------
//      CLASS: Govee
//----------------------------------------------------------------------------------------------------------------------
/// @brief
//----------------------------------------------------------------------------------------------------------------------
class Govee : public QObject
{
public:
	Govee(QObject* parent = nullptr);

	//----------------------------
	//  MESSAGES
	//----------------------------

	void scan();
	void turnOff();
	void turnOn();

public slots:
	void receiveDatagram();

private:
	static QNetworkInterface getPrimaryInterface();
	static QHostAddress getIPv4Address(const QNetworkInterface &iface);

signals:

private:
	QUdpSocket* m_socket = nullptr;

};

#endif // GOVEE_SYNC_GOVEE_H