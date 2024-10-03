////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <DataModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
DataModule::~DataModule(void)
{

}

/**
 * Default construction.
 *
 * @param chipADS1247SelectPin Pin for selecting ADS1247 chip.
 * @return
 *     <p>No results returned.</p>
 */
DataModule::DataModule(DigitalPin chipADS1247SelectPin)
	: chipADS1247(chipADS1247SelectPin)
{
	//Set sample rate.
	sampleRate = -1;
	//Set sample timestamp.
	sampleTimestamp = 0;
	//Reset chip ADS1247.
	chipADS1247.resetChip();
}

/**
 * Read registers.
 *
 * @param None No parameters needed.
 * @return
 *    <p>Value of registers.</p>
 */
_UINT64 DataModule::readRegisters()
{
	//Return result.
	return chipADS1247.readRegisters();
}

/**
 * Write registers.
 *
 * @param value Value of registers.
 * @return
 *     <p>No results returned.</p>
 */
void DataModule::writeRegisters(_UINT64 value)
{
	//Return result.
	return chipADS1247.writeRegisters(value);
}

/**
 * Get sample rate.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Sample rate.</p>
 */
_SHORT DataModule::getSampleRate(void)
{
	//Return sample rate.
	return sampleRate;
}

/**
 * Whether sample is timeout.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if sample is timeout.</p>
 */
_BOOL DataModule::isSampleTimeout(void)
{
	//Get current time.
	_UINT32 currentTime = millis();
	//If there is no sample rate limitation.
	//Return true as soon as possible.
	if(sampleRate == 0) return _TRUE;
	//If current time is no bigger than sample timestamp.
	//Return true as soon as possible.
	if(currentTime <= sampleTimestamp) return _FALSE;

	//Check sample rate.
	if(sampleRate < 0)
	{
		//Skip time (in seconds).
		_UINT32 skipTime = (- sampleRate) * 1000;
		//Get delta value.
		_UINT32 deltaValue = currentTime - sampleTimestamp;
		//Check result.
		if(deltaValue > 2 * skipTime)
		{
			//Add only one step.
			sampleTimestamp += skipTime;
		}
		else if(deltaValue > skipTime)
		{
			//Set sample timestamp.
			sampleTimestamp = currentTime;
		}
		//Return false.
		else return _FALSE;
	}
	else if(sampleRate > 0)
	{
		//Get delta value.
		_UINT32 deltaValue = (currentTime - sampleTimestamp) * ((_UINT32)sampleRate);
		//If the delta value is not more than 1 second.
		//Return false as soon as possible.
		if(deltaValue < 1000) return _FALSE;
		//Check result.
		if(deltaValue < 2000)
		{
			//Set sample timestamp.
			sampleTimestamp = currentTime;
		}
		else
		{
			//Add only one step.
			sampleTimestamp += (_UINT32)(1000.0f / sampleRate);
		}
	}
	//Return true.
	return _TRUE;
}

/**
 * Set sample rate.
 *
 * <p>Reset parameters.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DataModule::setSampleRate(_SHORT sampleRate)
{
	//Set sample rate.
	this->sampleRate = sampleRate;

	//Get SYS0.
	_UINT8 value = chipADS1247.getSYS0();
	//Check sample rate.
	if(sampleRate == 0)
	{
		//Set value.
		value = (value & 0xF0) | 0x0F;
	}
	else if(sampleRate <= 5)
	{
		//Set value.
		value = value & 0xF0;
	}
	else if(sampleRate <= 10)
	{
		//Set value.
		value = (value & 0xF0) | 0x01;
	}
	else if(sampleRate <= 20)
	{
		//Set value.
		value = (value & 0xF0) | 0x02;
	}
	else if(sampleRate <= 40)
	{
		//Set value.
		value = (value & 0xF0) | 0x03;
	}
	else if(sampleRate <= 80)
	{
		//Set value.
		value = (value & 0xF0) | 0x04;
	}
	else if(sampleRate <= 160)
	{
		//Set value.
		value = (value & 0xF0) | 0x05;
	}
	else if(sampleRate <= 320)
	{
		//Set value.
		value = (value & 0xF0) | 0x06;
	}
	else if(sampleRate <= 640)
	{
		//Set value.
		value = (value & 0xF0) | 0x07;
	}
	else if(sampleRate <= 1000)
	{
		//Set value.
		value = (value & 0xF0) | 0x08;
	}
	else
	{
		//Set value.
		value = (value & 0xF0) | 0x0F;
	}
	//Set value.
	chipADS1247.setSYS0(value);
	//Set timestamp.
	sampleTimestamp = millis();
}

/**
 * Get pin value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Pin value.</p>
 */
_INT32 DataModule::getPinValue(void)
{
	//Return pin value.
	return pinValue;
}

/**
 * Read AVDD.
 *
 * @param keepRegisters Whether keep registers.
 * @return
 *     <p>AVDD of chip.</p>
 */
_FLOAT DataModule::readAVDD(_BOOL keepRegisters)
{
	//Read registers.
	_UINT64 registers = 0;
	//Check flags.
	if(keepRegisters)
	{
		//keep registers.
		registers = chipADS1247.readRegisters();
	}
	//Write registers.
	writeRegisters(0x01000360000FFLL);
	//Delay.
	delay(250);
	//Read value.
	_FLOAT avddValue = chipADS1247.readValue() * 4.0f * 2.048f / 8388607.0f;
	//Check flags and write back registers.
	if(keepRegisters) chipADS1247.writeRegisters(registers);
	//Delay.
	delay(250);
	//Return result.
	return avddValue;
}

/**
 * Read sample value.
 *
 * @param value Sample value.
 * @return
 *     <p>No results returned.</p>
 */
void DataModule::readSampleValue(SampleValue& value)
{
	//Read value.
	pinValue = chipADS1247.readValue();
	//Check result.
	if(pinValue & 0x800000) pinValue = (_INT32)(pinValue | 0xFF000000);
	//Set pin value.
	value.pinValue = pinValue;
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DataModule::dumpConfig(void)
{
	//Print.
	_PRINT0("DataModule::dumpConfig : show configs !");
	//Print.
	_PRINT1("\tsampleRate = %d",sampleRate);
	//Dump registers.
	chipADS1247.dumpRegisters();
}
