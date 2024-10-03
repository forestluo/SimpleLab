#ifndef _SIMPLE_DEVICE_H
#define _SIMPLE_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <SampleTable.h>

#include <RealDevice.h>
#include <DataModule.h>
#include <FileModule.h>
#include <ConfigModule.h>
#include <DisplayModule.h>
#include <NetworkModule.h>
#include <WirelessModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// Simple Device
//
////////////////////////////////////////////////////////////////////////////////

class SimpleDevice
{
private:
	/**
     * Flags.
	 *
	 * <p>Flags of status.</p>
	 */
	_BYTE flags;
	/**
     * Real device.
	 */
	RealDevice device;

private:
	/**
     * Mac address.
	 */
	_UINT64 macAddress;
	/**
	 * Master address.
	 */
	_UINT64 masterAddress;
	/**
	 * Local address.
	 */
	IPAddress localAddress;

private:
	/**
     * Data module.
	 */
	DataModule dataModule;
	/**
	 * File module.
	 */
	FileModule fileModule;
	/**
	 * Config module.
	 */
	ConfigModule configModule;
	/**
	 * Display module.
	 */
	DisplayModule displayModule;
	/**
	 * Network module.
	 */
	NetworkModule networkModule;
	/**
	 * Wireless module.
	 */
	WirelessModule wirelessModule;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~SimpleDevice(void);

	/**
     * Default construction.
	 *
	 * @param chipAT24C128NAddress Address for AT24C128N chip.
	 * @param chipW5100SelectPin Pin for selecting W5100 chip.
	 * @param chipADS1247SelectPin Pin for selecting ADS1247 chip.
	 * @param chipAT45DB161DSelectPin Pin for selecting AT45DB161D chip.
	 * @param chipNRF24L01EnablePinA Pin for enabling NRF24L01 chip A.
	 * @param chipNRF24L01SelectePinA Pin for selecting NRF24L01 chip A.
	 * @param chipNRF24L01EnablePinB Pin for enabling NRF24L01 chip B.
	 * @param chipNRF24L01SelectePinB Pin for selecting NRF24L01 chip B.
	 * @param chipAdafruitDCPin DC pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitCLKPin CLK pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitMOSIPin MOSI pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitRESETPin RESET pin for Adafruit SSD1306 chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleDevice(_UINT8 chipAT24C128NAddress,
				 DigitalPin chipW5100SelectPin,
				 DigitalPin chipADS1247SelectPin,
				 DigitalPin chipAT45DB161DSelectPin,
				 DigitalPin chipNRF24L01EnablePinA,
				 DigitalPin chipNRF24L01SelectPinA,
				 DigitalPin chipNRF24L01EnablePinB,
				 DigitalPin chipNRF24L01SelectPinB,
				 DigitalPin chipAdafruitDCPin,
				 DigitalPin chipAdafruitCLKPin,
				 DigitalPin chipAdafruitMOSIPin,
				 DigitalPin chipAdafruitRESETPin);

protected:
	/**
     * Whether network is engaged.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if network is engaged.</p>
	 */
	_BOOL isEngaged(void);

	/**
	 * Set engaged.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setEngaged(void);

	/**
	 * Clear engaged.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearEngaged(void);

	/**
	 * Whether show console.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if showing console.</p>
	 */
	_BOOL showConsole(void);

	/**
	 * Whether show background.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if showing background.</p>
	 */
	_BOOL showBackground(void);

	/**
	 * Whether show information.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if showing information.</p>
	 */
	_BOOL showInformation(void);

protected:
	/**
	 * Get local address.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Local address.</p>
	 */
	IPAddress getLocalAddress(void);

	/**
	 * Whether local address is valid.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if local address is valid.</p>
	 */
	_BOOL isValidLocalAddress(void);

protected:
	/**
     * Clear master address.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearMasterAddress(void);

	/**
	 * Get remote address.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Remote address.</p>
	 */
	IPAddress getRemoteAddress(void);

	/**
     * Whether remote is master.
	 *
	 * @param remoteAddress Address of remote.
	 * @return
	 *     <p>Return true, if remote is mater.</p>
	 */
	_BOOL isMasterAddress(const IPAddress& remoteAddress);

	/**
     * Set master address.
	 *
	 * @param remoteAddress Address of remote.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMasterAddress(const IPAddress& remoteAddress);

public:
	/**
     * Do loop.
	 *
	 * @param None No paramters needed.
	 * @return
	 *     <p>No results return.</p>
	 */
	void doLoop(void);

private:
	/**
     * Do config action.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void doConfigAction(void);

	/**
	 * Do network key action.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void doNetworkKeyAction(void);

	/**
     * Do information key action.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void doInformationKeyAction(void);

public:
	/**
	 * Check HZK.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void checkHZK(void);

	/**
     * Dump device.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpDevice(void);

private:
	/**
     * Display main.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayMain(void);

	/**
	 * Display value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayValue(void);

	/**
	 * Display engaged.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayEngaged(void);

	/**
	 * Display console.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayConsole(void);

	/**
	 * Display no config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayNoConfig(void);

	/**
	 * Display background.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayBackground(void);

	/**
	 * Display information.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayInformation(void);

	/**
	 * Display sample result.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displaySampleResult(void);

private:
	/**
	 * Fill device status.
	 *
	 * @param packet Device packet.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void fillDeviceStatus(DevicePacket& packet);

	/**
	 * Fill device wireless status.
	 *
	 * @param packet Device packet.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void fillDeviceWirelessStatus(DevicePacket& packet);

	/**
     * Do receive.
	 *
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL doReceive(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * Do receive.
	 *
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL doReceive(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device status.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceStatus(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device control.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceControl(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device release.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceRelease(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device read data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceReadData(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device write data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWriteData(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device read storage.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceReadStorage(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device write storage.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWriteStorage(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device wireless status.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessStatus(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * On device wireless status.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessStatus(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device wireless control.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessControl(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * On device wireless control.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessControl(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device wireless release.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessRelease(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * On device wireless release.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessRelease(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device wireless read data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessReadData(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * On device wireless read data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessReadData(DevicePacket& packet,const IPAddress& remoteAddress);

	/**
     * On device wireless write data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessWriteData(DevicePacket& packet,const _UINT64 remoteAddress);

	/**
     * On device wireless write data.
	 * 
	 * @param packet Device packet.
	 * @param remoteAddress Remote address.
	 * @return
	 *     <p>Return true, if there is a return packet.</p>
	 */
	_BOOL onDeviceWirelessWriteData(DevicePacket& packet,const IPAddress& remoteAddress);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !