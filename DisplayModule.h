#ifndef _DISPLAY_MODULE_H
#define _DISPLAY_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files.
//
////////////////////////////////////////////////////////////////////////////////

#include <FileModule.h>

#include <ChipAdafruit.h>

////////////////////////////////////////////////////////////////////////////////
//
// Display Module
//
////////////////////////////////////////////////////////////////////////////////

class DisplayModule
{
private:
	/**
     * Chip Adafruit.
	 */
	ChipAdafruit chipAdafruit;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~DisplayModule(void);

	/**
	 * Default construction.
	 *
	 * @param chipAdafruitDCPin DC pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitCLKPin CLK pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitMOSIPin MOSI pin for Adafruit SSD1306 chip.
	 * @param chipAdafruitRESETPin RESET pin for Adafruit SSD1306 chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DisplayModule(DigitalPin chipAdafruitDCPin,
				  DigitalPin chipAdafruitCLKPin,
				  DigitalPin chipAdafruitMOSIPin,
				  DigitalPin chipAdafruitRESETPin);

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
     * Display header.
	 *
	 * @param network Whether network connected.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayHeader(_BOOL network);

	/**
	 * Draw HZK bitmap.
	 *
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @param color Color of bitmap.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void drawHZKBitmap(_UINT8 x,_UINT8 y,_HZKBITMAP bitmap,_UINT8 color);

	/**
	 * Display string.
	 *
	 * @param fileModule File module.
	 * @param x X coordination.
	 * @param y Y coordination.
	 * @param string String in first row.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void displayString(FileModule& fileModule,_UINT8 x,_UINT8 y,const _STRING string);

public:
	/**
	 * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !