////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <Global.h>

#include <I2CChip.h>
#include <ChipAT24C128N.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default construction.
 *
 * @param address Address of chip.
 * @return
 *     <p>No results returned.</p>
 */
ChipAT24C128N::ChipAT24C128N(_UINT8 address)
	: I2CChip(address)
{

}

/**
 * Read data.
 *
 * @param dataAddress Address of data.
 * @param value Data value.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipAT24C128N::readData(_UINT16 dataAddress,_UINT8& value)
{
	//Begin transmission.
	Wire.beginTransmission(getAddress());
	//Address high byte.
	if(!Wire.write((_UINT8)(dataAddress >> 8)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::readData : fail to write high byte of address !");
#endif
		return _FALSE;
	}
	//Address low byte.
	if(!Wire.write((_UINT8)(dataAddress & 0xFF)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::readData : fail to write low byte of address !");
#endif
		return _FALSE;
	}
	//End transmission.
	_UINT8 result = Wire.endTransmission();
	//Check result.
	if(result != 0)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ChipAT24C128N::readData : fail to end transmission (result = %d) !",result);
#endif
		return _FALSE;
	}
	//Request one byte from device address.
	Wire.requestFrom(getAddress(),(_UINT8)1);
	//Check available.
	if(!Wire.available())
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::readData : no data is available !");
#endif
		return _FALSE;
	}
	//Get value.
	value = Wire.read();
	//Return true.
	return _TRUE;
}

/**
 * Write data.
 *
 * @param dataAddress Address of data.
 * @param value Data value.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipAT24C128N::writeData(_UINT16 dataAddress,_UINT8 value)
{
	//Begin transmission.
	Wire.beginTransmission(getAddress());
	//Address high byte.
	if(!Wire.write((_UINT8)(dataAddress >> 8)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::writeData : fail to write high byte of address !");
#endif
		return _FALSE;
	}
	//Address low byte.
	if(!Wire.write((_UINT8)(dataAddress & 0xFF)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::writeData : fail to write low byte of address !");
#endif
		return _FALSE;
	}
	//Write data.
	if(!Wire.write(value))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::writeData : fail to write byte !");
#endif
		return _FALSE;
	}
	//End transmission.
	_UINT8 result = Wire.endTransmission();
	//Check result.
	if(result != 0)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ChipAT24C128N::writeData : fail to end transmission (result = %d) !",result);
#endif
		return _FALSE;
	}
	///////////////////////////////////////
	//
	//Delay.
	//Must delay for a while !!!!!
	delay(10);
	//
	///////////////////////////////////////
	//Return true.
	return _TRUE;
}

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
_BOOL ChipAT24C128N::readPage(_UINT16 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG_CONFIG_MODULE
	_ASSERT(buffer != _NULL && length <= 28);
#endif
	//Begin transmission.
	Wire.beginTransmission(getAddress());
	//Address high byte.
	if(!Wire.write((_UINT8)(dataAddress >> 8)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::readPage : fail to write high byte of address !");
#endif
		return _FALSE;
	}
	//Address low byte.
	if(!Wire.write((_UINT8)(dataAddress & 0xFF)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::readPage : fail to write low byte of address !");
#endif
		return _FALSE;
	}
	//End transmission.
	_UINT8 result = Wire.endTransmission();
	//Check result.
	if(result != 0)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ChipAT24C128N::readPage : fail to end transmission (result = %d) !",result);
#endif
		return _FALSE;
	}
	//Request from bytes.
	Wire.requestFrom(getAddress(),length);
	//Do while.
	for(_UINT16 i = 0;i < length;i ++)
	{
		//Check available.
		if(!Wire.available())
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT0("ChipAT24C128N::readPage : no data is available !");
#endif
			return _FALSE;
		}
		//Read data.
		buffer[i] = Wire.read();
	}
	//Return true.
	return _TRUE;
}

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
_BOOL ChipAT24C128N::writePage(_UINT16 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG_CONFIG_MODULE
	_ASSERT(buffer != _NULL && length <= 28);
#endif
	//Begin transmission.
	Wire.beginTransmission(getAddress());
	//Address high byte.
	if(!Wire.write((_UINT8)(dataAddress >> 8)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::writePage : fail to write high byte of address !");
#endif
		return _FALSE;
	}
	//Address low byte.
	if(!Wire.write((_UINT8)(dataAddress & 0xFF)))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ChipAT24C128N::writePage : fail to write low byte of address !");
#endif
		return _FALSE;
	}
	//Do while.
	for(_UINT16 i = 0;i < length;i ++)
	{
		//Write byte.
		if(!Wire.write(buffer[i]))
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT0("ChipAT24C128N::writePage : fail to write byte !");
#endif
			return _FALSE;
		}
		//Position.
		dataAddress ++;
	}
	//End transmission.
	_UINT8 result = Wire.endTransmission();
	//Check result.
	if(result != 0)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ChipAT24C128N::writePage : fail to end transmission (result = %d) !",result);
#endif
		return _FALSE;
	}
	///////////////////////////////////////
	//
	//Delay.
	//Must delay for a while !!!!!
	delay(10);
	//
	///////////////////////////////////////
	//Return true.
	return _TRUE;
}
