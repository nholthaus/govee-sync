// ---------------------------------------------------------------------------------------------------------------------
//
/// @file       goveeDevice.cpp
/// @author     Nic Holthaus
/// @date       8/4/2024
//
// ---------------------------------------------------------------------------------------------------------------------
//
/// @details    Implementation file for `goveeDevice.h`.
//
// ---------------------------------------------------------------------------------------------------------------------

//----------------------------
//  INCLUDES
//----------------------------

#include "goveeDevice.h"

//======================================================================================================================
//      MEMBER FUNCTIONS
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: GoveeDevice [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      BRIEF
//----------------------------------------------------------------------------------------------------------------------
GoveeDevice::GoveeDevice() = default;
QHostAddress GoveeDevice::ipAddress() const { return m_ipAddress; }
QString      GoveeDevice::device() const { return m_device; }
QString      GoveeDevice::sku() const { return m_sku; }
QString      GoveeDevice::bleVersionHard() const { return m_bleVersionHard; }
QString      GoveeDevice::bleVersionSoft() const { return m_bleVersionSoft; }
QString      GoveeDevice::wifiVersionHard() const { return m_wifiVersionHard; }
QString      GoveeDevice::wifiVersionSoft() const { return m_wifiVersionSoft; }
bool         GoveeDevice::on() const { return m_on; }
int          GoveeDevice::brightness() const { return m_brightness; }
QColor       GoveeDevice::color() const { return m_color; }
void         GoveeDevice::setIpAddress(const QHostAddress& ipAddress) { m_ipAddress = ipAddress; }
void         GoveeDevice::setDevice(const QString& device) { m_device = device; }
void         GoveeDevice::setSku(const QString& sku) { m_sku = sku; }
void         GoveeDevice::setBleVersionHard(const QString& bleVersionHard) { m_bleVersionHard = bleVersionHard; }
void         GoveeDevice::setBleVersionSoft(const QString& bleVersionSoft) { m_bleVersionSoft = bleVersionSoft; }
void         GoveeDevice::setWifiVersionHard(const QString& wifiVersionHard) { m_wifiVersionHard = wifiVersionHard; }
void         GoveeDevice::setWifiVersionSoft(const QString& wifiVersionSoft) { m_wifiVersionSoft = wifiVersionSoft; }
void         GoveeDevice::setOn(bool on) { m_on = on; }
void         GoveeDevice::setBrightness(int brightness) { m_brightness = brightness; }
void         GoveeDevice::setColor(const QColor& color) { m_color = color; }

std::ostream& operator<<(std::ostream& os, const GoveeDevice& obj)
{
	return os
		<< "m_device: " << qPrintable(obj.m_device) << std::endl
		<< " m_ipAddress: " << qPrintable(obj.m_ipAddress.toString()) << std::endl
		<< " m_sku: " << qPrintable(obj.m_sku) << std::endl
		<< " m_bleVersionHard: " << qPrintable(obj.m_bleVersionHard) << std::endl
		<< " m_bleVersionSoft: " << qPrintable(obj.m_bleVersionSoft) << std::endl
		<< " m_wifiVersionHard: " << qPrintable(obj.m_wifiVersionHard) << std::endl
		<< " m_wifiVersionSoft: " << qPrintable(obj.m_wifiVersionSoft);
}

bool operator<(const GoveeDevice& lhs, const GoveeDevice& rhs) { return lhs.m_device < rhs.m_device; }
bool operator<=(const GoveeDevice& lhs, const GoveeDevice& rhs) { return !(rhs < lhs); }
bool operator>(const GoveeDevice& lhs, const GoveeDevice& rhs) { return rhs < lhs; }
bool operator>=(const GoveeDevice& lhs, const GoveeDevice& rhs) { return !(lhs < rhs); }