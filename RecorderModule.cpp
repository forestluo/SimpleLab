////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <RecorderModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Device parameter.
 */
DeviceParameter RecorderModule::parameter;
/**
 * Sample values.
 */
SampleValue RecorderModule::samples[MAX_DEVICE_RECORDER];

/**
 * Read index.
 */
_UINT8 RecorderModule::readIndex							= 0;
/**
 * Write index.
 */
_UINT8 RecorderModule::writeIndex							= 0;

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderModule::initialize(void)
{
	//Set read index.
	readIndex = 0;
	//Set write index.
	writeIndex = 0;
	//Clear samples.
	memset(samples,0,MAX_DEVICE_RECORDER * sizeof(SampleValue));
}

/**
 * Get average pin value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Average pin value.</p>
 */
_INT32 RecorderModule::getAveragePinValue(void)
{
	//Set min pin value.
	_INT32 minValue = (_INT32)0x7FFFFFFF;
	//Set max pin value.
	_INT32 maxValue = (_INT32)0x80000001;
	//Do while.
	for(_UINT8 i = 0;i < MAX_DEVICE_RECORDER;i ++)
	{
		//Check min pin value.
		if(samples[i].pinValue < minValue)
		{
			//Set minimum value.
			minValue = samples[i].pinValue;
		}
		//Check max pin value.
		if(samples[i].pinValue > maxValue)
		{
			//Set maximum value.
			maxValue = samples[i].pinValue;
		}
	}
	//Get sum of values.
	_INT32 value = 0;
	//Get count of values.
	_UINT8 count = 0;
	//Do while.
	for(_UINT8 i = 0;i < MAX_DEVICE_RECORDER;i ++)
	{
		//Check value.
		if(samples[i].pinValue != minValue &&
			samples[i].pinValue != maxValue)
		{
			//Add count and pin value.
			count ++; value += samples[i].pinValue;
		}
	}
	//Return result.
	return count > 0 ? (value / count) : ((minValue + maxValue) / 2);
}

/**
 * Get device parameter.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Device parameter.</p>
 */
DeviceParameter& RecorderModule::getParameter(void)
{
	//Return result.
	return parameter;
}

/**
 * Move to next.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderModule::nextSampleValue(void)
{
	//Add write index.
	writeIndex = (writeIndex + 1) & DEVICE_RECORDER_MASK;
	//Check read index.
	if(writeIndex == readIndex) readIndex = (readIndex + 1) & DEVICE_RECORDER_MASK;
}

/**
 * Get sample value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SampleValue& RecorderModule::getSampleValue(void)
{
#ifdef _DEBUG
	_ASSERT(writeIndex >= 0 && writeIndex < MAX_DEVICE_RECORDER);
#endif
	//Return result.
	return samples[writeIndex];
}

/**
 * Get last sample value.
 *
 * @param index Index of sample value.
 * @return
 *     <p>Sample value with specified index.</p>
 */
SampleValue& RecorderModule::getLastSampleValue(_UINT8 index)
{
#ifdef _DEBUG
	_ASSERT(writeIndex >= 0 && writeIndex < MAX_DEVICE_RECORDER);
#endif
	//Return result.
	return samples[(writeIndex - index) & DEVICE_RECORDER_MASK];
}

/**
 * Write next sample value.
 *
 * @param value Sample value.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderModule::writeNextSampleValue(SampleValue& value)
{
#ifdef _DEBUG
	_ASSERT(writeIndex >= 0 && writeIndex < MAX_DEVICE_RECORDER);
#endif
	//Copy sample value.
	memcpy(&samples[writeIndex],&value,sizeof(SampleValue));
	//Add write index.
	writeIndex = (writeIndex + 1) & DEVICE_RECORDER_MASK;
	//Check read index.
	if(writeIndex == readIndex) readIndex = (readIndex + 1) & DEVICE_RECORDER_MASK;
}

/**
 * Read next sample value.
 *
 * @param value Sample value.
 * @return
 *     <p>Return true, if there is sample value.</p>
 */
_BOOL RecorderModule::readNextSampleValue(SampleValue& value)
{
#ifdef _DEBUG
	_ASSERT(readIndex >= 0 && readIndex < MAX_DEVICE_RECORDER);
#endif
	//Check read index.
	if(readIndex == writeIndex) return _FALSE;
	//Copy.
	memcpy(&value,&samples[readIndex],sizeof(SampleValue));
	//Add read index.
	readIndex = (readIndex + 1) & DEVICE_RECORDER_MASK;
	//Return true.
	return _TRUE;
}
