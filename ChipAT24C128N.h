#ifndef _CHIP_AT24C128N_H
#define _CHIP_AT24C128N_H

////////////////////////////////////////////////////////////////////////////////
//
// Chip AT24C128N
//
////////////////////////////////////////////////////////////////////////////////

class ChipAT24C128N : public I2CChip
{
public:
	/**
     * Default construction.
	 *
	 * @param address Address of chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ChipAT24C128N(_UINT8 address);

public:
	/**
     * Read data.
	 *
	 * @param dataAddress Address of data.
	 * @param value Data value.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL readData(_UINT16 dataAddress,_UINT8& value);

	/**
	 * Write data.
	 *
	 * @param dataAddress Address of data.
	 * @param value Data value.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeData(_UINT16 dataAddress,_UINT8 value);

public:
	/**
     * Read page.
	 *
	 * <p>Should not read more than 28 bytes at a time !</p>
	 *
	 * @param dataAddress Address of page.
	 * @param buffer Buffer of page.
	 * @param length Length of page.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL readPage(_UINT16 dataAddress,_BUFFER buffer,_UINT16 length);

	/**
     * Write page.
	 *
	 * <p>Should not write more than 28 bytes at a time !</p>
	 *
	 * @param dataAddress Address of page.
	 * @param buffer Buffer of page.
	 * @param length Length of page.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writePage(_UINT16 dataAddress,_BUFFER buffer,_UINT16 length);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !