////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <RecorderFile.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Max Recroder
#define MAX_RECORDER										8192
#define RECORDER_MASK										0x1FFF

//Recorder Address
#define RECORDER_ADDRESS									268288
//Recorder File Size (122884 bytes)
#define RECORDER_FILE_SIZE									(2 * sizeof(_UINT16) + MAX_RECORDER * sizeof(SampleValue))
//Recorder File Page Count
#define RECORDER_FILE_PAGE_COUNT							241

//Count Address
#define COUNT_ADDRESS										RECORDER_ADDRESS
//Index Address
#define INDEX_ADDRESS										(COUNT_ADDRESS + sizeof(_UINT16))
//Data Address
#define DATA_ADDRESS(n)										(INDEX_ADDRESS + sizeof(_UINT16) + (n) * sizeof(SampleValue))

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize.
 *
 * @param fileModule File module.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderFile::initialize(FileModule& fileModule)
{
#ifdef _DEBUG_FILE_MODULE
	//Print.
	_PRINT0("RecorderFile::initialize : begin to initialize recorder file !");
#endif
	//Write count.
	fileModule.writeUint16(COUNT_ADDRESS,0);
	//Write index.
	fileModule.writeUint16(INDEX_ADDRESS,0);
}

/**
 * Get count.
 *
 * @param fileModule File module.
 * @return
 *     <p>Current count.</p>
 */
_UINT16 RecorderFile::getCount(FileModule& fileModule)
{
	//Return result.
	return fileModule.readUint16(COUNT_ADDRESS);
}

/**
 * Get index.
 *
 * @param fileModule File module.
 * @return
 *     <p>Current index.</p>
 */
_UINT16 RecorderFile::getIndex(FileModule& fileModule)
{
	//Return result.
	return fileModule.readUint16(INDEX_ADDRESS) & RECORDER_MASK;
}

/**
 * Write recorder.
 *
 * @param fileModule File module.
 * @param value Sample value.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderFile::writeRecorder(FileModule& fileModule,SampleValue& value)
{
	//Read count.
	_UINT16 count = fileModule.readUint16(COUNT_ADDRESS);
	//Read index.
	_UINT16 index = fileModule.readUint16(INDEX_ADDRESS) & RECORDER_MASK;
#ifdef _DEBUG
	_ASSERT(index >= 0 && index < MAX_RECORDER);
#endif
	//Write buffer.
	fileModule.writeBuffer(DATA_ADDRESS(index),(_BUFFER)&value,sizeof(SampleValue));
	//Write index.
	fileModule.writeUint16(INDEX_ADDRESS,(index + 1) & RECORDER_MASK);
	//Write count.
	fileModule.writeUint16(COUNT_ADDRESS,count + 1);
}

/**
 * Read recorder.
 *
 * @param fileModule File module.
 * @param index Index of value.
 * @param value Sample value.
 * @return
 *     <p>No results returned.</p>
 */
void RecorderFile::readRecorder(FileModule& fileModule,_UINT16 index,SampleValue& value)
{
#ifdef _DEBUG
	_ASSERT(index >= 0 && index < MAX_RECORDER);
#endif
	//Read buffer.
	fileModule.readBuffer(DATA_ADDRESS(index & RECORDER_MASK),(_BUFFER)&value,sizeof(SampleValue));
}
