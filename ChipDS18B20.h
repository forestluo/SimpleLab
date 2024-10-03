#ifndef _CHIP_DS18B20_H
#define _CHIP_DS18B20_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip DS18B20
//
////////////////////////////////////////////////////////////////////////////////

class ChipDS18B20
{
private:
	/**
     * Chip cores.
	 */
	_OBJECT chipCores[2];
	/**
	 * Device address.
	 */
	_UINT8 deviceAddress[8];

	/**
	 * Instance of chip.
	 */
	static ChipDS18B20* instance;

public:
	/**
     * Clear.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	~ChipDS18B20();

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipDS18B20(DigitalPin pin);

public:
	/**
     * Setup.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL setup(void);

	/**
	 * Read temperature.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Temperature.</p>
	 */
	_FLOAT readTemperature(void);

public:
	/**
	 * Uninitialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void uninitialize(void);

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
	 * @param temperature Temperature.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	static _BOOL read(_FLOAT& temperature);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !