#ifndef _FILE_MODULE_H
#define _FILE_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <SPIChip.h>
#include <ChipAT45DB161D.h>

////////////////////////////////////////////////////////////////////////////////
//
// File Module
//
////////////////////////////////////////////////////////////////////////////////

class FileModule
{
private:
	/**
     * Flags.
	 *
	 * <p>Flags of status.</p>
	 */
	_BYTE flags;

private:
	/**
     * Chip AT45DB161D
	 */
	ChipAT45DB161D chipAT45DB161D;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~FileModule(void);

	/**
	 * Default construction.
	 *
	 * @param selectPin Pin for selecting.
	 * @return
	 *     <p>No results returned.</p>
	 */
	FileModule(DigitalPin selectPin);

public:
	/**
     * Initialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void initialize(void);

	/**
     * Whether file exits.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if file exists.</p>
	 */
	_BOOL fileExists(void);

public:
	/**
     * Read uint8.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT8 readUint8(_UINT32 dataAddress);

	/**
     * Read uint16.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT16 readUint16(_UINT32 dataAddress);

	/**
     * Read uint32.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT32 readUint32(_UINT32 dataAddress);

	/**
	 * Read buffer.
	 *
	 * @param dataAddress Address of data.
	 * @param buffer Buffer.
	 * @param length Length of buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void readBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length);

public:
	/**
	 * Write uint8.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeUint8(_UINT32 dataAddress,_UINT8 value);

	/**
	 * Write uint16.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeUint16(_UINT32 dataAddress,_UINT16 value);

	/**
	 * Write uint32.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeUint32(_UINT32 dataAddress,_UINT32 value);

	/**
	 * Write buffer.
	 *
	 * @param dataAddress Address of data.
	 * @param buffer Buffer.
	 * @param length Length of buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length);

public:
	/**
	 * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !