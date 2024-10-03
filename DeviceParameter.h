#ifndef _DEVICE_PARAMETER_H
#define _DEVICE_PARAMETER_H

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Pulse parameter.
 */
typedef struct tagPulseParameter
{
	//Pulse started.
	_BOOL pulseStarted;

} PulseParameter;

/**
 * Humidity parameter.
 */
typedef struct tagHumidityParameter
{

} HumidityParameter;

/**
 * Temperature parameter.
 */
typedef struct tagTemperatureParameter
{

} TemperatureParameter;

/**
 * Device parameter.
 */
typedef union tagDeviceParameter
{
	//Pulse
	PulseParameter pulse;
	//Humidity.
	HumidityParameter humidity;
	//Temperature
	TemperatureParameter temperature;

} DeviceParameter;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !