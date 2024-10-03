#ifndef _PHOTOGATE_DEVICE_H
#define _PHOTOGATE_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Photogate Device
//
////////////////////////////////////////////////////////////////////////////////

class PhotogateDevice
{
private:
	/**
     * Pin.
	 */
	static DigitalPin pin;

public:
	/**
	 * Initialize.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(DigitalPin pin);

public:
	/**
	 * Get pin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Pin of device.</p>
	 */
	static DigitalPin getPin(void);

public:
	/**
	 * Read photogate pulse.
	 *
	 * <p>Read latest pulse.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Time of latest pulse.</p>
	 */
	static _UINT32 readPulse(void);

	/**
	 * Read photogate pulses.
	 *
	 * <p>Read latest pulses.</p>
	 *
	 * @param pulses Pulses ticks.
	 * @param count Count of pulses.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void readPulses(_UINT32* pulses,_UINT8 count);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !