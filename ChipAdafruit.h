#ifndef _CHIP_ADAFRUIT_H
#define _CHIP_ADAFRUIT_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip Adafruit
//
////////////////////////////////////////////////////////////////////////////////

class ChipAdafruit
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
	~ChipAdafruit(void);

	/**
     * Default construction.
	 *
	 * @param dcPin DC pin.
	 * @param clkPin CLK pin.
	 * @param mosiPin MOSI pin.
	 * @param resetPin RESET pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipAdafruit(DigitalPin dcPin,DigitalPin clkPin,
					DigitalPin mosiPin,DigitalPin resetPin);

public:
	/**
	 * Get width.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Width of display.</p>
	 */
	_UINT8 getWidth();

	/**
	 * Get height.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Height of display.</p>
	 */
	_UINT8 getHeight();

public:
	/**
     * Initialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void initialize(void);

	/**
	 * Clear buffer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearBuffer(void);

	/**
	 * Display buffer.
	 *
	 * <p>Send the buffer data to screen.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayBuffer(void);

	/**
     * Set cursor.
	 *
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setCursor(_UINT8 x,_UINT8 y);

public:
	/**
	 * Draw pixel.
	 *
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @param color Color of pixel.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void drawPixel(_UINT8 x,_UINT8 y,_UINT8 color);

	/**
	 * Draw horizontal line.
	 *
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @param width Width of line.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void drawHLine(_UINT8 x,_UINT8 y,_UINT8 width,_UINT8 color);

	/**
	 * Draw vertical line.
	 *
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @param height Height of line.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void drawVLine(_UINT8 x,_UINT8 y,_UINT8 height,_UINT8 color);

public:
	/**
	 * Print
	 *
	 * @param string String.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void print(const _STRING value);

	/**
	 * Print with new line.
	 *
	 * @param string String.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void println(const _STRING value);

public:
	/**
	 * Dump registers.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpRegisters(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !