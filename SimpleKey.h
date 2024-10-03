#ifndef _SIMPLE_KEY_H
#define _SIMPLE_KEY_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Key
//
////////////////////////////////////////////////////////////////////////////////

class SimpleKey
{
public:
	/**
     * Whether key was pressed.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static _BOOL isPressed(DigitalPin pin);

	/**
     * Whether key was pressed.
	 *
	 * @param pin Digital pin.
	 * @param milliseconds Milliseconds.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static _BOOL isPressed(DigitalPin pin,_INTEGER milliseconds);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !