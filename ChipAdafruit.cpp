////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <ChipAdafruit.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define ADAFRUIT_SSD1306(o)									((Adafruit_SSD1306 *)(o))

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
ChipAdafruit::~ChipAdafruit(void)
{
	//Check result.
	if(chipCore != _NULL)
	{
		//Delete object.
		delete ADAFRUIT_SSD1306(chipCore);
		//Clear object.
		chipCore = (Adafruit_SSD1306 *)_NULL;
	}
}

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
ChipAdafruit::ChipAdafruit(DigitalPin dcPin,DigitalPin clkPin,
							DigitalPin mosiPin,DigitalPin resetPin)
{
	//Create object.
	chipCore = new Adafruit_SSD1306(mosiPin,clkPin,dcPin,resetPin,
									DigitalPin32/* csPin has no use.*/);
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Initialize.
	ADAFRUIT_SSD1306(chipCore)->begin(SSD1306_SWITCHCAPVCC);
}

/**
 * Get width.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Width of display.</p>
 */
_UINT8 ChipAdafruit::getWidth()
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Return result.
	return ADAFRUIT_SSD1306(chipCore)->width();
}

/**
 * Get height.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Height of display.</p>
 */
_UINT8 ChipAdafruit::getHeight()
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Return result.
	return ADAFRUIT_SSD1306(chipCore)->height();
}

/**
 * Initialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::initialize(void)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Initialize.
	ADAFRUIT_SSD1306(chipCore)->begin(SSD1306_SWITCHCAPVCC);
}

/**
 * Clear buffer.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::clearBuffer()
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Clear buffer.
	ADAFRUIT_SSD1306(chipCore)->clearDisplay();
}

/**
 * Display buffer.
 *
 * <p>Send the buffer data to screen.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::displayBuffer()
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Display buffer.
	ADAFRUIT_SSD1306(chipCore)->display();
}

/**
 * Set cursor.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::setCursor(_UINT8 x,_UINT8 y)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Set cursor.
	ADAFRUIT_SSD1306(chipCore)->setCursor(x,y);
}

/**
 * Draw pixel.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @param color Color of pixel.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::drawPixel(_UINT8 x,_UINT8 y,_UINT8 color)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Draw pixel.
	ADAFRUIT_SSD1306(chipCore)->drawPixel(x,y,color);
}

/**
 * Draw horizontal line.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @param width Width of line.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::drawHLine(_UINT8 x,_UINT8 y,_UINT8 width,_UINT8 color)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Draw horizontal line.
	ADAFRUIT_SSD1306(chipCore)->drawFastHLine(x,y,width,color);
}

/**
 * Draw vertical line.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @param height Height of line.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::drawVLine(_UINT8 x,_UINT8 y,_UINT8 height,_UINT8 color)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(chipCore != _NULL);
#endif
	//Draw vertical line.
	ADAFRUIT_SSD1306(chipCore)->drawFastVLine(x,y,height,color);
}

/**
 * Print
 *
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::print(const _STRING value)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(value != _NULL);
	_ASSERT(chipCore != _NULL);
#endif
	//Print.
	ADAFRUIT_SSD1306(chipCore)->print(value);
}

/**
 * Print with new line.
 *
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::println(const _STRING value)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(value != _NULL);
	_ASSERT(chipCore != _NULL);
#endif
	//Print.
	ADAFRUIT_SSD1306(chipCore)->println(value);
}

/**
 * Dump registers.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAdafruit::dumpRegisters(void)
{
	//Print.
	_PRINT0("ChipAdafruit::dumpRegisters : show registers !");
	//Print.
	_PRINT1("\twidth = %d",getWidth());
	//Print.
	_PRINT1("\theight = %d",getHeight());
}
