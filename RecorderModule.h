#ifndef _RECORDER_MODULE_H
#define _RECORDER_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <DeviceParameter.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Max Device Recorder
#define MAX_DEVICE_RECORDER									16
//Device Recorder Mask
#define DEVICE_RECORDER_MASK								0x0F

////////////////////////////////////////////////////////////////////////////////
//
// Recorder Module
//
////////////////////////////////////////////////////////////////////////////////

class RecorderModule
{
private:
	/**
	 * Read index.
	 */
	static _UINT8 readIndex;
	/**
	 * Write index.
	 */
	static _UINT8 writeIndex;
	/**
	 * Device parameter.
	 */
	static DeviceParameter parameter;
	/**
	 * Sample values.
	 */
	static SampleValue samples[MAX_DEVICE_RECORDER];

public:
	/**
     * Initialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(void);

	/**
	 * Get average pin value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Average pin value.</p>
	 */
	static _INT32 getAveragePinValue(void);

public:
	/**
	 * Get device parameter.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Device parameter.</p>
	 */
	static DeviceParameter& getParameter(void);

public:
	/**
     * Move to next sample value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void nextSampleValue(void);

	/**
	 * Get sample value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Current sample value.</p>
	 */
	static SampleValue& getSampleValue(void);

	/**
	 * Get last sample value.
	 *
	 * @param index Index of value.
	 * @return
	 *     <p>Sample value with specified index.</p>
	 */
	static SampleValue& getLastSampleValue(_UINT8 index);

public:
	/**
     * Write next sample value.
	 *
	 * @param value Sample value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void writeNextSampleValue(SampleValue& value);

	/**
	 * Read next sample value.
	 *
	 * @param value Sample value.
	 * @return
	 *     <p>Return true, if there is sample value.</p>
	 */
	static _BOOL readNextSampleValue(SampleValue& value);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !