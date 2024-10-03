////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <RealDevice.h>
#include <SimpleTimer3.h>

#include <ChipDHT.h>
#include <ChipDS18B20.h>
#include <PhotogateDevice.h>
#include <UltrasonicDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
RealDevice::RealDevice(void)
{
	//Set sequence id.
	sequenceID = 0;
	//Set device type.
	deviceType = -1;//Invalid device type.
	//Set ADS1247 mode.
	ads1247Mode = 0LL;
	//Set sample value.
	sampleValue = 0.0f;
	//Set average value.
	averageValue = 0.0f;
}

/**
 * Invalidate.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void RealDevice::invalidate(void)
{
	//Check device type.
	if(DS18B20(deviceType))
	{
		//Uninitialize.
		ChipDS18B20::uninitialize();
	}
	else if(HCSR04(deviceType))
	{
		//Uninitialize.
		UltrasonicDevice::uninitialize();
	}
	//Set sequence id.
	sequenceID = 0;
	//Clear device type.
	deviceType = -1;//Invalid device type.
	//Set ADS1247 mode.
	ads1247Mode = 0LL;
	//Set sample value.
	sampleValue = 0.0f;
	//Set average value.
	averageValue = 0.0f;
	//Clear interrupts.
	for(int i = 0;i < 6;i ++) detachInterrupt(i);
}

/**
 * Whether is valid mode.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if mode is valid.</p>
 */
_BOOL RealDevice::isValidMode(void) const
{
	//Check result.
	if(ads1247Mode == 0x0000000000000000LL) return _FALSE;
	//Check result.
	if(ads1247Mode == 0x0000FFFFFFFFFFFFLL) return _FALSE;
	//Return true.
	return _TRUE;
}

/**
 * Whether ads1247 is needed.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if device type is needed.</p>
 */
_BOOL RealDevice::isADS1247Needed(void) const
{
	//Check result.
	if(INVALID_DEVICE(deviceType)) return _FALSE;
	//Check result.
	if(TOGGLE_DEVICE(deviceType)) return _FALSE;
	//Check result.
	if(HCSR04(deviceType)) return _FALSE;
	//Check result.
	if(AOSONG_DHT11(deviceType)) return _FALSE;
	//Check result.
	if(DS18B20(deviceType)) return _FALSE;
	//Return true.
	return _TRUE;
}

/**
 * Get type.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Type of device.</p>
 */
_UINT32 RealDevice::getType(void) const
{
	//Return result.
	return deviceType;
}

/**
 * Get mode.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Mode of ADS1247.</p>
 */
_UINT64 RealDevice::getMode(void) const
{
	//Return result.
	return ads1247Mode;
}

/**
 * Get min index.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Mininum index of table.</p>
 */
_INT32 RealDevice::getMinIndex(void)
{
	//Return result.
	return sampleTable.getMinIndex();
}

/**
 * Get max index.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Maxinum index of table.</p>
 */
_INT32 RealDevice::getMaxIndex(void)
{
	//Return result.
	return sampleTable.getMaxIndex();
}

/**
 * Get sample value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Sample value.</p>
 */
_FLOAT RealDevice::getSampleValue(void) const
{
	//Return sample value.
	return sampleValue;
}

/**
 * Get average value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Average value.</p>
 */
_FLOAT RealDevice::getAverageValue(void) const
{
	//Read average value.
	return averageValue;
}

/**
 * Load config.
 *
 * @param configModule Config module.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL RealDevice::loadConfig(ConfigModule& configModule)
{
	//Return result.
	if(!configModule.loadConfig(deviceType,ads1247Mode,sampleTable)) return _FALSE;
	//Adjust mode.
	ads1247Mode &= 0x0000FFFFFFFFFFFFLL;
	//Check device type.
	if(AOSONG_DHT11(deviceType))
	{
		//Initialize DHT11.
		ChipDHT::initialize(DigitalPin2);
	}
	//Check device type.
	else if(DS18B20(deviceType))
	{
		//Initialize DS18B20.
		ChipDS18B20::initialize(DigitalPin2);
	}
	//It is a photogate.
	else if(PHOTOGATE(deviceType))
	{
		//Initialie photogate.
		PhotogateDevice::initialize(DigitalPin2);
	}
	//It is a ultrasonic device.
	else if(HCSR04(deviceType))
	{
		//Initialize ultrasonic device.
		UltrasonicDevice::initialize(DigitalPin18,DigitalPin19);
	}
	//Return true.
	return _TRUE;
}

/**
 * Activate data module.
 *
 * @param dataModule Data module.
 * @return
 *     <p>No results returned.</p>
 */
void RealDevice::activateDataModule(DataModule& dataModule)
{
	//Check ads1247 mode.
	//Avoid to write invalid mode into registers.
	if(isValidMode() && isADS1247Needed())
	{
		//Set sample rate.
		dataModule.setSampleRate(1);
		//Write registers.
		dataModule.writeRegisters(ads1247Mode);
		//Delay for sometime.
		delay(250);
	}
}

/**
 * Calculate.
 *
 * @param dataModule Data module.
 * @param value Sample value.
 * @return
 *     <p>Count of sample.</p>
 */
_BOOL RealDevice::readDataModule(DataModule& dataModule,SampleValue& value)
{
	//Set sample and average value.
	sampleValue = -0.0f; averageValue = -0.0f;
	//Check device type.
	if(INVALID_DEVICE(deviceType)) return _FALSE;
	//Set sequence id.
	value.sequenceID = sequenceID ++;
	//Set timestamp.
	value.timestamp = SimpleTimer3::micros();
	//It is a photogate device.
	if(PHOTOGATE(deviceType))
	{
		//Get current pulse.
		sampleValue = PhotogateDevice::readPulse() / 1000.0f;
		//Get pin value.
		_INT32 pinValue = digitalRead(PhotogateDevice::getPin());
		//Set general value.
		value.generalValue.valueType = GENERAL_BOOLEAN_TYPE;
		//Set general value.
		value.generalValue.dataValue.boolValue = pinValue ? _TRUE : _FALSE;
		//Return true.
		return _TRUE;
	}
	//It is a ultrasonic device.
	if(HCSR04(deviceType))
	{
		//Get distance of flight.
		sampleValue = UltrasonicDevice::getFlightDistance();
		//Set general value.
		value.generalValue.valueType = GENERAL_FLOAT_TYPE;
		//Set general value.
		value.generalValue.dataValue.floatValue = sampleValue;
		//Write next sample value.
		RecorderModule::writeNextSampleValue(value);
		//Return true.
		return _TRUE;
	}
	//It is a DS18B20 device.
	if(DS18B20(deviceType))
	{
		//Set sample value.
		sampleValue = 0.0f;
		//Get distance of flight.
		ChipDS18B20::read(sampleValue);
		//Set general value.
		value.generalValue.valueType = GENERAL_FLOAT_TYPE;
		//Set general value.
		value.generalValue.dataValue.floatValue = sampleValue;
		//Write next sample value.
		RecorderModule::writeNextSampleValue(value);
		//Return true.
		return _TRUE;
	}
	//Read sample value.
	dataModule.readSampleValue(value);
	//Check result.
	if(EXPERIMENT_DEVICE(deviceType))
	{
		//Get sample value.
		sampleValue = (_FLOAT)value.pinValue;
		//Set general value.
		value.generalValue.valueType = GENERAL_FLOAT_TYPE;
		//Set general value.
		value.generalValue.dataValue.floatValue = sampleValue;
		//Write next sample value.
		RecorderModule::writeNextSampleValue(value);
		//Get average value.
		averageValue = (_FLOAT)RecorderModule::getAveragePinValue();
	}
	else
	{
		//Get pin value.
		_INT32 pinValue = value.pinValue;
		//Check result.
		if(pinValue < sampleTable.getMinIndex() ||
			pinValue > sampleTable.getMaxIndex())
		{
			//Set sample value.
			sampleValue = -0.0f;
			//Set general value.
			value.generalValue.valueType = GENERAL_NULL_TYPE;
		}
		else
		{
			//Get sample value.
			sampleValue = sampleTable.getRealSampleValue(pinValue);
			//Set general value.
			value.generalValue.valueType = GENERAL_FLOAT_TYPE;
			//Set general value.
			value.generalValue.dataValue.floatValue = sampleValue;
			//Write next sample value.
			RecorderModule::writeNextSampleValue(value);
			//Get average value.
			averageValue = sampleTable.getRealSampleValue(RecorderModule::getAveragePinValue());
		}
	}
	//Return result.
	return _TRUE;
}
