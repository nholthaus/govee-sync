// ---------------------------------------------------------------------------------------------------------------------
//
/// @file       goveeDevice.h
/// @author     Nic Holthaus
/// @date       8/4/2024
/// @copyright
//
// ---------------------------------------------------------------------------------------------------------------------
//
/// @brief      Definition of the `GoveeDevice` Class.
/// @details    
//
// ---------------------------------------------------------------------------------------------------------------------

#ifndef GOVEEDEVICE_H
#define GOVEEDEVICE_H

//----------------------------
//  INCLUDES
//----------------------------

#include <QHostAddress>
#include <QColor>
#include <ostream>

//----------------------------------------------------------------------------------------------------------------------
//      CLASS: GoveeDevice 
//----------------------------------------------------------------------------------------------------------------------
/// @brief 
//----------------------------------------------------------------------------------------------------------------------
class GoveeDevice 
{
public:

	//----------------------------
	//  CONSTRUCTORS
	//----------------------------

	GoveeDevice();

	//----------------------------
	//  GETTERS
	//----------------------------

	[[nodiscard]] QHostAddress ipAddress() const;
	[[nodiscard]] QString      device() const;
	[[nodiscard]] QString      sku() const;
	[[nodiscard]] QString      bleVersionHard() const;
	[[nodiscard]] QString      bleVersionSoft() const;
	[[nodiscard]] QString      wifiVersionHard() const;
	[[nodiscard]] QString      wifiVersionSoft() const;
	[[nodiscard]] bool         on() const;
	[[nodiscard]] int          brightness() const;
	[[nodiscard]] QColor       color() const;

	//----------------------------
	//  SETTERS
	//----------------------------

	void setIpAddress(const QHostAddress& ipAddress);
	void setDevice(const QString& device);
	void setSku(const QString& sku);
	void setBleVersionHard(const QString& bleVersionHard);
	void setBleVersionSoft(const QString& bleVersionSoft);
	void setWifiVersionHard(const QString& wifiVersionHard);
	void setWifiVersionSoft(const QString& wifiVersionSoft);
	void setOn(bool on);
	void setBrightness(int brightness);
	void setColor(const QColor& color);

	friend std::ostream& operator<<(std::ostream& os, const GoveeDevice& obj);

	//----------------------------
	//  OPERATORS
	//----------------------------

	friend bool operator<(const GoveeDevice& lhs, const GoveeDevice& rhs);
	friend bool operator<=(const GoveeDevice& lhs, const GoveeDevice& rhs);
	friend bool operator>(const GoveeDevice& lhs, const GoveeDevice& rhs);
	friend bool operator>=(const GoveeDevice& lhs, const GoveeDevice& rhs);

public:

	QHostAddress m_ipAddress;
	QString m_device;
	QString m_sku;
	QString m_bleVersionHard;
	QString m_bleVersionSoft;
	QString m_wifiVersionHard;
	QString m_wifiVersionSoft;
	bool m_on = false;
	int m_brightness = 100;
	QColor m_color;

};

#endif //GOVEEDEVICE_H