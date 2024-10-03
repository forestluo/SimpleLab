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
#define															_DEBUG
#endif

//Degbu Device Module
#define _DEBUG_DEVICE_MODULE
//Debug Data Module
#define _DEBUG_DATA_MODULE
//Debug File Module
#define _DEBUG_FILE_MODULE
//Debug Config Module
#define _DEBUG_CONFIG_MODULE
//Debug Display Module
#define _DEBUG_DISPLAY_MODULE
//Debug Network Module
//#define _DEBUG_NETWORK_MODULE
//Debug Wireless Module
//#define _DEBUG_WIRELESS_MODULE

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

//Magic Number
#define _MAGIC_NUMBER											0x19751204
//Protocol Port
#define _PROTOCOL_PORT											9527
//Current Version
#define _CURRENT_VERSION										0x10
//Protocol Version
#define _PROTOCOL_VERSION										0x11

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
#include <GeneralValue.h>

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
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

//Invalid Device
#define INVALID_DEVICE(deviceType) \
	(deviceType == 0xFFFFFFFF)
//Experiment Device
#define EXPERIMENT_DEVICE(deviceType) \
	(deviceType == 0x00000000)
//Toggle Device
#define TOGGLE_DEVICE(deviceType) \
	((deviceType & 0xFFFF0000) == 0x01010000)
//Distance Device
#define DISTANCE_DEVICE(deviceType) \
	((deviceType & 0xFFFF0000) == 0x03010000)
//Infrared Distance Device
#define INFRARED_DISTANCE_DEVICE(deviceType) \
	((deviceType & 0xFFFFFF00) == 0x03010100)
//Ultrasonic Distance Device
#define ULTRASONIC_DISTANCE_DEVICE(deviceType) \
	((deviceType & 0xFFFFFF00) == 0x03010200)

//Photogate
#define PHOTOGATE(deviceType) \
	(deviceType == 0x01010100)
//SHARP GP2Y0A21YK
#define SHARP_GP2Y0A21YK(deviceType) \
	(deviceType == 0x03010101)
//SHARP GP2Y0A02YK0F
#define SHARP_GP2Y0A02YK0F(deviceType) \
	(deviceType == 0x03010102)
//HC-SR04
#define HCSR04(deviceType) \
	(deviceType == 0x03010201)
//GQY WL0008
#define GQY_WL0008(deviceType) \
	(deviceType == 0x02010100)
//AOSONG DHT11
#define AOSONG_DHT11(deviceType) \
	(deviceType == 0x0A030001)
//GQY WL0001
#define GQY_WL0001(deviceType) \
	(deviceType == 0x08010100)
//ACS712
#define ACS712(deviceType) \
	(deviceType == 0x08020101)
//DS18B20
#define DS18B20(deviceType) \
	(deviceType == 0x0A010101)
//MPX10DP
#define MPX10DP(deviceType) \
	(deviceType == 0x06010101)
//E900
#define E900(deviceType) \
	(deviceType == 0x0C010101)

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

#define LTRIM_STRING(b,v)										\
{																\
	_UINT16 p = 0;												\
	while(b[p] == ' ' && b[p] != 0 && p < (v)) p ++;			\
	for(_UINT16 q = 0;q < 32;q ++) b[q] = b[q + p];				\
}																\

#define DOUBLE_ASCII(b,d)										\
{																\
	for(_UINT16 i = 0;i < strlen(b);i ++)						\
	{															\
		d[2 * i] = 0xa3; d[2 * i + 1] = 0xb0 + (b[i] - '0');	\
	}															\
}																\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
