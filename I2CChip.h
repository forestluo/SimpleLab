#ifndef _I2C_CHIP_H
#define _I2C_CHIP_H

////////////////////////////////////////////////////////////////////////////////
//
// I2C Chip
//
////////////////////////////////////////////////////////////////////////////////

class I2CChip
{
private:
	/**
     * Address.
	 */
	_UINT8 address;

public:
	/**
     * Default construction.
	 *
	 * @param address Address of chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	I2CChip(_UINT8 address);

public:
	/**
     * Get address.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Address of chip.</p>
	 */
	_UINT8 getAddress() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !