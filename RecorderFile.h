#ifndef _RECORDER_FILE_H
#define _RECORDER_FILE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <FileModule.h>
#include <DeviceRecorder.h>

////////////////////////////////////////////////////////////////////////////////
//
// Recorder File
//
////////////////////////////////////////////////////////////////////////////////

class RecorderFile
{
public:
	/**
     * Initialize.
	 *
	 * @param fileModule File module.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(FileModule& fileModule);

	/**
	 * Get count.
	 *
	 * @param fileModule File module.
	 * @return
	 *     <p>Current count.</p>
	 */
	static _UINT16 getCount(FileModule& fileModule);

	/**
	 * Get index.
	 *
	 * @param fileModule File module.
	 * @return
	 *     <p>Current index.</p>
	 */
	static _UINT16 getIndex(FileModule& fileModule);

	/**
     * Write recorder.
	 *
	 * @param fileModule File module.
	 * @param value Sample value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void writeRecorder(FileModule& fileModule,SampleValue& value);

	/**
     * Read recorder.
	 *
	 * @param fileModule File module.
	 * @param index Index of recorder.
	 * @param value Sample value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void readRecorder(FileModule& fileModule,_UINT16 index,SampleValue& value);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !