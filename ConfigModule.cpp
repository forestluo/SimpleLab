////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <EEPROM.h>
#include <Global.h>
#include <ConfigModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Null ID
#define NULL_ID												0x0000
//Magic Number
#define MAGIC_NUMBER_ID										0x0001
//Version
#define VERSION_ID											0x0002
//Counter
#define COUNTER_ID											0x0003
//Device Type
#define DEVICE_TYPE_ID										0x0101
//ADS1247 Mode
#define ADS1247_MODE_ID										0x0201
//Sample Table
#define SAMPLE_TABLE_ID										0x0301

//Sample Table Size
#define SAMPLE_TABLE_SIZE(n) \
	(sizeof(_UINT8) + sizeof(_UINT16) + 2 * sizeof(_INT32) + (n) * sizeof(_FLOAT))

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
ConfigModule::~ConfigModule(void)
{

}

/**
 * Default construction.
 *
 * @param chipAT24C128NAddress Address for chip AT24C128N.
 * @return
 *     <p>No results returned.</p>
 */
ConfigModule::ConfigModule(_UINT8 chipAT24C128NAddress)
	: chipAT24C128N(chipAT24C128NAddress)
{
	//Clear flags.
	flags = 0x00;

	//Read magic number.
	_UINT32 magicNumber = readMagicNumber();
	//_UINT32 magicNumber = 0;
	//Check result.
	if(magicNumber == _MAGIC_NUMBER)
	{
		//Add counter.
		writeCounter(readCounter() + 1);
	}
	else
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::ConfigModule : invalid magic number !");
		_PRINT0("The internal E2PROM will be erased and rebuild automatically !");
#endif
		//Write magic number.
		writeMagicNumber(_MAGIC_NUMBER);
		//Write counter.
		writeCounter(0);
		//Write MAC address.
		writeMACAddress(0x005056000000LL |
			(((_UINT64)random(255)) << 16) | (((_UINT64)random(255)) << 8) | ((_UINT64)random(255)));
	}
}

/**
 * Read uint8.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT8 ConfigModule::readUint8(_UINT16 dataAddress)
{
	//Value.
	_UINT8 value = 0;
	//Add address.
	//dataAddress += 0;
	//Try to read value.
	return chipAT24C128N.readData(dataAddress,value) ? value : -1;
}

/**
 * Read uint16.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT16 ConfigModule::readUint16(_UINT16 dataAddress)
{
	//Value.
	_UINT16 value = 0;
	//Add address.
	//dataAddress += 0;
	//Add bytes.
	value |= ((_UINT16)readUint8(dataAddress)) << 8;
	//Add address.
	dataAddress += sizeof(_UINT8);
	//Add bytes.
	value |= (_UINT16)readUint8(dataAddress);
	//Return result.
	return value;
}

/**
 * Read uint32.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT32 ConfigModule::readUint32(_UINT16 dataAddress)
{
	//Value.
	_UINT32 value = 0;
	//Add address.
	//dataAddress += 0;
	//Add bytes.
	value |= ((_UINT32)readUint16(dataAddress)) << 16;
	//Add address.
	dataAddress += sizeof(_UINT16);
	//Add bytes.
	value |= (_UINT32)readUint16(dataAddress);
	//Return result.
	return value;
}

/**
 * Read uint64.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT64 ConfigModule::readUint64(_UINT16 dataAddress)
{
	//Value.
	_UINT64 value = 0;
	//Add address.
	//dataAddress += 0;
	//Add bytes.
	value |= ((_UINT64)readUint32(dataAddress)) << 32;
	//Add address.
	dataAddress += sizeof(_UINT32);
	//Add bytes.
	value |= (_UINT64)readUint32(dataAddress);
	//Return result.
	return value;
}

/**
 * Write uint8.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeUint8(_UINT16 dataAddress,_UINT8 value)
{
	//Add address.
	//dataAddress += 0;
	//Write byte.
	return chipAT24C128N.writeData(dataAddress,value);
}

/**
 * Write uint16.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeUint16(_UINT16 dataAddress,_UINT16 value)
{
	//Add address.
	//dataAddress += 0;
	//Write high byte.
	if(!writeUint8(dataAddress,(value >> 8) & 0xFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint16 : fail to write !");
#endif
		return _FALSE;
	}
	//Add address.
	dataAddress += sizeof(_UINT8);

	//Write low byte.
	if(!writeUint8(dataAddress,value & 0xFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint16 : fail to write !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write uint32.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeUint32(_UINT16 dataAddress,_UINT32 value)
{
	//Add address.
	//dataAddress += 0;
	//Write high part.
	if(!writeUint16(dataAddress,(value >> 16) & 0xFFFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint32 : fail to write !");
#endif
		return _FALSE;
	}
	//Add address.
	dataAddress += sizeof(_UINT16);
	//Write low part.
	if(!writeUint16(dataAddress,value & 0xFFFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint32 : fail to write !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write uint64.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeUint64(_UINT16 dataAddress,_UINT64 value)
{
	//Add address.
	//dataAddress += 0;
	//Write high part.
	if(!writeUint32(dataAddress,(value >> 32) & 0xFFFFFFFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint64 : fail to write !");
#endif
		return _FALSE;
	}
	//Add address.
	dataAddress += sizeof(_UINT32);
	//Write low part.
	if(!writeUint32(dataAddress,value & 0xFFFFFFFF))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeUint64 : fail to write !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Read null id.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Return true, if it is null id.</p>
 */
_BOOL ConfigModule::readNullID(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[4];
	//Clear buffer.
	memset(buffer,0,4 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,4))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readNullID : fail to read data !");
#endif
		return _FALSE;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != NULL_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readNullID : invalid id(0x%04x) !",dataID);
#endif
		return _FALSE;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != 0)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readNullID : invalid length(%d) !",dataLength);
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Read magic number.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Magic number.</p>
 */
_UINT32 ConfigModule::readMagicNumber(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readMagicNumber : fail to read data !");
#endif
		return -1;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != MAGIC_NUMBER_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readMagicNumber : invalid id(0x%04x) !",dataID);
#endif
		return -1;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != sizeof(_UINT32))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readMagicNumber : invalid length(%d) !",dataLength);
#endif
		return -1;
	}
	//Return result.
	return (((_UINT32)buffer[4]) << 24) | (((_UINT32)buffer[5]) << 16) | (((_UINT32)buffer[6]) << 8) | (_UINT32)buffer[7];
}

/**
 * Read version.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Version.</p>
 */
_UINT16 ConfigModule::readVersion(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[6];
	//Clear buffer.
	memset(buffer,0,6 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,6))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readVersion : fail to read data !");
#endif
		return -1;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != VERSION_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readVersion : invalid id(0x%04x) !",dataID);
#endif
		return -1;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != 2 * sizeof(_UINT8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readVersion : invalid length(%d) !",dataLength);
#endif
		return -1;
	}
	//Return result.
	return (((_UINT16)buffer[4]) << 8) | (_UINT16)buffer[5];
}

/**
 * Read counter.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Counter.</p>
 */
_UINT32 ConfigModule::readCounter(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readCounter : fail to read data !");
#endif
		return -1;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != COUNTER_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readCounter : invalid id(0x%04x) !",dataID);
#endif
		return -1;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != sizeof(_UINT32))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readCounter : invalid length(%d) !",dataLength);
#endif
		return -1;
	}
	//Return result.
	return (((_UINT32)buffer[4]) << 24) | (((_UINT32)buffer[5]) << 16) | (((_UINT32)buffer[6]) << 8) | (_UINT32)buffer[7];
}

/**
 * Read device type.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Device type.</p>
 */
_UINT32 ConfigModule::readDeviceType(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readDeviceType : fail to read data !");
#endif
		return -1;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != DEVICE_TYPE_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readDeviceType : invalid id(0x%04x) !",dataID);
#endif
		return -1;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != sizeof(_UINT32))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readDeviceType : invalid length(%d) !",dataLength);
#endif
		return -1;
	}
	//Return result.
	return (((_UINT32)buffer[4]) << 24) | (((_UINT32)buffer[5]) << 16) | (((_UINT32)buffer[6]) << 8) | (_UINT32)buffer[7];
}

/**
 * Read ads1247 mode.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>ADS1247 mode.</p>
 */
_UINT64 ConfigModule::readADS1247Mode(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[10];
	//Clear buffer.
	memset(buffer,0,10 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,10))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readADS1247Mode : fail to read data !");
#endif
		return -1LL;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != ADS1247_MODE_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readADS1247Mode : invalid id(0x%04x) !",dataID);
#endif
		return -1LL;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength != 6 * sizeof(_UINT8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readADS1247Mode : invalid length(%d) !",dataLength);
#endif
		return -1LL;
	}
	//Return value.
	return (((_UINT64)buffer[4] & 0xFF) << 40) | (((_UINT64)buffer[5] & 0xFF) << 32) |
		   (((_UINT64)buffer[6] & 0xFF) << 24) | (((_UINT64)buffer[7] & 0xFF) << 16) | (((_UINT64)buffer[8] & 0xFF) << 8) | ((_UINT64)buffer[9] & 0xFF);
}

/**
 * Read sample table.
 *
 * @param dataAddress Address of data.
 * @param table Sample table.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::readSampleTable(_UINT16 dataAddress,SampleTable& table)
{
	//Page buffer.
	_BYTE buffer[4];
	//Clear buffer.
	memset(buffer,0,4 * sizeof(_BYTE));

	//Add address.
	//dataAddress += 0;
	//Read page from e2prom.
	if(!chipAT24C128N.readPage(dataAddress,buffer,4))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::readSampleTable : fail to read data !");
#endif
		return _FALSE;
	}
	//Get data id.
	_UINT16 dataID = (((_UINT16)buffer[0]) << 8) | (_UINT16)buffer[1];
	//Check result.
	if(dataID != SAMPLE_TABLE_ID)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readSampleTable : invalid id(0x%04x) !",dataID);
#endif
		return _FALSE;
	}
	//Get data length.
	_UINT16 dataLength = (((_UINT16)buffer[2]) << 8) | (_UINT16)buffer[3];
	//Check result.
	if(dataLength < 2 * sizeof(_FLOAT))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readSampleTable : invalid length(%d) !",dataLength);
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_SHORT);

	//Read type.
	_UINT8 type = readUint8(dataAddress);
	//Check result.
	if(type <= 0 || type > 3)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readSampleTable : invalid type(%d) !",type);
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += sizeof(_UINT8);
#ifdef _DEBUG_CONFIG_MODULE
	//Print.
	_PRINT1("ConfigModule::readSampleTable : table(type = %d) was found !",type);
#endif
	
	//Read size.
	_UINT16 size = readUint16(dataAddress);
	//Check result.
	if(size <  2 || size > 256)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT1("ConfigModule::readSampleTable : invalid size(%d) !",size);
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += sizeof(_UINT16);
#ifdef _DEBUG_CONFIG_MODULE
	//Print.
	_PRINT1("ConfigModule::readSampleTable : table size has %d parameters !",size);
#endif

	//Check result.
	if(type == UNIFORM_FITTING_TABLE)
	{
		//Check size.
		if(size < 2 || size > 256)
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT2("ConfigModule::readSampleTable : invalid size(%d) of table(%d) !",size,type);
#endif
			return _FALSE;
		}
	}
	else if(type == LINEAR_FITTING_TABLE)
	{
		//Check size.
		if(size < 4 || (size % 2) != 0)
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT2("ConfigModule::readSampleTable : invalid size(%d) of table(%d) !",size,type);
#endif
			return _FALSE;
		}
	}
	else if(type == GAUSSIAN_FITTING_TABLE)
	{
		//Check size.
		if(size < 3 || (size % 3) != 0)
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT2("ConfigModule::readSampleTable : invalid size(%d) of table(%d) !",size,type);
#endif
			return _FALSE;
		}
	}
	//Read minimum index.
	_INT32 minIndex = (_INT32)readUint32(dataAddress);
	//Add data address.
	dataAddress += sizeof(_INT32);
	//Read maximum index.
	_INT32 maxIndex = (_INT32)readUint32(dataAddress);
	//Add data address.
	dataAddress += sizeof(_INT32);
	//Check result.
	if((minIndex >= maxIndex) || maxIndex > (_INT32)0x007FFFFF || minIndex < (_INT32)0xFF800001)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT2("ConfigModule::readSampleTable : invalid min index(%ld) and max index(%ld)",minIndex,maxIndex);
#endif
		return _FALSE;
	}

	//Set type.
	table.setType(type);
	//Set size.
	table.setSize(size);
	//Set min index.
	table.setMinIndex(minIndex);
	//Set max index.
	table.setMaxIndex(maxIndex);
	//Do while.
	for(_UINT16 i = 0;i < size;i ++)
	{
		//Read value.
		_UINT32 value = readUint32(dataAddress);
		//Add data address.
		dataAddress += sizeof(_FLOAT); table.setParameterValue(i,*((_FLOAT *)&value));
	}
	//Check type.
	if(type == LINEAR_FITTING_TABLE)
	{
		//Check value.
		if(minIndex != (_INT32)table.getParameterValue(0) ||
			maxIndex != (_INT32)table.getParameterValue(size - 2))
		{
#ifdef _DEBUG_CONFIG_MODULE
			//Print.
			_PRINT2("ConfigModule::readSampleTable : invalid min index(%ld) and max index(%ld)",minIndex,maxIndex);
#endif
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

/**
 * Write null id.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeNullID(_UINT16 dataAddress)
{
	//Page buffer.
	_BYTE buffer[4];
	//Clear buffer.
	memset(buffer,0,4 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(NULL_ID >> 8);
	buffer[1] = (_BYTE)(NULL_ID >> 0);
	//Get data length.
	_UINT16 length = 0;
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,4))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeNullID : fail to write null id !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write magic number.
 *
 * @param dataAddress Address of data.
 * @param magicNumber Magic number.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeMagicNumber(_UINT16 dataAddress,_UINT32 magicNumber)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(MAGIC_NUMBER_ID >> 8);
	buffer[1] = (_BYTE)(MAGIC_NUMBER_ID >> 0);
	//Get data length.
	_UINT16 length = sizeof(_UINT32);
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Set data value.
	buffer[4] = (_BYTE)(magicNumber >> 24);
	buffer[5] = (_BYTE)(magicNumber >> 16);
	buffer[6] = (_BYTE)(magicNumber >> 8);
	buffer[7] = (_BYTE)(magicNumber >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeMagicNumber : fail to write magic number !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write version.
 *
 * @param dataAddress Address of data.
 * @param version Format version.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeVersion(_UINT16 dataAddress,_UINT16 version)
{
	//Page buffer.
	_BYTE buffer[6];
	//Clear buffer.
	memset(buffer,0,6 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(VERSION_ID >> 8);
	buffer[1] = (_BYTE)(VERSION_ID >> 0);
	//Get data length.
	_UINT16 length = sizeof(_UINT16);
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Set data value.
	buffer[4] = (_BYTE)(version >> 8);
	buffer[5] = (_BYTE)(version >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,6))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeVersion : fail to write version !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write counter.
 *
 * @param dataAddress Address of data.
 * @param counter Counter.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeCounter(_UINT16 dataAddress,_UINT32 counter)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(COUNTER_ID >> 8);
	buffer[1] = (_BYTE)(COUNTER_ID >> 0);
	//Get data length.
	_UINT16 length = sizeof(_UINT32);
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Set data value.
	buffer[4] = (_BYTE)(counter >> 24);
	buffer[5] = (_BYTE)(counter >> 16);
	buffer[6] = (_BYTE)(counter >> 8);
	buffer[7] = (_BYTE)(counter >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeCounter : fail to write counter !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write device type.
 *
 * @param dataAddress Address of data.
 * @param deviceType Device type.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeDeviceType(_UINT16 dataAddress,_UINT32 deviceType)
{
	//Page buffer.
	_BYTE buffer[8];
	//Clear buffer.
	memset(buffer,0,8 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(DEVICE_TYPE_ID >> 8);
	buffer[1] = (_BYTE)(DEVICE_TYPE_ID >> 0);
	//Get data length.
	_UINT16 length = sizeof(_UINT32);
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Set data value.
	buffer[4] = (_BYTE)(deviceType >> 24);
	buffer[5] = (_BYTE)(deviceType >> 16);
	buffer[6] = (_BYTE)(deviceType >> 8);
	buffer[7] = (_BYTE)(deviceType >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,8))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeDeviceType : fail to write device type !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write ADS1247 mode.
 *
 * @param dataAddress Address of data.
 * @param ads1247Mode ADS1247 mode.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeADS1247Mode(_UINT16 dataAddress,_UINT64 ads1247Mode)
{
	//Page buffer.
	_BYTE buffer[10];
	//Clear buffer.
	memset(buffer,0,10 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(ADS1247_MODE_ID >> 8);
	buffer[1] = (_BYTE)(ADS1247_MODE_ID >> 0);
	//Get data length.
	_UINT16 length = 6 * sizeof(_UINT8);
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Set data value.
	buffer[4] = (_BYTE)(ads1247Mode >> 40);
	buffer[5] = (_BYTE)(ads1247Mode >> 32);
	buffer[6] = (_BYTE)(ads1247Mode >> 24);
	buffer[7] = (_BYTE)(ads1247Mode >> 16);
	buffer[8] = (_BYTE)(ads1247Mode >> 8);
	buffer[9] = (_BYTE)(ads1247Mode >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,10))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeADS1247Mode : fail to write ADS1247 mode !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Write sample table.
 *
 * @param dataAddress Address of data.
 * @param table Sample table.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::writeSampleTable(_UINT16 dataAddress,SampleTable& table)
{
	//Page buffer.
	_BYTE buffer[4];
	//Clear buffer.
	memset(buffer,0,4 * sizeof(_BYTE));

	//Set data id.
	buffer[0] = (_BYTE)(SAMPLE_TABLE_ID >> 8);
	buffer[1] = (_BYTE)(SAMPLE_TABLE_ID >> 0);
	//Get data length.
	_UINT16 length = SAMPLE_TABLE_SIZE(table.getSize());
	//Set data length.
	buffer[2] = (_BYTE)(length >> 8);
	buffer[3] = (_BYTE)(length >> 0);
	//Write page.
	if(!chipAT24C128N.writePage(dataAddress,buffer,4))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::writeSampleTable : fail to write sample table !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_SHORT);

	//Write type.
	writeUint8(dataAddress,(_UINT8)table.getType());
	//Add data address.
	dataAddress += sizeof(_UINT8);
	//Write size.
	writeUint16(dataAddress,(_UINT8)table.getSize());
	//Add data address.
	dataAddress += sizeof(_UINT16);
	//Write minimum index.
	writeUint32(dataAddress,(_UINT32)table.getMinIndex());
	//Add data address.
	dataAddress += sizeof(_UINT32);
	//Write maximum index.
	writeUint32(dataAddress,(_UINT32)table.getMaxIndex());
	//Add data address.
	dataAddress += sizeof(_UINT32);
	//Do while.
	for(_UINT8 i = 0;i < table.getSize();i ++)
	{
		//Get value.
		_FLOAT value = table.getParameterValue(i);
		//Write value.
		writeUint32(dataAddress,*((_UINT32 *)&value)); dataAddress += sizeof(_FLOAT);
	}
}

/**
 * Read magic number.
 *
 * <p>Read magic number from internal E2PROM.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Magic number.</p>
 */
_UINT32 ConfigModule::readMagicNumber(void)
{
	//Return result.
	return (((_UINT32)EEPROM.read(0)) << 24) | (((_UINT32)EEPROM.read(1)) << 16) | (((_UINT32)EEPROM.read(2)) << 8) | (_UINT32)EEPROM.read(3);
}

/**
 * Read magic number.
 *
 * <p>Read counter from internal E2PROM.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Counter.</p>
 */
_UINT32 ConfigModule::readCounter(void)
{
	//Return result.
	return (((_UINT32)EEPROM.read(4)) << 24) | (((_UINT32)EEPROM.read(5)) << 16) | (((_UINT32)EEPROM.read(6)) << 8) | (_UINT32)EEPROM.read(7);
}

/**
 * Write magic number.
 *
 * <p>Write magic number into internal E2PROM.</p>
 *
 * @param magicNumber Magic number.
 * @return
 *     <p>No results returned.</p>
 */
void ConfigModule::writeMagicNumber(_UINT32 magicNumber)
{
	//Write value.
	EEPROM.write(0,(_UINT8)(magicNumber >> 24));
	//Write value.
	EEPROM.write(1,(_UINT8)(magicNumber >> 16));
	//Write value.
	EEPROM.write(2,(_UINT8)(magicNumber >> 8));
	//Write value.
	EEPROM.write(3,(_UINT8)(magicNumber >> 0));
}

/**
 * Write counter.
 *
 * <p>Write counter into internal E2PROM.</p>
 *
 * @param counter Counter.
 * @return
 *     <p>No results returned.</p>
 */
void ConfigModule::writeCounter(_UINT32 counter)
{
	//Write value.
	EEPROM.write(4,(_UINT8)(counter >> 24));
	//Write value.
	EEPROM.write(5,(_UINT8)(counter >> 16));
	//Write value.
	EEPROM.write(6,(_UINT8)(counter >> 8));
	//Write value.
	EEPROM.write(7,(_UINT8)(counter >> 0));
}

/**
 * Read MAC address.
 *
 * <p>Read MAC address from internal E2PROM.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>MAC address.</p>
 */
_UINT64 ConfigModule::readMACAddress(void)
{
	//Return value.
	return (((_UINT64)EEPROM.read(8)) << 40) | (((_UINT64)EEPROM.read(9)) << 32) |
		   (((_UINT64)EEPROM.read(10)) << 24) | (((_UINT64)EEPROM.read(11)) << 16) | (((_UINT64)EEPROM.read(12)) << 8) | ((_UINT64)EEPROM.read(13));
}

/**
 * Write MAC address.
 *
 * <p>Write MAC address into internal E2PROM.</p>
 *
 * @param macAddress MAC address.
 * @return
 *     <p>No results returned.</p>
 */
void ConfigModule::writeMACAddress(_UINT64 macAddress)
{
	//Write value.
	EEPROM.write(8,(_UINT8)(macAddress >> 40));
	//Write value.
	EEPROM.write(9,(_UINT8)(macAddress >> 32));
	//Write value.
	EEPROM.write(10,(_UINT8)(macAddress >> 24));
	//Write value.
	EEPROM.write(11,(_UINT8)(macAddress >> 16));
	//Write value.
	EEPROM.write(12,(_UINT8)(macAddress >> 8));
	//Write value.
	EEPROM.write(13,(_UINT8)(macAddress >> 0));
}

/**
 * Invalidate.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ConfigModule::invalidate(void)
{
	//Clear flag.
	flags &= ~0x01;
}

/**
 * Whether available.
 *
 * <p>It depends on flags.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if config is available.</p>
 */
_BOOL ConfigModule::isAvailable(void)
{
	//Return result.
	return ((flags & 0x01) == 0x01) ? _TRUE : _FALSE;
}

/**
 * Check version.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if version is correct.</p>
 */
_BOOL ConfigModule::checkVersion(_UINT16 version)
{
	//Data address.
	_UINT16 dataAddress = 0;
	//Try to read magic number.
	if(readMagicNumber(dataAddress) != _MAGIC_NUMBER)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::checkVersion : fail to check magic number !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to read version.
	if(readVersion(dataAddress) != version)
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::checkVersion : fail to check version !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT16);
	//Return true.
	return _TRUE;
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ConfigModule::dumpConfig(void)
{
	//Print.
	_PRINT0("ConfigModule::dumpConfig : internal values !");
	//Try to read magic number.
	_PRINT1("\tmagicNumber = 0x%08lx",readMagicNumber());
	//Try to read counter.
	_PRINT1("\tcounter = %lu",readCounter());
	//MAC address.
	_UINT64 macAddress = readMACAddress();
	//Try to read ads1247 mode.
	_PRINT6("\tmacAddress = %02x-%02x-%02x-%02x-%02x-%02x",
		(_UINT8)(macAddress >> 40),(_UINT8)(macAddress >> 32),(_UINT8)(macAddress >> 24),(_UINT8)(macAddress >> 16),(_UINT8)(macAddress >> 8),(_UINT8)macAddress);

	//Data address.
	_UINT16 dataAddress = 0;
	//Print.
	_PRINT0("ConfigModule::dumpConfig : external values !");

	//Try to read magic number.
	_PRINT1("\tmagicNumber = 0x%08lx",
		readMagicNumber(dataAddress));
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to read version.
	_PRINT1("\tversion = 0x%04x",
		readVersion(dataAddress));
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT16);

	//Try to read counter.
	_PRINT1("\tcounter = %lu",
		readCounter(dataAddress));
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to read device type.
	_PRINT1("\tdeviceType = 0x%08lx",
		readDeviceType(dataAddress));
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);
	
	//ADS1247 mode.
	_UINT64 ads1247Mode = readADS1247Mode(dataAddress);
	//Try to read ads1247 mode.
	_PRINT2("\tads1247Mode = 0x%04x%08lx",
		(_UINT16)(ads1247Mode >> 32),(_UINT32)ads1247Mode);
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + 6 * sizeof(_UINT8);
}

/**
 * Format config.
 *
 * <p>Use default config to format.</p>
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ConfigModule::formatConfig(void)
{
	//Data address.
	_UINT16 dataAddress = 0;

	//Try to write magic number.
	if(!writeMagicNumber(dataAddress,_MAGIC_NUMBER))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write magic number !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to write version.
	if(!writeVersion(dataAddress,_CURRENT_VERSION))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write version !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT16);

	//Try to write counter.
	if(!writeCounter(dataAddress,0))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write counter !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to write device type.
	if(!writeDeviceType(dataAddress,(_UINT32)-1))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write device type !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);
	
	//Try to write ads1247 mode.
	if(!writeADS1247Mode(dataAddress,(_UINT64)0))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write ads1247 mode !");
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + 6 * sizeof(_UINT8);

	//Default table.
	SampleTable table;
	//Set type.
	table.setType(UNIFORM_FITTING_TABLE);
	//Set size.
	table.setSize(2);
	//Set min index.
	table.setMinIndex((_INT32)0xFF800001);
	//Set max index.
	table.setMaxIndex((_INT32)0x007FFFFF);
	//Set real value.
	table.setParameterValue(0,0.0F);
	table.setParameterValue(1,1048576.0F);
	//Try to write table.
	if(!writeSampleTable(dataAddress,table))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write sample table !");
#endif
	}
	//Add data address.
	dataAddress += 2* sizeof(_UINT16) + SAMPLE_TABLE_SIZE(table.getSize());

	//Try to write null id.
	if(!writeNullID(dataAddress))
	{
#ifdef _DEBUG_CONFIG_MODULE
		//Print.
		_PRINT0("ConfigModule::formatConfig : fail to write null id !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Load config.
 *
 * @param deviceType Type of device.
 * @param ads1247Mode Mode of ADS1247.
 * @param sampleTable Sample table.
 * @return
 *     <p>Sample table.</p>
 */
_BOOL ConfigModule::loadConfig(_UINT32& deviceType,_UINT64& ads1247Mode,SampleTable& sampleTable)
{
	//Clear flags.
	flags &= ~0x01;
	//Data address.
	_UINT16 dataAddress = 0;

	//Try to read magic number.
	_UINT32 magicNumber = readMagicNumber(dataAddress);
	//Check result.
	if(magicNumber != _MAGIC_NUMBER)
	{
#ifdef _DEBUG_CONFIG_MODULE
		_PRINT1("ConfigModule::loadConfig : invalid magic number(0x%08lx) !",magicNumber);
#endif
		return _FALSE;
	}
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to read version.
	_UINT16 version = readVersion(dataAddress);
	//Check result.
	if(version != _CURRENT_VERSION)
	{
#ifdef _DEBUG_CONFIG_MODULE
		_PRINT1("ConfigModule::loadConfig : invalid version(0x%04x) !",version);
#endif
		return _FALSE;
	}
#ifdef _DEBUG_CONFIG_MODULE
	_PRINT1("ConfigModule::loadConfig : version(0x%04x) !",version);
#endif
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT16);

	//Try to read counter.
	_UINT32 counter = readCounter(dataAddress);
#ifdef _DEBUG_CONFIG_MODULE
	_PRINT1("ConfigModule::loadConfig : counter(0x%08lx) !",counter);
#endif
	//Write it back into config.
	writeCounter(dataAddress,counter + 1);
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//Try to read device type.
	deviceType = readDeviceType(dataAddress);
#ifdef _DEBUG_CONFIG_MODULE
	_PRINT1("ConfigModule::loadConfig : device type(0x%08lx) !",deviceType);
#endif
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + sizeof(_UINT32);

	//ADS1247 mode.
	ads1247Mode = readADS1247Mode(dataAddress);
#ifdef _DEBUG_CONFIG_MODULE
	_PRINT2("ConfigModule::loadConfig : ADS1247 mode(0x%04x%08lx) !",
					(_UINT16)(ads1247Mode >> 32),(_UINT32)ads1247Mode);
#endif
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + 6 * sizeof(_UINT8);

	//Check result.
	if(!readSampleTable(dataAddress,sampleTable))
	{
#ifdef _DEBUG_CONFIG_MODULE
		_PRINT0("ConfigModule::loadConfig : fail to read sample table !");
#endif
		return _FALSE;
	}
	//Set flag.
	flags |= 0x01;
#ifdef _DEBUG_CONFIG_MODULE
	_PRINT0("ConfigModule::loadConfig : sample table was loaded !");
#endif
	//Add data address.
	dataAddress += 2 * sizeof(_UINT16) + SAMPLE_TABLE_SIZE(sampleTable.getSize());

	//Check null id.
	if(!readNullID(dataAddress))
	{
#ifdef _DEBUG_CONFIG_MODULE
		_PRINT0("ConfigModule::loadConfig : fail to read end of config !");
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
