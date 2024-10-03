#ifndef _PACKET_BODY_H
#define _PACKET_BODY_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Device status.
 */
typedef struct tagDeviceStatus
{
	/**
	 * Type of device.
	 */
	_UINT32 deviceType;
	/**
	 * Flags of device.
	 *
	 * <p>Mainly used for master or slave.</p>
	 */
	_UINT8 deviceFlags;
	/**
	 * Status of device.
	 *
	 * <p>Mainly used for busy or idle.</p>
	 */
	_UINT8 deviceStatus;
	/**
	 * MAC address.
	 *
	 * <p>Machine physical address.</p>
	 */
	_BYTE macAddress[6];
	/**
	 * IP address.
	 *
	 * <p>IP v4 address only.</p>
	 */
	_BYTE ipv4Address[4];
	/**
	 * Current sample rate.
	 *
	 * <p>Sample rate.</p>
	 */
	_SHORT sampleRate;

} DeviceStatus;

/**
 * Device control.
 */
typedef struct tagDeviceControl
{
	/**
	 * The rate of sample.
	 *
	 * <p>It is 32bit precision.
	 * When it is positive, it means times/second.
	 * When it is negtive, it means seconds/time.
	 * When it is zero, it means no sample action.</p>
	 */
	_SHORT sampleRate;

} DeviceControl;

/**
 * Device release.
 */
typedef struct tagDeviceRelease
{
	/**
	 * The rate of sample.
	 *
	 * <p>It is 32bit precision.
	 * When it is positive, it means times/second.
	 * When it is negtive, it means seconds/time.
	 * When it is zero, it means no sample action.</p>
	 */
	_SHORT sampleRate;

} DeviceRelease;

/**
 * Device read data.
 */
typedef struct tagDeviceReadData
{
	/**
	 * Device value.
	 */
	DeviceValue deviceValue;

} DeviceReadData;

/**
 * Device write data.
 */
typedef struct tagDeviceWriteData
{
	/**
	 * Device value.
	 */
	DeviceValue deviceValue;

} DeviceWriteData;

/**
 * Device read storage.
 */
typedef struct tagDeviceReadStorage
{
	/**
	 * Offset of data.
	 */
	_UINT32 offset;
	/**
	 * Value of data.
	 */
	GeneralValue generalValue;

} DeviceReadStorage;

/**
 * Device write storage.
 */
typedef struct tagDeviceWriteStorage
{
	/**
	 * Offset of data.
	 */
	_UINT32 offset;
	/**
	 * Value of data.
	 */
	GeneralValue generalValue;

} DeviceWriteStorage;

/**
 * Device wireless packet.
 */
typedef struct tagDeviceWirelessPacket
{
	/**
	 * Wireless address.
	 */
	_UINT8 wirelessAddress[6];

} DeviceWirelessPacket;

/**
 * Device wireless status.
 */
typedef struct tagDeviceWirelessStatus : 
	public tagDeviceWirelessPacket
{
	/**
	 * Type of device.
	 */
	_UINT32 deviceType;
	/**
	 * Flags of device.
	 *
	 * <p>Mainly used for master or slave.</p>
	 */
	_UINT8 deviceFlags;
	/**
	 * Status of device.
	 *
	 * <p>Mainly used for busy or idle.</p>
	 */
	_UINT8 deviceStatus;
	/**
	 * Machine address.
	 *
	 * <p>Machine address.</p>
	 */
	_BYTE macAddress[6];
	/**
	 * Current sample rate.
	 *
	 * <p>Sample rate.</p>
	 */
	_SHORT sampleRate;

} DeviceWirelessStatus;

/**
 * Device wireless control.
 */
typedef struct tagDeviceWirelessControl : 
	public tagDeviceWirelessPacket
{
	/**
	 * The rate of sample.
	 *
	 * <p>It is 32bit precision.
	 * When it is positive, it means times/second.
	 * When it is negtive, it means seconds/time.
	 * When it is zero, it means no sample action.</p>
	 */
	_SHORT sampleRate;
	/**
	 * Channel.
	 *
	 * <p>Data channel.</p>
	 */
	_UINT8 channel;

} DeviceWirelessControl;

/**
 * Device wireless release.
 */
typedef struct tagDeviceWirelessRelease : 
	public tagDeviceWirelessPacket
{
	/**
	 * The rate of sample.
	 *
	 * <p>It is 32bit precision.
	 * When it is positive, it means times/second.
	 * When it is negtive, it means seconds/time.
	 * When it is zero, it means no sample action.</p>
	 */
	_SHORT sampleRate;
	/**
	 * Channel.
	 *
	 * <p>Data channel.</p>
	 */
	_UINT8 channel;

} DeviceWirelessRelease;

/**
 * Device wireless read data.
 */
typedef struct tagDeviceWirelessReadData :
	public tagDeviceWirelessPacket
{
	/**
	 * Flags.
	 */
	_UINT8 flags;
	/**
	 * Sample value.
	 */
	SampleValue sampleValue;
	
} DeviceWirelessReadData;

/**
 * Device wireless write data.
 */
typedef struct tagDeviceWirelessWriteData :
	public tagDeviceWirelessPacket
{
	/**
	 * Flags.
	 */
	_UINT8 flags;
	/**
	 * Sample value.
	 */
	SampleValue sampleValue;
	
} DeviceWirelessWriteData;

/**
 * Packet body.
 */
typedef union tagPacketBody
{
	/**
	 * Device status.
	 */
	DeviceStatus			ds;

	/**
	 * Device control.
	 */
	DeviceControl			dc;
	/**
	 * Device release.
	 */
	DeviceRelease			dr;

	/**
	 * Device read data.
	 */
	DeviceReadData			drd;
	/**
	 * Device write data.
	 */
	DeviceWriteData			dwd;

	/**
	 * Device read storage.
	 */
	DeviceReadStorage		drs;
	/**
	 * Device write storage.
	 */
	DeviceWriteStorage		dws;

	/**
	 * Device wireless packet.
	 */
	DeviceWirelessPacket    dwp;
	/**
	 * Device wireless status.
	 */
	DeviceWirelessStatus	dwps;
	/**
	 * Device wireless control.
	 */
	DeviceWirelessControl	dwpc;
	/**
	 * Device wireless release.
	 */
	DeviceWirelessRelease	dwpr;
	/**
	 * Device wireless read data.
	 */
	DeviceWirelessReadData	dwprd;
	/**
	 * Device wireless write data.
	 */
	DeviceWirelessWriteData	dwpwd;

} PacketBody;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
