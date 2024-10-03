#ifndef _ANALOG_CONNECTION_H
#define _ANALOG_CONNECTION_H

////////////////////////////////////////////////////////////////////////////////
//
// Analog Connection
//
////////////////////////////////////////////////////////////////////////////////

class AnalogConnection
{
public:
	/**
     * Whether is connected.
	 *
	 * @param pin Analog pin.
	 * @return
	 *     <p>Return true, if it is connected.</p>
	 */
	static _BOOL isConnected(AnalogPin pin);

	/**
     * Whether is connected.
	 *
	 * @param pin Analog pin.
	 * @param milliseconds Milliseconds for waiting.
	 * @return
	 *     <p>Return true, if it is connected.</p>
	 */
	static _BOOL isConnected(AnalogPin pin,_INTEGER milliseconds);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !