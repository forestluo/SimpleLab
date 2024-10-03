////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleTimer2.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Overflow count per second.
 */
#define OVERFLOW_COUNT_PER_SECOND 4
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
volatile _UINT32 timer2_seconds = 0;
/**
 * Overflow count of timer.
 */
volatile _UINT32 timer2_overflow_count = 0;

////////////////////////////////////////////////////////////////////////////////
//
// General Interruptions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Timer 2 overflow interrupt handler.
 */
ISR(TIMER2_OVF_vect)
{
	//Add overflow of timer.
	timer2_overflow_count ++;
	//Check result.
	if(timer2_overflow_count >= OVERFLOW_COUNT_PER_SECOND)
	{
		//Add seconds of timer.
		timer2_seconds ++;
		//Reset overflow count of timer.
		timer2_overflow_count = 0;
	}
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
void SimpleTimer2::initializeTimer(void)
{
    //Disable interrupts while setting registers.
    cli();

	//1. Disable the Timer/Counter2 interrupts by clearing OCIE2x and TOIE2.
	cbi(TIMSK2,OCIE2B);
	cbi(TIMSK2,OCIE2A);
	cbi(TIMSK2,TOIE2);

	//2. Select clock source by setting AS2 as appropriate.
	sbi(ASSR,AS2);

	//3. Write new value to TCNT2, OCR2x, and TCCR2x.
	//Clear counter.
	TCNT2 = 0;
    // 17.11.1 TCCR2A 每 Timer/Counter Control Register A
    //   Bit    7      6      5      4      3      2      1      0
    // (0xB0) COM2A1 COM2A0 COM2B1 COM2B0   每      每    WGM21 WGM20 
    //          0      0      0      0      0      0      0      0
    // Compare output mode (OC2A): normal port operation
    // Compare output mode (OC2B): normal port operation
    // Waveform generation mode: normal
	cbi(TCCR2A,WGM21); cbi(TCCR2A,WGM20);
    // TCCR2B 每 Timer/Counter Control Register B
    //   Bit    7     6     5     4     3     2     1    0
    // (0xB1) FOC2A FOC2B   每     每   WGM22  CS22  CS21 CS20
    //          0     0     0     0     0     0     0    0
    // Output compare A & B: 0
    // Prescaler: clkT2S/1024 (From prescaler)
	cbi(TCCR2B,WGM22);
	//Set prescaler.
	cbi(TCCR2B,CS22);sbi(TCCR2B,CS21);sbi(TCCR2B,CS20);

	//4. To switch to asynchronous operation : Wait for TCN2UB, OCR2xUB and TCR2xUB.
	while(!(ASSR & ((1 << TCN2UB) | (1 << TCR2AUB) | (1 << TCR2BUB))));
	
	//5. Clear the Timer/Counter2 Interrupt Flags.
	sbi(TIFR2,TOV2);
	
	//6. Enable TOV2 interrupt.
    // TIMSK2 每 Timer/Counter2 Interrupt Mask Register
    // Bit      7     6     5     4     3     2     1     0
    // (0x70)   每     每     每     每     每  OCIE2B OCIE2A TOIE2
    //          0     0     0     0     0     0     0     1
    // Output Compare A & B Interr. Enable: 0
    // Overflow Interrupt Enable: 1
	sbi(TIMSK2,TOIE2);

	//This needs to be called before setup.
	//Or some functions won't work there.
	sei();
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
_UINT32 SimpleTimer2::millis(void)
{
	//Temp value.
	volatile _UINT8 t = 0;
	volatile _UINT32 seconds;
	volatile _UINT32 overflow_count;
	//Keep interrupt registers.
    uint8_t oldSREG = SREG;
    //Disable interrupts.
    cli();
	//Get register value.
	t = TCNT2;
	//Get second value.
	seconds = timer2_seconds;
	//Get tickcount value.
	overflow_count = timer2_overflow_count;
    //Reset registers.
    SREG = oldSREG;
	//Calculate milliseconds.
	return seconds * 1000 + overflow_count * 250 + (unsigned long)(((uint32_t)t & 0xFF) * 0.9765625);
}
