#ifndef _NETWORK_MODULE_H
#define _NETWORK_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files.
//
////////////////////////////////////////////////////////////////////////////////

#include <Ethernet.h>
#include <EthernetUdp.h>

#include <SPIChip.h>
#include <ChipW5100.h>

#include <DevicePacket.h>

////////////////////////////////////////////////////////////////////////////////
//
// Network Module
//
////////////////////////////////////////////////////////////////////////////////

class NetworkModule
{
private:
	/**
     * Flags.
	 *
	 * <p>Flags of status.</p>
	 */
	_BYTE flags;

private:
	/**
     * Chip W5100.
	 */
	ChipW5100 chipW5100;
	/**
	 * UDP device.
	 */
	EthernetUDP udpDevice;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~NetworkModule(void);

	/**
	 * Default construction.
	 *
	 * @param chipW5100SelectPin Pin for selecting W5100 chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	NetworkModule(DigitalPin chipW5100SelectPin);

public:
	/**
	 * Whether network connected.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if network connected.</p>
	 */
	_BOOL isConnected(void);

public:
	/**
	 * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);

public:
	/**
	 * Build connection.
	 *
	 * @param macAddress MAC address.
	 * @param localAddress Local IP address.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL buildConnection(_UINT64 macAddress,IPAddress& localAddress);

	/**
	 * Receive device packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if there is a valid packet.</p>
	 */
	_BOOL receiveDevicePacket(DevicePacket& packet,IPAddress& address);

	/**
	 * Send device packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL sendDevicePacket(DevicePacket& packet,const IPAddress& address);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !