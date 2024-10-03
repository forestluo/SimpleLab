#ifndef _SIMPLE_RANDOM_H
#define _SIMPLE_RANDOM_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Random
//
////////////////////////////////////////////////////////////////////////////////

class SimpleRandom
{
private:
	/**
     * Analog pin.
	 */
	AnalogPin pin;

public:
	/**
     * Default construction.
	 *
	 * @param pin Pin for random.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleRandom(AnalogPin pin);

public:
	/**
	 * Random.
	 *
	 * @param range Range of random.
	 * @return
	 *     <p>Result of random.</p>
	 */
	_INTEGER random(_INTEGER range);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !