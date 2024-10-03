////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <FileModule.h>

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
FileModule::~FileModule(void)
{

}

/**
 * Default construction.
 *
 * @param selectPin Pin for selecting card.
 * @return
 *     <p>No results returned.</p>
 */
FileModule::FileModule(DigitalPin selectPin)
	: chipAT45DB161D(selectPin)
{
	//Set flags.
	flags = 0x00;
}

/**
 * Initialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::initialize(void)
{
#ifdef _DEBUG_FILE_MODULE
	//Print.
	_PRINT0("FileModule::initialize : begin to initialize file !");
#endif
	//Initialize.
	flags = chipAT45DB161D.initialize() ? 0x01 : 0x00;
	//Check result.
	if(!fileExists())
	{
#ifdef _DEBUG_FILE_MODULE
		//Print.
		_PRINT0("FileModule::initialize : fail to initialize file !");
#endif
	}
}

/**
 * Whether file exits.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if card exists.</p>
 */
_BOOL FileModule::fileExists(void)
{
	//Return result.
	return ((flags & 0x01) == 0x01) ? _TRUE : _FALSE;
}

/**
 * Read uint8.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT8 FileModule::readUint8(_UINT32 dataAddress)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Read result.
	return chipAT45DB161D.readUint8(dataAddress);
}

/**
 * Read uint16.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT16 FileModule::readUint16(_UINT32 dataAddress)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Return result.
	return chipAT45DB161D.readUint16(dataAddress);
}

/**
 * Read uint32.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT32 FileModule::readUint32(_UINT32 dataAddress)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Return result.
	return chipAT45DB161D.readUint32(dataAddress);
}

/**
 * Read buffer.
 *
 * @param dataAddress Address of data.
 * @param buffer Buffer.
 * @param length Length of buffer.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::readBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
	_ASSERT(buffer != _NULL);
	_ASSERT(length > 0 && length < 256);
#endif
	//Read buffer.
	chipAT45DB161D.readBuffer(dataAddress,buffer,length);
}

/**
 * Write uint8.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::writeUint8(_UINT32 dataAddress,_UINT8 value)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Write.
	chipAT45DB161D.writeUint8(dataAddress,value);
}

/**
 * Write uint16.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::writeUint16(_UINT32 dataAddress,_UINT16 value)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Write.
	chipAT45DB161D.writeUint16(dataAddress,value);
}

/**
 * Write uint32.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::writeUint32(_UINT32 dataAddress,_UINT32 value)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
#endif
	//Write.
	chipAT45DB161D.writeUint32(dataAddress,value);
}

/**
 * Write buffer.
 *
 * @param dataAddress Address of data.
 * @param buffer Buffer.
 * @param length Length of buffer.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::writeBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG_FILE_MODULE
	//Assert condition.
	_ASSERT(fileExists());
	_ASSERT(buffer != _NULL);
	_ASSERT(length > 0 && length < 256);
#endif
	//Write buffer.
	chipAT45DB161D.writeBuffer(dataAddress,buffer,length);
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void FileModule::dumpConfig(void)
{
	//Print.
	_PRINT0("FileModule::dumpConfig : show flags !");
	//Print.
	_PRINT1("\tfileExists = %d",fileExists());
}
