#ifndef _DIGITAL_CONNECTION_H
#define _DIGITAL_CONNECTION_H

////////////////////////////////////////////////////////////////////////////////
//
// Digital Connection
//
////////////////////////////////////////////////////////////////////////////////

class DigitalConnection
{
public:
	/**
     * Whether is connected.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>Return true, if it is connected.</p>
	 */
	static _BOOL isConnected(DigitalPin pin);

	/**
     * Whether is connected.
	 *
	 * @param pin Digital pin.
	 * @param milliseconds Milliseconds for waiting.
	 * @return
	 *     <p>Return true, if it is connected.</p>
	 */
	static _BOOL isConnected(DigitalPin pin,_INTEGER milliseconds);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !