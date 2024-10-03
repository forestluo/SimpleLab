#ifndef _WIRELESS_MODULE_H
#define _WIRELESS_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <SPIChip.h>
#include <ChipNRF24L01.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Major Pipe
#define MAJOR_PIPE(p)										(((p) & 0xFFFFFFFFF0LL) | 0x01)
//Data Pipes
#define DATA_PIPE1(p)										(((p) & 0xFFFFFFFFF0LL) | 0x02)
#define DATA_PIPE2(p)										(((p) & 0xFFFFFFFFF0LL) | 0x03)
#define DATA_PIPE3(p)										(((p) & 0xFFFFFFFFF0LL) | 0x04)
#define DATA_PIPE4(p)										(((p) & 0xFFFFFFFFF0LL) | 0x05)
//Data Pipes
#define DATA_PIPE5(p)										(((p) & 0xFFFFFFFFF0LL) | 0x06)
#define DATA_PIPE6(p)										(((p) & 0xFFFFFFFFF0LL) | 0x07)
#define DATA_PIPE7(p)										(((p) & 0xFFFFFFFFF0LL) | 0x08)
#define DATA_PIPE8(p)										(((p) & 0xFFFFFFFFF0LL) | 0x09)
#define DATA_PIPE9(p)										(((p) & 0xFFFFFFFFF0LL) | 0x0A)
//Random Data Pipe
#define DATA_PIPEx(p)										(((p) & 0xFFFFFFFFF0LL) | ((random() % 4) + 2))
#define DATA_PIPEn(p)										(((p) & 0xFFFFFFFFF0LL) | ((random() % 5) + 6))

////////////////////////////////////////////////////////////////////////////////
//
// Wireless Module
//
////////////////////////////////////////////////////////////////////////////////

class WirelessModule
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
     * Chip NRF24L01.
	 *
	 * <p>Commannd channel.</p>
	 */
	ChipNRF24L01 chipA;
	/**
     * Chip NRF24L01.
	 *
	 * <p>Sample data channel.</p>
	 */
	ChipNRF24L01 chipB;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~WirelessModule(void);

	/**
	 * Default construction.
	 *
	 * @param chipNRF24L01EnabledPinA Pin for enabling NRF24L01 chip A.
	 * @param chipNRF24L01SelectedPinA Pin for selecting NRF24L01 chip A.
	 * @param chipNRF24L01EnabledPinB Pin for enabling NRF24L01 chip B.
	 * @param chipNRF24L01SelectedPinB Pin for selecting NRF24L01 chip B.
	 * @return
	 *     <p>No results returned.</p>
	 */
	WirelessModule(DigitalPin chipNRF24L01EnabledPinA,
					DigitalPin chipNRF24L01SelectedPinA,
					DigitalPin chipNRF24L01EnabledPinB,
					DigitalPin chipNRF24L01SelectedPinB);

public:
	/**
     * Power up.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void powerUp(void);

	/**
	 * Power down.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void powerDown(void);

	/**
	 * Whether wireless is connected.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if wireless is online.</p>
	 */
	_BOOL isConnected(void);

	/**
	 * Initialize.
	 *
	 * @param pipe Pipe.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void initialize(_UINT64 pipe);

public:
	/**
	 * Whether wireless is a proxy.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if wireless is a proxy.</p>
	 */
	_BOOL isProxy(void);

	/**
	 * Set proxy.
	 *
	 * @param status Status of proxy.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setProxy(_BOOL status);

public:

	/**
	 * Send command packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL sendCommandPacket(DevicePacket& packet,_UINT64 address);

	/**
	 * Receive command packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if there is a valid packet.</p>
	 */
	_BOOL receiveCommandPacket(DevicePacket& packet,_UINT64& address);

public:

	/**
	 * Send data packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL sendDataPacket(DevicePacket& packet,_UINT64 address);

	/**
	 * Receive data packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if there is a valid packet.</p>
	 */
	_BOOL receiveDataPacket(DevicePacket& packet,_UINT64& address);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !