#include <Global.h>
#include <SampleTable.h>

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
SampleTable::~SampleTable()
{

}

/**
 * Default construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SampleTable::SampleTable()
{
	//Set type.
	this->type = 0;
	//Set size.
	this->size = 0;
	//Clear parameter values.
	memset(parameterValues,0,256 * sizeof(_FLOAT));
}

/**
 * Get type.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Type of table.</p>
 */
_UINT8 SampleTable::getType(void)
{
	//Return result.
	return type;
}

/**
 * Set type.
 *
 * @param type Type of table.
 * @return
 *     <p>No results returned.</p>
 */
void SampleTable::setType(_UINT8 type)
{
#ifdef _DEBUG
	_ASSERT(type > 0 && type <= 3);
#endif
	//Set type.
	this->type = type;
}

/**
 * Get size.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Size of parameter.</p>
 */
_UINT16 SampleTable::getSize(void)
{
	//Return result.
	return size;
}

/**
 * Set size.
 *
 * @param size Size of parameter.
 * @return
 *     <p>No results returned.</p>
 */
void SampleTable::setSize(_UINT16 size)
{
#ifdef _DEBUG
	_ASSERT(size >= 2 && size <= 256);
#endif
	//Set size.
	this->size = size;
}

/**
 * Get minimum index.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Minimum index of table.</p>
 */
_INT32 SampleTable::getMinIndex(void)
{
	//Return result.
	return minIndex;
}

/**
 * Set minimum index.
 *
 * @param minIndex Minimum index.
 * @return
 *     <p>No results returned.</p>
 */
void SampleTable::setMinIndex(_INT32 minIndex)
{
	//Set minimum index.
	this->minIndex = minIndex;
}

/**
 * Get maximum index.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Maximum index of table.</p>
 */
_INT32 SampleTable::getMaxIndex(void)
{
	//Return result.
	return maxIndex;
}

/**
 * Set maximum index.
 *
 * @param maxIndex Maximum index.
 * @return
 *     <p>No results returned.</p>
 */
void SampleTable::setMaxIndex(_INT32 maxIndex)
{
	//Set maximum index.
	this->maxIndex = maxIndex;
}

/**
 * Get parameter value.
 *
 * @param index Index of value.
 * @return
 *     <p>Paremter value.</p>
 */
_FLOAT SampleTable::getParameterValue(_UINT8 index)
{
	//Return result.
	return parameterValues[index & 0xFF];
}

/**
 * Set parameter value.
 *
 * @param index Index of value.
 * @param value Real value.
 * @return
 *     <p>No results returned.</p>
 */
void SampleTable::setParameterValue(_UINT8 index,_FLOAT value)
{
	//Set real value.
	parameterValues[index & 0xFF] = value;
}

/**
 * Get uniform value.
 *
 * @param pinValue Pin value.
 * @return
 *     <p>Uniform value of pin value.</p>
 */
_FLOAT SampleTable::getUniformValue(_INT32 pinValue)
{
#ifdef _DEBUG
	_ASSERT(pinValue >= minIndex && pinValue <= maxIndex);
#endif
	//Get index value.
	_FLOAT indexValue = (_FLOAT)(pinValue - minIndex) / (_FLOAT)(maxIndex - minIndex) * (size - 1);
#ifdef _DEBUG
	_ASSERT(indexValue >= 0 && indexValue < size);
#endif
	//Get ceil value.
	_INT32 ceilIndex = ceil(indexValue);
#ifdef _DEBUG
	_ASSERT(ceilIndex >= 0 && ceilIndex < size);
#endif
	//Get floor value.
	_INT32 floorIndex = floor(indexValue);
#ifdef _DEBUG
	_ASSERT(floorIndex >= 0 && floorIndex < size);
#endif
	//Return linear value.
	return (indexValue - floorIndex) * (parameterValues[ceilIndex] - parameterValues[floorIndex]) + parameterValues[floorIndex];
}

/**
 * Get linear value.
 *
 * @param pinValue Pin value.
 * @return
 *     <p>Linear value of pin value.</p>
 */
_FLOAT SampleTable::getLinearValue(_INT32 pinValue)
{
#ifdef _DEBUG
	_ASSERT((size % 2) == 0 && size >= 4);
	_ASSERT(pinValue >= minIndex && pinValue <= maxIndex);
#endif
	//Do while.
	for(_UINT16 i = 1;i < size / 2;i ++)
	{
		//Get index value.
		_FLOAT x2 = parameterValues[2 * i];
		//Check result.
		if(x2 >= pinValue)
		{
			//Get index value.
			_FLOAT x1 = parameterValues[2 * (i - 1)];
			//Get real value.
			_FLOAT y2 = parameterValues[2 * i + 1];
			//Get real value.
			_FLOAT y1 = parameterValues[2 * (i - 1) + 1];
			//Return result.
			return ((_FLOAT)pinValue - x1) / (x2 - x1) * (y2 - y1) + y1;
		}
	}
	//Return 0.0.
	return 0.0;
}

/**
 * Get gaussian value.
 *
 * @param pinValue Pin value.
 * @return
 *     <p>Gaussian value of pin value.</p>
 */
_FLOAT SampleTable::getGaussianValue(_INT32 pinValue)
{
	//Value.
	_FLOAT value = 0.0f;
#ifdef _DEBUG
	_ASSERT(size <= 9 && (size % 3) == 0);
#endif
	//Do while.
	for(_UINT16 i = 0;i < size / 3;i ++)
	{
		//Get parameter.
		_FLOAT a = parameterValues[3 * i + 0];
		_FLOAT b = parameterValues[3 * i + 1];
		_FLOAT c = parameterValues[3 * i + 2];
		_FLOAT p = ((_FLOAT)pinValue - b) / c;
		//Add value.
		value += a * exp(- p * p);
	}
	//Return result.
	return value;
}

/**
 * Get real sample value.
 *
 * @param pinValue Pin value.
 * @return
 *     <p>Real sample value of pin value.</p>
 */
_FLOAT SampleTable::getRealSampleValue(_INT32 pinValue)
{
#ifdef _DEBUG
	_ASSERT(pinValue >= minIndex && pinValue <= maxIndex);
#endif
	//Check type.
	switch(type)
	{
	case UNIFORM_FITTING_TABLE:
		//Return result.
		return getUniformValue(pinValue);
	case LINEAR_FITTING_TABLE:
		//Return result.
		return getLinearValue(pinValue);
	case GAUSSIAN_FITTING_TABLE:
		//Return result.
		return getGaussianValue(pinValue);
	default:;
	}
	//Return default.
	return 0.0;
}
