////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleTimer3.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Start count.
 */
#define START_COUNT 3036

/**
 * Tick count per second.
 */
#define TICK_COUNT_PER_SECOND 1

/**
 * sbi
 */
#define sbi(sfr, bit) \
	(_SFR_BYTE(sfr) |= _BV(bit))
/**
 * cbi
 */
#define cbi(sfr, bit) \
	(_SFR_BYTE(sfr) &= ~_BV(bit))

/**
 * Seconds of timer.
 */
volatile unsigned long timer3_seconds = 0;

////////////////////////////////////////////////////////////////////////////////
//
// General Interruptions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Timer 3 overflow interrupt handler.
 */
ISR(TIMER3_OVF_vect)
{
	//Add seconds of timer.
	timer3_seconds ++;
	//Reset count register.
	TCNT3 = START_COUNT;
}

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize timer.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleTimer3::initializeTimer(void)
{
    //Disable interrupts while setting registers.
    cli();
	//Disable the Timer/Counter3 interrupts.
	TIMSK3 = 0;
	//Write new value to TCNT3, OCR3x, and TCCR3x.
	//Set prescaler as 256 and only 1 overflow counts.
	TCCR3A = 0;	TCCR3B = 0x04;	TCCR3C = 0; TCNT3 = START_COUNT;
	//Clear the Timer/Counter2 Interrupt Flags.
	sbi(TIFR3,TOV3);
	//Enable TOV2 interrupt.
	sbi(TIMSK3,TOIE3);
	//This needs to be called before setup.
	//Or some functions won't work there.
	sei();
}

/**
 * Reset.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleTimer3::reset(void)
{
	//Keep interrupt registers.
    uint8_t oldSREG = SREG;
    //Disable interrupts.
    cli();
	//Reset seconds of timer.
	timer3_seconds = 0;
	//Reset counter.
	TCNT3 = START_COUNT;
    //Reset registers.
    SREG = oldSREG;
}

/**
 * Get milliseconds.
 *
 * <p>Milliseconds according to the crystal ocilliator.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Milliseconds.</p>
 */
unsigned long SimpleTimer3::millis(void)
{
	//Temp value.
	volatile unsigned long seconds;
	volatile unsigned long tickcount;
	//Keep interrupt registers.
    uint8_t oldSREG = SREG;
    //Disable interrupts.
    cli();
	//Get second value.
	seconds = timer3_seconds;
	//Get tick count.
	tickcount = TCNT3 - START_COUNT;
    //Reset registers.
    SREG = oldSREG;
	//Calculate milliseconds.
	return seconds * 1000 + (unsigned long)((tickcount << 4) / 1000.0);
}

/**
 * Get microseconds.
 *
 * <p>Microseconds according to the crystal ocilliator.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Microseconds.</p>
 */
unsigned long SimpleTimer3::micros(void)
{
	//Temp value.
	volatile unsigned long seconds;
	volatile unsigned long tickcount;
	//Keep interrupt registers.
    uint8_t oldSREG = SREG;
    //Disable interrupts.
    cli();
	//Get second value.
	seconds = timer3_seconds;
	//Get tick count.
	tickcount = TCNT3 - START_COUNT;
    //Reset registers.
    SREG = oldSREG;
	//Calculate milliseconds.
	return seconds * 1000000 + (tickcount << 4);
}
