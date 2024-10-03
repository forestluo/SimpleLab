#ifndef _SPI_CHIP_H
#define _SPI_CHIP_H

////////////////////////////////////////////////////////////////////////////////
//
// SPI Chip
//
////////////////////////////////////////////////////////////////////////////////

class SPIChip
{
private:
	/**
     * Selected pin.
	 */
	DigitalPin selectedPin;

public:
	/**
     * Default construction.
	 *
	 * @param selectedPin Chip selected pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SPIChip(DigitalPin selectedPin);

public:
	/**
     * Get selected pin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Selected pin.</p>
	 */
	DigitalPin getSelectedPin(void);

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
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !