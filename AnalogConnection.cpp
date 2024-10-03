#include <Global.h>
#include <AnalogConnection.h>

/**
 * Whether is connected.
 *
 * @param pin Analog pin.
 * @return
 *     <p>Return true, if it is connected.</p>
 */
_BOOL AnalogConnection::isConnected(AnalogPin pin)
{
	//Return result.
	return analogRead(pin) <= 1000 ? _TRUE : _FALSE;
}

/**
 * Whether is connected.
 *
 * @param pin Analog pin.
 * @param milliseconds Milliseconds for waiting.
 * @return
 *     <p>Return true, if it is connected.</p>
 */
_BOOL AnalogConnection::isConnected(AnalogPin pin,_INTEGER milliseconds)
{
	//Check connection.
	if(!isConnected(pin)) return _FALSE;
    //Do while.
    for(int i = 0;i < milliseconds;i += 100)
    {
        //Delay for a while.
        delay(100);
        //Check pin continously.
        if(!isConnected(pin)) return _FALSE;
    }
	//Return true.
	return _TRUE;
}
