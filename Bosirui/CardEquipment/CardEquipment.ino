#include <EEPROM.h>

#include <Global.h>

#include "CardDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//UART Device
SimpleUART uart;
//Major Device
SimpleDevice* pDevice = _NULL;

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Setup.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void setup()
{
    //If analog input pin 0 is unconnected, random analog
    //noise will cause the call to randomSeed() to generate
    //different seed numbers each time the sketch runs.
    //randomSeed() will then shuffle the random function.
    randomSeed(analogRead(0));

    //Initialize serial port.
    Serial.begin(115200);
#ifdef _DEBUG
    //Print.
    _PRINT0(">CardEquipment::setup : serial was initialized !");
#endif

    //Create device.
    pCardDevice = pDevice = new CardDevice();
#ifdef _DEBUG
    _ASSERT(pDevice != _NULL);
    //Print.
    _PRINT0(">CardEquipment::setup : device was created !");
#endif
}

/**
 * Loop.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void loop()
{
    //Whether uart is ready.
    if(!uart.lineReady())
    {
        //Check device.
        if(pDevice->isIdle())
        {
/*          
#ifdef _DEBUG
            _PRINT0(">CardEquipment::loop : device is dile !");
#endif
*/
        }
        else
        {
            //Execute.
            if(!pDevice->doLoop())
            {
#ifdef _DEBUG
                _PRINT0(">CardEquipment::loop : stop device loop !");
#endif
            }
        }  
    }
    else
    {
#ifdef _DEBUG
        _PRINT1(">CardEquipment::loop : input(\"%s\") received !",uart.getString());
#endif
        //Check command.
        if(strcmp("cec",uart.getString()) == 0)
        {
            //Check device.
            if(pDevice->isIdle())
            {
                //Return result.
                _PRINT0("+cec");
                _PRINT0("OK");
            }
            else
            {
                //Cancel command.
                pDevice->cancel();
#ifdef _DEBUG
                _PRINT0(">CardEquipment::loop : cancel command !");
#endif
            }
        }
        else if(pDevice->isIdle())
        {
            //Parse command.
            if(!pDevice->parse(uart.getString()))
            {
		//Return result.
		//_PRINT1("+%s",uart.getString());
		//_PRINT0("Error");
#ifdef _DEBUG
                _PRINT0(">CardEquipment::loop : fail to parse !");
#endif
            }
	    else
	    {
#ifdef _DEBUG
                _PRINT0(">CardEquipment::loop : input was parsed !");
#endif
                //Execute.
                if(pDevice->begin())
                {
#ifdef _DEBUG
                    _PRINT0(">CardEquipment::loop : begin to executed !");
#endif
		}
	    }
        }
    }
}
