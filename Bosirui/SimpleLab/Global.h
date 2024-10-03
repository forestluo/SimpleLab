#ifndef _GLOBAL_H
#define _GLOBAL_H

////////////////////////////////////////////////////////////////////////////////
//
// Hardware Type Definition
//
// Definition of the hardware system type.
//
// These directives are for the portable program.
// I suppose this program would run on AVR chips.
//
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#elif defined(__AVR_ATmega32U4__)
#elif defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB162__)
#else
#endif
// 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <avr/pgmspace.h>

////////////////////////////////////////////////////////////////////////////////
//
// General requirements
//
// Including the requirements for general using.
//
// These requirements are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

//Debug
#ifndef _DEBUG
//#define															_DEBUG
#endif

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
// Including the definitions for general using.
//
// These definitions are generally used in different hardware system.
//
////////////////////////////////////////////////////////////////////////////////

//INT8
typedef int8_t													_INT8;
//Unsigned INT8
typedef uint8_t													_UINT8;
//INT16
typedef int16_t													_INT16;
//Unsigned INT16
typedef uint16_t												_UINT16;
//INT32
typedef int32_t													_INT32;
//Unsigned INT32
typedef uint32_t												_UINT32;
//INT64
typedef int64_t													_INT64;
//Unsigned INT64
typedef uint64_t												_UINT64;

//BOOL
typedef bool													_BOOL;
//TRUE
#define _TRUE													true
//FALSE
#define _FALSE													false

//Byte
typedef _INT8													_BYTE;
//Short
typedef _INT16													_SHORT;
//Integer
typedef _INT32													_INTEGER;
//Long
typedef _INT64													_LONG;

//Float
typedef float													_FLOAT;
//Double
typedef double													_DOUBLE;

//Char
typedef char													_CHAR;
//Wide Char
typedef short													_WIDECHAR;

//Object
typedef void													*_OBJECT;
//String
typedef _CHAR													*_STRING;
//Wide String
typedef _WIDECHAR												*_WIDESTRING;
//Buffer
typedef _BYTE													*_BUFFER;

//Block
typedef _BYTE													_BLOCK[256];
//HZK Bitmap
typedef _BYTE													_HZKBITMAP[32];

//Null
#define _NULL													((_OBJECT)0)

////////////////////////////////////////////////////////////////////////////////
//
// General including files
//
// Including the files for the system.
//
// These including files are generally used in different operation system.
//
////////////////////////////////////////////////////////////////////////////////

#include <SimplePin.h>
#include <SimplePrint.h>
#include <SimpleFormat.h>
#include <SimpleAssert.h>

#include <SimpleUART.h>

#include <SimpleMotor.h>
#include <DCMotor.h>

#include <SimpleSensor.h>
#include <AnalogSensor.h>
#include <SwitchSensor.h>
#include <ReflectSensor.h>

#include <SimpleDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

//Swap16
#define SWAP16(v) \
	((((v) & 0xff00) >> 8) | (((v) & 0x00ff) << 8))
//Swap32
#define SWAP32(v) \
	((((v) & 0x000000ff) << 24) | (((v) & 0x0000ff00) << 8) | (((v) & 0x00ff0000) >> 8) | (((v) & 0xff000000) >> 24))

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
