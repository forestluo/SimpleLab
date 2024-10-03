////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <PhotogateDevice.h>

#include <SimpleTimer3.h>
#include <RecorderModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Pin
DigitalPin PhotogateDevice::pin								= DigitalPin2;

////////////////////////////////////////////////////////////////////////////////
//
// General Interruption
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Photogate interrupt.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void photogateInterrupt(void)
{
	//Get sample value.
	SampleValue& value = RecorderModule::getSampleValue();
	//Get device parameter.
	DeviceParameter& parameter = RecorderModule::getParameter();
	//Check result.
	if(digitalRead(PhotogateDevice::getPin()) == HIGH)
	{
		//Check pulse started.
		if(!parameter.pulse.pulseStarted)
		{
			//Start pulse started.
			parameter.pulse.pulseStarted = _TRUE;
			//Set timestamp.
			value.timestamp = SimpleTimer3::micros();
			//Set pin value.
			value.pinValue = HIGH;
			//Set value type.
			value.generalValue.valueType = GENERAL_INTEGER_TYPE;
			//Set value.
			value.generalValue.dataValue.integerValue = 0;
		}
	}
	else
	{
		//Check tick started.
		if(parameter.pulse.pulseStarted)
		{
			//Stop tick started.
			parameter.pulse.pulseStarted = _FALSE;
			//Set value.
			value.generalValue.dataValue.integerValue = SimpleTimer3::micros() - value.timestamp;
			//Move to next sample value.
			RecorderModule::nextSampleValue();
		}
	}
}

/**
 * Initialize.
 *
 * @param pin Digital pin.
 * @return
 *     <p>No results returned.</p>
 */
void PhotogateDevice::initialize(DigitalPin pin)
{
	//Set pin mode.
	pinMode(pin,INPUT);
	//Set pin.
	PhotogateDevice::pin = pin;
	//Initialize recorder module.
	RecorderModule::initialize();
	//Get device parameter.
	DeviceParameter& parameter = RecorderModule::getParameter();
	//Set pulse stated.
	parameter.pulse.pulseStarted = _FALSE;
	//Check status.
	if(digitalRead(pin) == HIGH)
	{
		//Start pulse started.
		parameter.pulse.pulseStarted = _TRUE;
		//Get sample value.
		SampleValue& value = RecorderModule::getSampleValue();
		//Set timestamp.
		value.timestamp = SimpleTimer3::micros();
		//Set pin value.
		value.pinValue = HIGH;
		//Set value type.
		value.generalValue.valueType = GENERAL_INTEGER_TYPE;
		//Set value.
		value.generalValue.dataValue.integerValue = 0;
	}
	//Attach interrupt with INT0.
	attachInterrupt(0,photogateInterrupt,CHANGE);
}

/**
 * Get pin.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
DigitalPin PhotogateDevice::getPin(void)
{
	//Return result.
	return pin;
}

/**
 * Read pulse.
 *
 * <p>Read latest pulse.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Time of lastest pulse.</p>
 */
_UINT32 PhotogateDevice::readPulse(void)
{
	//Get device parameter.
	DeviceParameter& parameter = RecorderModule::getParameter();
	//Check result.
	if(parameter.pulse.pulseStarted)
	{
		//Get sample value.
		SampleValue& value = RecorderModule::getSampleValue();
		//Return result.
		return SimpleTimer3::micros() - value.timestamp;
	}
	//Get last sample value.
	SampleValue& value = RecorderModule::getLastSampleValue(1);
	//Return result.
	return value.generalValue.dataValue.integerValue;
}

/**
 * Read pulses.
 *
 * <p>Read latest pulses.</p>
 *
 * @param pulses Pulses ticks.
 * @param count Count of pulses.
 * @return
 *     <p>No results returned.</p>
 */
void PhotogateDevice::readPulses(_UINT32* pulses,_UINT8 count)
{
#ifdef _DEBUG
	_ASSERT(pulses != _NULL);
	_ASSERT(count > 0 && count < 16);
#endif
	//Do while.
	for(_UINT8 i = 0;i < count;i ++)
	{
		//Get last sample value.
		SampleValue& value = RecorderModule::getLastSampleValue(i + 1);
		//Calculate pulse result.
		pulses[i] = value.generalValue.dataValue.integerValue;
	}
}
