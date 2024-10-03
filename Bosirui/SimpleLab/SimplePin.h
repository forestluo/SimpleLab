#ifndef _SIMPLE_PIN_H
#define _SIMPLE_PIN_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

//Max Analog Pin
#define MAX_ANALOG_PIN										16
//Max Digital Pin
#define MAX_DIGITAL_PIN										54

#elif defined(__AVR_ATmega32U4__)

#elif defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB162__)

#else

//Max Analog Pin
#define MAX_ANALOG_PIN										6
//Max Digital Pin
#define MAX_DIGITAL_PIN										14

#endif

/**
 * Analog pin.
 */
typedef enum tagAnalogPin
{
	AnalogPin0 = 0,
	AnalogPin1 = 1,
	AnalogPin2 = 2,
	AnalogPin3 = 3,
	AnalogPin4 = 4,
	AnalogPin5 = 5,
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	AnalogPin6 = 6,
	AnalogPin7 = 7,
	AnalogPin8 = 8,
	AnalogPin9 = 9,
	AnalogPin10 = 10,
	AnalogPin11 = 11,
	AnalogPin12 = 12,
	AnalogPin13 = 13,
	AnalogPin14 = 14,
	AnalogPin15 = 15,
#endif
} AnalogPin;

/**
 * Digital pin.
 */
typedef enum tagDigitalPin
{
	DigitalPin0 = 0,
	DigitalPin1 = 1,
	DigitalPin2 = 2,
	DigitalPin3 = 3,
	DigitalPin4 = 4,
	DigitalPin5 = 5,
	DigitalPin6 = 6,
	DigitalPin7 = 7,
	DigitalPin8 = 8,
	DigitalPin9 = 9,
	DigitalPin10 = 10,
	DigitalPin11 = 11,
	DigitalPin12 = 12,
	DigitalPin13 = 13,
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	DigitalPin14 = 14,
	DigitalPin15 = 15,
	DigitalPin16 = 16,
	DigitalPin17 = 17,
	DigitalPin18 = 18,
	DigitalPin19 = 19,
	DigitalPin20 = 20,
	DigitalPin21 = 21,
	DigitalPin22 = 22,
	DigitalPin23 = 23,
	DigitalPin24 = 24,
	DigitalPin25 = 25,
	DigitalPin26 = 26,
	DigitalPin27 = 27,
	DigitalPin28 = 28,
	DigitalPin29 = 29,
	DigitalPin30 = 30,
	DigitalPin31 = 31,
	DigitalPin32 = 32,
	DigitalPin33 = 33,
	DigitalPin34 = 34,
	DigitalPin35 = 35,
	DigitalPin36 = 36,
	DigitalPin37 = 37,
	DigitalPin38 = 38,
	DigitalPin39 = 39,
	DigitalPin40 = 40,
	DigitalPin41 = 41,
	DigitalPin42 = 42,
	DigitalPin43 = 43,
	DigitalPin44 = 44,
	DigitalPin45 = 45,
	DigitalPin46 = 46,
	DigitalPin47 = 47,
	DigitalPin48 = 48,
	DigitalPin49 = 49,
	DigitalPin50 = 50,
	DigitalPin51 = 51,
	DigitalPin52 = 52,
	DigitalPin53 = 53,
#endif
} DigitalPin;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
