////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <DisplayModule.h>

#include <HZK16File.h>
#include <SimpleString.h>

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
DisplayModule::~DisplayModule(void)
{

}

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
DisplayModule::DisplayModule(DigitalPin chipAdafruitDCPin,
							 DigitalPin chipAdafruitCLKPin,
				  			 DigitalPin chipAdafruitMOSIPin,
							 DigitalPin chipAdafruitRESETPin)
	: chipAdafruit(chipAdafruitDCPin,chipAdafruitCLKPin,
				  chipAdafruitMOSIPin,chipAdafruitRESETPin)
{
#ifdef _DEBUG_DISPLAY_MODULE   
    //Print.
    _PRINT0("DisplayModule::DisplayModule : display was initialized !");
#endif
	//Display title.
	{
		//Buffer.
		_CHAR buffer[32];
		//Format buffer.
		_FORMAT0(buffer,"www.4DClass.com");
		//Set cursor.
		chipAdafruit.setCursor(21,48);
		//Print buffer.
		chipAdafruit.println(buffer);
	}
	//Display logo.
    //The logo exits in buffer.
    chipAdafruit.displayBuffer();
#ifdef _DEBUG_DISPLAY_MODULE
    //Print.
    _PRINT0("DisplayModule::DisplayModule : manufacture LOGO was displayed !");
#endif
}

/**
 * Initialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::initialize(void)
{
	//Initialize.
	chipAdafruit.initialize();
}

/**
 * Clear buffer.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::clearBuffer()
{
	//Clear buffer.
	chipAdafruit.clearBuffer();
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
void DisplayModule::displayBuffer()
{
	//Display buffer.
	chipAdafruit.displayBuffer();
}

/**
 * Set cursor.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::setCursor(_UINT8 x,_UINT8 y)
{
	//Set cursor.
	chipAdafruit.setCursor(x,y);
}

/**
 * Print
 *
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::print(const _STRING value)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(value != _NULL);
#endif
	//Print.
	chipAdafruit.print(value);
}

/**
 * Print with new line.
 *
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::println(const _STRING value)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(value != _NULL);
#endif
	//Print.
	chipAdafruit.println(value);
}

/**
 * Display header.
 *
 * @param network Whether network connected.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::displayHeader(_BOOL network)
{
	//Display title.
	{
		//Buffer.
		_CHAR buffer[32];
		//Format buffer.
		_FORMAT0(buffer,"4DClass-Lab");
		//Set cursor.
		chipAdafruit.setCursor(0,0);
		//Print buffer.
		chipAdafruit.println(buffer);
	}
	//Draw signal.
	if(network)
	{
		//Draw line.
		chipAdafruit.drawVLine(100,5,3,1);//White
		//Draw line.
		chipAdafruit.drawVLine(102,4,4,1);//White
		//Draw line.
		chipAdafruit.drawVLine(104,3,5,1);//White
		//Draw line.
		chipAdafruit.drawVLine(106,2,6,1);//White
		//Draw line.
		chipAdafruit.drawVLine(108,1,7,1);//White
	}
	else
	{
		//Draw cross.
		for(_UINT8 i = 0;i < 7;i ++)
		{
			//Draw pixel.
			chipAdafruit.drawPixel(101 + i,1 + i,1);//White
			//Draw pixel.
			chipAdafruit.drawPixel(107 - i,1 + i,1);//White
		}
	}

	//Draw battery.
	{
		//Draw line.
		chipAdafruit.drawVLine(114,3,3,1);//White
		//Draw line.
		chipAdafruit.drawHLine(115,1,12,1);//White
		//Draw line.
		chipAdafruit.drawHLine(115,7,12,1);//White
		//Draw line.
		chipAdafruit.drawVLine(115,1,7,1);//White
		//Draw line.
		chipAdafruit.drawVLine(126,1,7,1);//White

		//Draw line.
		chipAdafruit.drawHLine(117,3,8,1);//White
		//Draw line.
		chipAdafruit.drawHLine(117,4,8,1);//White
		//Draw line.
		chipAdafruit.drawHLine(117,5,8,1);//White
	}

	//Draw horizontal line.
	chipAdafruit.drawHLine(0,9,128,1);//White
}

/**
 * Draw HZK bitmap.
 *
 * @param x X coordination.
 * @param y Y coordination.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::drawHZKBitmap(_UINT8 x,_UINT8 y,_HZKBITMAP bitmap,_UINT8 color)
{
	//Do while.
	for(_UINT8 i = 0;i < 16;i ++)
	{
		for(_UINT8 j = 0;j < 2;j ++)
		{
			for(_UINT8 k = 0;k < 8;k ++)
			{
				//Check result.
				if(bitmap[i * 2 + j] & (0x80 >> k))
				{
					//Draw pixel.
					chipAdafruit.drawPixel(x + j * 8 + k,y + i,color);
				}
			}
		}
	}
}

/**
 * Display string.
 *
 * @param fileModule File module.
 * @param x X coordination.
 * @param y Y coordination.
 * @param string String in row.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::displayString(FileModule& fileModule,_UINT8 x,_UINT8 y,const _STRING string)
{
#ifdef _DEBUG_DISPLAY_MODULE
	_ASSERT(string != _NULL /*&& SimpleString::getLength(string) <= 16*/);
#endif
	//Check existance.
	if(fileModule.fileExists())
	{
		//Bitmaps.
		_HZKBITMAP bitmaps[8];
		//Clear it.
		memset(bitmaps,0,8 * sizeof(_HZKBITMAP));
		//Load bitmaps.
		HZK16File::loadHZKBitmaps(fileModule,string,bitmaps);
		//Do while.
		for(_UINT8 i = 0;i < 8 && i < strlen(string) / 2;i ++)
		{
			//Draw hzk bitmap.
			drawHZKBitmap(x + i * 16,y,bitmaps[i],1);//White.
		}
	}
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DisplayModule::dumpConfig(void)
{
	//Dump registers.
	chipAdafruit.dumpRegisters();
}
