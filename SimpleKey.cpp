////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleKey.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Whether key was pressed.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleKey::isPressed(DigitalPin pin)
{
	//Return result.
	return digitalRead(pin) == LOW ? _TRUE : _FALSE;
}

/**
 * Whether key was pressed.
 *
 * @param pin Digital pin.
 * @param milliseconds Milliseconds.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleKey::isPressed(DigitalPin pin,_INTEGER milliseconds)
{
	//Check pressed.
	if(!isPressed(pin)) return _FALSE;
	//Do while.
	for(_INTEGER i = 0;i < milliseconds;i += 100)
	{
		//Sleep.
		delay(100);
		//Check pressed.
		if(!isPressed(pin)) return _FALSE;
	}
	//Return true.
	return _TRUE;
}
