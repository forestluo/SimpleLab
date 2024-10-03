#include <SPI.h>
#include <Global.h>
#include <SPIChip.h>
#include <ChipADS1247.h>

#define MUX0_REGISTER										0x00
#define VBIAS_REGISTER										0x01
#define MUX1_REGISTER										0x02
#define SYS0_REGISTER										0x03
#define OFC0_REGISTER										0x04
#define OFC1_REGISTER										0x05
#define OFC2_REGISTER										0x06
#define FCS0_REGISTER										0x07
#define FCS1_REGISTER										0x08
#define FCS2_REGISTER										0x09
#define IDAC0_REGISTER										0x0a
#define IDAC1_REGISTER										0x0b
#define GPIOCFG_REGISTER									0x0c
#define GPIODIR_REGISTER									0x0d
#define GPIODAT_REGISTER									0x0e

/**
 * Default construction.
 *
 * @param selectedPin Pin for selection.
 * @return
 *     <p>No results returned.</p>
 */
ChipADS1247::ChipADS1247(DigitalPin selectedPin)
	: SPIChip(selectedPin)
{

}

/**
 * Select chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::selectChip(void)
{
	//Select chip.
	SPIChip::selectChip();
    //Set data mode.
	//This chip would work under mode 1.
    SPI.setDataMode(SPI_MODE1);//0x04
}

/**
 * Unselected chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::unselectChip(void)
{
	//Unselect chip.
	SPIChip::unselectChip();
	//Set data mode.
	//Recover data mode as previous.
    SPI.setDataMode(SPI_MODE0);//0x00
}

/**
 * Reset chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::resetChip(void)
{
	//Select chip.
	selectChip();
	//Send reset command.
	SPI.transfer(0x06);
	//Unselect chip.
	unselectChip();
}

/**
 * Sleep chip.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::sleepChip(void)
{
	//Select chip.
	selectChip();
	//Send sleep command.
	SPI.transfer(0x02);
	//Unselect chip.
	unselectChip();
}

/**
 * Wakeup.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::wakeupChip(void)
{
	//Select chip.
	selectChip();
	//Send wakeup command.
	SPI.transfer(0x00);
	//Unselect chip.
	unselectChip();
}

/**
 * Read register.
 *
 * @param address Address of register.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::readRegister(_UINT8 address)
{
#ifdef _DEBUG
	_ASSERT(address >= 0 && address <= 14);
#endif
	//Set reading register.
	SPI.transfer(0x20 | (address & 0x0F));
	//Read one byte.
	SPI.transfer(0x00);
	//Return result.
	return SPI.transfer(0xFF);
}

/**
 * Write register.
 *
 * @param address Address of register.
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::writeRegister(_UINT8 address,_UINT8 value)
{
#ifdef _DEBUG
	_ASSERT(address >= 0 && address <= 14);
#endif
	//Set writing register.
	SPI.transfer(0x40 | (address & 0x0F));
	//Write one byte.
	SPI.transfer(0x00);
	//Send value of register.
	SPI.transfer(value);
}

/**
 * Get MUX0.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getMUX0()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(MUX0_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set MUX0.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setMUX0(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(MUX0_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Get VBIAS.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getVBIAS()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(VBIAS_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set VBIAS.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setVBIAS(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(VBIAS_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Get MUX1.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getMUX1()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(MUX1_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set MUX1.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setMUX1(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(MUX1_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Get SYS0.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getSYS0()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(SYS0_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set SYS0.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setSYS0(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(SYS0_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Get IDAC0.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getIDAC0()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(IDAC0_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set IDAC0.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setIDAC0(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(IDAC0_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Get IDAC1.
 *
 * @param None No parameter needed.
 * @return
 *     <p>Value of register.</p>
 */
_UINT8 ChipADS1247::getIDAC1()
{
	//Select chip.
	selectChip();
	//Read register.
	_UINT8 value = readRegister(IDAC1_REGISTER);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Set IDAC1.
 *
 * @param value Value.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::setIDAC1(_UINT8 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(IDAC1_REGISTER,value);
	//Unselect cihp.
	unselectChip();
}

/**
 * Read registers.
 *
 * <p>MUX0 | VBIAS | MUX1 | SYS0 | IDAC0 | IDAC1</p>
 *
 * @param None No parameters needed.
 * @return
 *    <p>Value of registers.</p>
 */
_UINT64 ChipADS1247::readRegisters()
{
	//Value.
	_UINT64 value = 0;
	//Select chip.
	selectChip();
	//Read register.
	value |= ((_UINT64)readRegister(MUX0_REGISTER) & 0xFF) << 40;
	//Read register.
	value |= ((_UINT64)readRegister(VBIAS_REGISTER) & 0xFF) << 32;
	//Read register.
	value |= ((_UINT64)readRegister(MUX1_REGISTER) & 0xFF) << 24;
	//Read register.
	value |= ((_UINT64)readRegister(SYS0_REGISTER) & 0xFF) << 16;
	//Read register.
	value |= ((_UINT64)readRegister(IDAC0_REGISTER) & 0xFF) << 8;
	//Read register.
	value |= ((_UINT64)readRegister(IDAC1_REGISTER) & 0xFF) << 0;
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Write registers.
 *
 * <p>MUX0 | VBIAS | MUX1 | SYS0 | IDAC0 | IDAC1</p>
 *
 * @param value Value of registers.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::writeRegisters(_UINT64 value)
{
	//Select chip.
	selectChip();
	//Write register.
	writeRegister(MUX0_REGISTER,(_UINT8)(value >> 40));
	//Write register.
	writeRegister(VBIAS_REGISTER,(_UINT8)(value >> 32));
	//Write register.
	writeRegister(MUX1_REGISTER,(_UINT8)(value >> 24));
	//Write register.
	writeRegister(SYS0_REGISTER,(_UINT8)(value >> 16));
	//Write register.
	writeRegister(IDAC0_REGISTER,(_UINT8)(value >> 8));
	//Write register.
	writeRegister(IDAC1_REGISTER,(_UINT8)(value >> 0));
	//Unselect chip.
	unselectChip();
}

/**
 * Read AVDD value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>AVDD value.</p>
 */
_FLOAT ChipADS1247::readAVDD(void)
{
	//Write registers.
	writeRegisters(0x01000360000FFLL);
	//Delay.
	delay(250);
	//Read value.
	_FLOAT avddValue = readValue() * 4.0f * 2.048f / 8388607.0f;
	//Return result.
	return avddValue;
}

/**
 * Read A/D value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Value of A/D result.</p>
 */
_UINT32 ChipADS1247::readValue(void)
{
	//Value.
	_UINT32 value = 0;
	//Select chip.
	selectChip();
	//Issue RDATA.
	SPI.transfer(0x12);
	//Read register.
	value |= SPI.transfer(0xFF);
	value <<= 8;
	//Read register.
	value |= SPI.transfer(0xFF);
	value <<= 8;
	//Read register.
	value |= SPI.transfer(0xFF);
	//Unselect chip.
	unselectChip();
	//Return result.
	return value;
}

/**
 * Dump registers.
 *
 * <p>Dump registers.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipADS1247::dumpRegisters(void)
{
	//Print.
	_PRINT0("ChipADS1247::dumpRegisters : show registers !");
	//Select chip.
	selectChip();
	//Dump registers.
	for(int i = 0x00;i <= 0x0b;i ++)
	{
		//Read register.
		_UINT8 value = readRegister(i);
		//Check result.
		switch(i)
		{
		case MUX0_REGISTER:
			_PRINT1("\tMUX0 = 0x%02x",value);
			break;
		case VBIAS_REGISTER:
			_PRINT1("\tVBIAS = 0x%02x",value);
			break;
		case MUX1_REGISTER:
			_PRINT1("\tMUX1 = 0x%02x",value);
			break;
		case SYS0_REGISTER:
			_PRINT1("\tSYS0 = 0x%02x",value);
			break;
		case IDAC0_REGISTER:
			_PRINT1("\tIDAC0 = 0x%02x",value);
			break;
	    case IDAC1_REGISTER:
			_PRINT1("\tIDAC1 = 0x%02x",value);
			break;
		}
    }
	//Unselect chip.
	unselectChip();
}
