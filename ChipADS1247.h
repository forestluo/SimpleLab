#ifndef _CHIP_ADS1247_H
#define _CHIP_ADS1247_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip ADS1247
//
////////////////////////////////////////////////////////////////////////////////

class ChipADS1247 : public SPIChip
{
public:
	/**
     * Default construction.
	 *
	 * @param selectedPin Chip selected pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipADS1247(DigitalPin selectedPin);

public:
	/**
     * Select chip.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void selectChip(void);

	/**
     * Unselect chip.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void unselectChip(void);

public:
	/**
	 * Reset chip.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void resetChip(void);

	/**
	 * Sleep chip.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void sleepChip(void);

	/**
	 * Wakeup chip.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void wakeupChip(void);

private:
	/**
     * Read register.
	 *
	 * @param address Address of register.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 readRegister(_UINT8 address);

	/**
     * Write register.
	 *
	 * @param address Address of register.
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeRegister(_UINT8 address,_UINT8 value);

public:
	/**
     * Get MUX0.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getMUX0();

	/**
	 * Set MUX0.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMUX0(_UINT8 value);

public:
	/**
     * Get VBIAS.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getVBIAS();

	/**
	 * Set VBIAS.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setVBIAS(_UINT8 value);

public:
	/**
     * Get MUX1.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getMUX1();

	/**
	 * Set MUX1.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMUX1(_UINT8 value);

public:
	/**
     * Get SYS0.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getSYS0();

	/**
	 * Set SYS0.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSYS0(_UINT8 value);

public:
	/**
     * Get IDAC0.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getIDAC0();

	/**
	 * Set IDAC0.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setIDAC0(_UINT8 value);

public:
	/**
     * Get IDAC1.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Value of register.</p>
	 */
	_UINT8 getIDAC1();

	/**
	 * Set IDAC1.
	 *
	 * @param value Value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setIDAC1(_UINT8 value);

public:
	/**
     * Read registers.
	 *
	 * <p>MUX0 | VBIAS | MUX1 | SYS0 | IDAC0 | IDAC1</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *    <p>Value of registers.</p>
	 */
	_UINT64 readRegisters();

	/**
	 * Write registers.
	 *
	 * <p>MUX0 | VBIAS | MUX1 | SYS0 | IDAC0 | IDAC1</p>
	 *
	 * @param value Value of registers.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeRegisters(_UINT64 value);

public:
	/**
     * Read AVDD value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>AVDD value.</p>
	 */
	_FLOAT readAVDD(void);

	/**
	 * Read A/D value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Value of A/D result.</p>
	 */
	_UINT32 readValue(void);

	/**
	 * Dump regsiters.
	 *
	 * <p>Dump registers.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpRegisters(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !