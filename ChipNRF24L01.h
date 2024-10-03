#ifndef _CHIP_NRF24L01_H
#define _CHIP_NRF24L01_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <DevicePacket.h>

////////////////////////////////////////////////////////////////////////////////
//
// Chip NRF24L01
//
////////////////////////////////////////////////////////////////////////////////

class ChipNRF24L01 : public SPIChip
{
private:
	/**
     * Chip core.
	 */
	_OBJECT chipCore;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	~ChipNRF24L01(void);

	/**
     * Default construction.
	 *
	 * @param enabledPin Chip enabled pin.
	 * @param selectedPin Chip selected pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipNRF24L01(DigitalPin enabledPin,DigitalPin selectedPin);

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
	 * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);

	/**
	 * Initialize.
	 *
	 * @param pipe Pipe.
	 * @param dataMode Whether it is a data mode.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void initialize(_UINT64 pipe,_BOOL dataMode);

public:

	/**
	 * Send device packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL sendDevicePacket(DevicePacket& packet,_UINT64 address);

	/**
	 * Receive device packet.
	 *
	 * @param packet Packet.
	 * @param address Remote address.
	 * @return
	 *     <p>Return true, if there is a valid packet.</p>
	 */
	_BOOL receiveDevicePacket(DevicePacket& packet,_UINT64& address);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !