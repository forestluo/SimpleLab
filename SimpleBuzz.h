#ifndef _SIMPLE_BUZZ_H
#define _SIMPLE_BUZZ_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Buzz
//
////////////////////////////////////////////////////////////////////////////////

class SimpleBuzz
{
protected:
	/**
	 * Buzz.
	 *
	 * @param pin Digital pin.
	 * @param milliseconds Milliseconds for sleeping.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void buzz(DigitalPin pin,int milliseconds);

public:
	/**
	 * Open.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void open(DigitalPin pin);

	/**
	 * Close.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void close(DigitalPin pin);

public:
	/**
	 * Warning.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void alert(DigitalPin pin);

	/**
	 * Alert.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void warning(DigitalPin pin);

	/**
	 * Whistle.
	 *
	 * @param pin Digital pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void whistle(DigitalPin pin);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !