#ifndef _CHIP_DHT_H
#define _CHIP_DHT_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip DHT
//
////////////////////////////////////////////////////////////////////////////////

class ChipDHT
{
private:
	/**
     * Read byte.
	 *
	 * @param pin Data pin.
	 * @return
	 *     <p>Byte value.</p>
	 */
	static _BYTE readByte(DigitalPin pin);

public:
	/**
     * Initialize.
	 *
	 * @param pin Data pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(DigitalPin pin);

	/**
	 * Read.
	 *
	 * @param pin Data pin.
	 * @param temperature Temperature.
	 * @param humidity Humidity.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	static _BOOL read(DigitalPin pin,_FLOAT& temperature,_FLOAT& humidity);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !