#ifndef _CHIP_AT45DB161D_H
#define _CHIP_AT45DB161D_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip AT45DB161D
//
////////////////////////////////////////////////////////////////////////////////

class ChipAT45DB161D : public SPIChip
{
private:
	/**
     * Index of buffer.
	 */
	_UINT8 index;
	/**
	 * Chip core.
	 */
	_OBJECT chipCore;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	~ChipAT45DB161D(void);

	/**
     * Default construction.
	 *
	 * @param selectedPin Chip selected pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipAT45DB161D(DigitalPin selectedPin);

public:
	/**
     * Initialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL initialize(void);

private:
	/**
     * Seek.
	 *
	 * @param dataAddress Address of data.
	 * @param page Page number.
	 * @param offset Offset of page.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void seek(_UINT32 dataAddress,_UINT32& page,_UINT32& offset);

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
     * Load HZK bitmap.
	 *
	 * @param hzCode GB2312 code.
	 * @param bitmap HZK bitmap.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	void loadHZKBitmap(_UINT16 hzCode,_HZKBITMAP bitmap);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !