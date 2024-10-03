#ifndef _DEVICE_PACKET_H
#define _DEVICE_PACKET_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#include <PacketBody.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Device packet.
 */
struct DevicePacket
{
public:
	/**
     * Commands.
	 */
	static const _UINT8 DEVICE_STATUS;
	static const _UINT8 DEVICE_CONTROL;
	static const _UINT8 DEVICE_RELEASE;
	static const _UINT8 DEVICE_READ_DATA;
	static const _UINT8 DEVICE_WRITE_DATA;
	static const _UINT8 DEVICE_READ_STORAGE;
	static const _UINT8 DEVICE_WRITE_STORAGE;
	static const _UINT8 DEVICE_WIRELESS_STATUS;
	static const _UINT8 DEVICE_WIRELESS_CONTROL;
	static const _UINT8 DEVICE_WIRELESS_RELEASE;
	static const _UINT8 DEVICE_WIRELESS_READ_DATA;
	static const _UINT8 DEVICE_WIRELESS_WRITE_DATA;

public:
	/**
	 * Total length.
	 *
	 * <p>It is 16bit.
	 * The total length is not more than 256 bytes.</p>
	 */
	_UINT16 totalLength;
	/**
	 * Command.
	 */
	_UINT8 command;
	/**
	 * Version.
	 * 
	 * <p>Version of protocol.</p>
	 */
	_UINT8 version;
	/**
	 * Checksum16.
	 *
	 * <p>When calculated it is filled with 0.</p>
	 */
	_UINT16 checksum16;

	/**
	 * Packet body.
	 */
	PacketBody body;


public:
	/**
	 * Get wireless address.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Wireless address.</p>
	 */
	_UINT64 getWirelessAddress(void);

	/**
     * Set wireless address.
	 *
	 * @param address Address.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setWirelessAddress(_UINT64 address);

public:
	/**
     * Make packet.
	 *
	 * <p>Make packet before transmission.</p>
	 *
	 * @param packet Device packet.
	 * @return
	 *     <p>Size of packet.</p>
	 */
	static _UINT16 makePacket(DevicePacket& packet);

	/**
     * Clear packet.
	 *
	 * @param packet Packet for clear.
	 * @param command Command of packet.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void clearPacket(DevicePacket& packet,_UINT8 command);

	/**
	 * Verify packet.
	 *
	 * <p>Verify the received packet.</p>
	 *
	 * @param packet Packet for verify.
	 * @param packetSize Size of packet.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	static _BOOL verifyPacket(DevicePacket& packet,_UINT16 packetSize);

public:
	/**
     * Dump samples.
	 *
	 * @param None No parameters needed.
	 * @return
	 *      <p>No results returned.</p>
	 */
	static void dumpSamples(void);

	/**
	 * Dump packet.
	 *
	 * @param packet Packet.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void dumpPacket(const DevicePacket& packet);

	/**
	 * Dump buffer.
	 *
	 * @param packet Packet.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void dumpBuffer(const DevicePacket& packet);
	
	/**
	 * Dump buffer.
	 *
	 * @param packet Packet.
	 * @param length Length of buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void dumpBuffer(const DevicePacket& packet,_UINT16 length);
};

/**
 * Size of packet.
 */
#define DEVICE_PACKET_HEADER_SIZE							(sizeof(DevicePacket) - sizeof(PacketBody))
#define DEVICE_STATUS_PACKET_SIZE							(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceStatus))
#define DEVICE_CONTROL_PACKET_SIZE							(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceControl))
#define DEVICE_RELEASE_PACKET_SIZE							(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceRelease))
#define DEVICE_READ_DATA_PACKET_SIZE(n)						(DEVICE_PACKET_HEADER_SIZE + sizeof(_BYTE) + ((_UINT16)(n)) * sizeof(SampleValue))
#define DEVICE_WRITE_DATA_PACKET_SIZE(n)					(DEVICE_PACKET_HEADER_SIZE + sizeof(_BYTE) + ((_UINT16)(n)) * sizeof(SampleValue))
#define DEVICE_READ_STORAGE_PACKET_SIZE						(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceReadStorage))
#define DEVICE_WRITE_STORAGE_PACKET_SIZE					(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWriteStorage))
#define DEVICE_READ_STORAGE_PACKET_LEFT_SIZE				(sizeof(DevicePacket) - DEVICE_READ_STORAGE_PACKET_SIZE)
#define DEVICE_WRITE_STORAGE_PACKET_LEFT_SIZE				(sizeof(DevicePacket) - DEVICE_WRITE_STORAGE_PACKET_SIZE)
#define DEVICE_WIRELESS_STATUS_PACKET_SIZE					(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWirelessStatus))
#define DEVICE_WIRELESS_CONTROL_PACKET_SIZE					(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWirelessControl))
#define DEVICE_WIRELESS_RELEASE_PACKET_SIZE					(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWirelessRelease))
#define DEVICE_WIRELESS_READ_DATA_PACKET_SIZE				(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWirelessReadData))
#define DEVICE_WIRELESS_WRITE_DATA_PACKET_SIZE				(DEVICE_PACKET_HEADER_SIZE + sizeof(DeviceWirelessWriteData))

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
