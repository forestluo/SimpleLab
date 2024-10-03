#include <Global.h>
#include <SimpleBuzz.h>

/**
 * Open.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::open(DigitalPin pin)
{
    //Write value.
    digitalWrite(pin,HIGH);
}

/**
 * Close.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::close(DigitalPin pin)
{
    //Write value.
    digitalWrite(pin,LOW);
}

/**
 * Buzz.
 *
 * @param pin Digital pin.
 * @param milliseconds Milliseconds for sleep.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::buzz(DigitalPin pin,int milliseconds)
{
    //Write value.
    digitalWrite(pin,HIGH);
    //Delay for a moment.
    delay(milliseconds);
    //Write value.
    digitalWrite(pin,LOW);
}

/**
 * Alert.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::alert(DigitalPin pin)
{
	//Buzz.
	buzz(pin,1000);
	//Delay.
	delay(1000);
}

/**
 * Warning.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::warning(DigitalPin pin)
{
	//Buzz.
	buzz(pin,100);
	//Delay.
	delay(1000);
}

/**
 * Whistle.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleBuzz::whistle(DigitalPin pin)
{
	//Buzz.
	buzz(pin,100);
	//Delay.
	delay(100);
}
