////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <ConsoleFile.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Console Address
#define CONSOLE_ADDRESS										267776
//Console File Size
#define CONSOLE_FILE_SIZE									512
//Console File Page Count
#define CONSOLE_FILE_PAGE_COUNT								1

//Write index.
_UINT8 ConsoleFile::writeIndex								= 0;

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
void ConsoleFile::initialize(FileModule& fileModule)
{
#ifdef _DEBUG_FILE_MODULE
	//Print.
	_PRINT0("ConsoleFile::initialize : begin to initialize console file !");
#endif
	//Initialize console buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));
	//Do while.
	for(_UINT8 i = 0;i < 16;i ++)
	{
		//Write buffer.
		fileModule.writeBuffer(CONSOLE_ADDRESS + i * 32,(_BUFFER)buffer,32 * sizeof(_CHAR));
	}
}

/**
 * Write into console buffer.
 *
 * @param fileModule File module.
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void ConsoleFile::writeConsole(FileModule& fileModule,_CHAR* string)
{
#ifdef _DEBUG
	_ASSERT(string != _NULL);
#endif
	//Get length.
	_UINT8 length = strlen(string);
#ifdef _DEBUG
	_ASSERT(length >= 0 && length < 25);
#endif
	//Data address.
	_UINT32 dataAddress = CONSOLE_ADDRESS + (writeIndex & 0x0F) * 32;
	//Write length.
	fileModule.writeUint8(dataAddress,length);
	//Write buffer.
	if(length > 0) fileModule.writeBuffer(dataAddress + sizeof(_UINT8),(_BUFFER)string,length);
	//Add write index.
	writeIndex = (writeIndex + 1) & 0x0F;
}

/**
 * Read console.
 *
 * <p>The maximum length is 32.</p>
 *
 * @param fileModule File module.
 * @param index Index of string.
 * @param string String.
 * @return
 *     <p>No results returned.</p>
 */
void ConsoleFile::readConsole(FileModule& fileModule,_UINT8 index,_CHAR* string)
{
#ifdef _DEBUG
	_ASSERT(string != _NULL);
	_ASSERT(index > 0 && index < 16);
#endif
	//Data address.
	_UINT32 dataAddress = CONSOLE_ADDRESS + ((writeIndex - index) & 0x0F) * 32;
	//Read length.
	_UINT8 length = fileModule.readUint8(dataAddress);
#ifdef _DEBUG
	_ASSERT(length >= 0 && length < 25);
#endif
	//Read buffer.
	if(length > 0) fileModule.readBuffer(dataAddress + sizeof(_UINT8),(_BUFFER)string,length);
}
