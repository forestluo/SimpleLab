////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleLED.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Open led.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleLED::open(DigitalPin pin)
{
	//Write low.
	digitalWrite(pin,LOW); 
}

/**
 * Close led.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleLED::close(DigitalPin pin)
{
	//Write high.
	digitalWrite(pin,HIGH); 
}

/**
 * Toggle.
 *
 * @param pin Digital pin.
 * @param status Status of led.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleLED::toggle(DigitalPin pin,_BOOL value)
{
	//Check value.
	if(value)
	{
		//Write low.
		digitalWrite(pin,LOW); 
	}
	//Write high.
	else digitalWrite(pin,HIGH);
}
