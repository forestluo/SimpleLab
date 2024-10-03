#ifndef _SAMPLE_TABLE_H
#define _SAMPLE_TABLE_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions.
//
////////////////////////////////////////////////////////////////////////////////

//Uniform Fitting Table
#define UNIFORM_FITTING_TABLE								1
//Linear Fitting Table
#define LINEAR_FITTING_TABLE								2
//Gaussian Fitting Table
#define GAUSSIAN_FITTING_TABLE								3

////////////////////////////////////////////////////////////////////////////////
//
// Sample Table
//
////////////////////////////////////////////////////////////////////////////////

class SampleTable
{
private:
	/**
     * Type.
	 */
	_UINT8 type;
	/**
	 * Size of parameter.
	 */
	_UINT16 size;

private:
	/**
	 * Minimum index value.
	 */
	_INT32 minIndex;
	/**
	 * Maximum index value.
	 */
	_INT32 maxIndex;

private:
	/**
	 * Parameter values.
	 */
	_FLOAT parameterValues[256];

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	~SampleTable();

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SampleTable(void);

public:
	/**
     * Get type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of table.</p>
	 */
	_UINT8 getType(void);

	/**
	 * Set power.
	 *
	 * @param power Power of table.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setType(_UINT8 type);

	/**
     * Get size.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of table.</p>
	 */
	_UINT16 getSize(void);
	
	/**
	 * Set size.
	 *
	 * @param size Size of table.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSize(_UINT16 size);

public:
	/**
     * Get min index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mininum index of table.</p>
	 */
	_INT32 getMinIndex(void);

	/**
	 * Set minimum index.
	 *
	 * @param minIndex Minimum index.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMinIndex(_INT32 minIndex);

	/**
     * Get max index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Maxinum index of table.</p>
	 */
	_INT32 getMaxIndex(void);

	/**
	 * Set maximum index.
	 *
	 * @param maxIndex Maximum index.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMaxIndex(_INT32 maxIndex);

public:
	/**
	 * Get parameter value.
	 *
	 * @param index Index of value.
	 * @return
	 *     <p>Real value.</p>
	 */
	_FLOAT getParameterValue(_UINT8 index);

	/**
	 * Set parameter value.
	 *
	 * @param index Index of value.
	 * @param value Parameter value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setParameterValue(_UINT8 index,_FLOAT value);

private:
	/**
	 * Get uniform value.
	 *
	 * @param pinValue Pin value.
	 * @return
	 *     <p>Uniform value of pin value.</p>
	 */
	_FLOAT getUniformValue(_INT32 pinValue);

	/**
	 * Get linear value.
	 *
	 * @param pinValue Pin value.
	 * @return
	 *     <p>Linear value of pin value.</p>
	 */
	_FLOAT getLinearValue(_INT32 pinValue);

	/**
	 * Get gaussian value.
	 *
	 * @param pinValue Pin value.
	 * @return
	 *     <p>Gaussian value of pin value.</p>
	 */
	_FLOAT getGaussianValue(_INT32 pinValue);

public:
	/**
	 * Get real sample value.
	 *
	 * @param pinValue Pin value.
	 * @return
	 *     <p>Real sample value of pin value.</p>
	 */
	_FLOAT getRealSampleValue(_INT32 pinValue);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
