#include <Global.h>
#include <SimpleRandom.h>

/**
 * Default construction.
 *
 * @param pin Analog pin.
 * @return
 *     <p>No results returned.</p>
 */
SimpleRandom::SimpleRandom(AnalogPin pin)
{
	//Set pin.
	this->pin = pin;

    //Set pin mode.
    pinMode(pin,INPUT);
    //If analog input pin 0 is unconnected, random analog
    //noise will cause the call to randomSeed() to generate
    //different seed numbers each time the sketch runs.
    //randomSeed() will then shuffle the random function.
    randomSeed(analogRead(pin));
}

/**
 * Random.
 *
 * @param range Range of random.
 * @return
 *     <p>Result of random.</p>
 */
_INTEGER SimpleRandom::random(_INTEGER range)
{
	//Return result.
	return ::random(range);
}
