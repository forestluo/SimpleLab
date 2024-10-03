#ifndef _SIMPLE_LED_H
#define _SIMPLE_LED_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple LED
//
////////////////////////////////////////////////////////////////////////////////

class SimpleLED
{
public:
	/**
     * Open led.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void open(DigitalPin pin);

	/**
     * Close led.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void close(DigitalPin pin);

public:
	/**
	 * Toggle.
	 *
	 * @param pin Digital pin.
	 * @param status Status of led.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void toggle(DigitalPin pin,_BOOL value);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !