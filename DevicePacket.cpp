////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Checksum16.h>
#include <DevicePacket.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Commands.
 */
const _UINT8 DevicePacket::DEVICE_STATUS					= 0x01;
const _UINT8 DevicePacket::DEVICE_CONTROL					= 0x02;
const _UINT8 DevicePacket::DEVICE_RELEASE					= 0x03;
const _UINT8 DevicePacket::DEVICE_READ_DATA					= 0x04;
const _UINT8 DevicePacket::DEVICE_WRITE_DATA				= 0x05;
const _UINT8 DevicePacket::DEVICE_READ_STORAGE				= 0x06;
const _UINT8 DevicePacket::DEVICE_WRITE_STORAGE				= 0x07;
const _UINT8 DevicePacket::DEVICE_WIRELESS_STATUS			= 0x81;
const _UINT8 DevicePacket::DEVICE_WIRELESS_CONTROL			= 0x82;
const _UINT8 DevicePacket::DEVICE_WIRELESS_RELEASE			= 0x83;
const _UINT8 DevicePacket::DEVICE_WIRELESS_READ_DATA		= 0x84;
const _UINT8 DevicePacket::DEVICE_WIRELESS_WRITE_DATA		= 0x85;

/**
 * Get wireless address.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Wireless address.</p>
 */
_UINT64 DevicePacket::getWirelessAddress(void)
{
	//Address.
	_UINT64 address = 0LL;
	//Get wireless address.
	address |= (body.dwp.wirelessAddress[0] & 0xFFLL) << 40;
	address |= (body.dwp.wirelessAddress[1] & 0xFFLL) << 32;
	address |= (body.dwp.wirelessAddress[2] & 0xFFLL) << 24;
	address |= (body.dwp.wirelessAddress[3] & 0xFFLL) << 16;
	address |= (body.dwp.wirelessAddress[4] & 0xFFLL) <<  8;
	address |= (body.dwp.wirelessAddress[5] & 0xFFLL) <<  0;
	//Return result.
	return address;
}

/**
 * Set wireless address.
 *
 * @param address Address.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::setWirelessAddress(_UINT64 address)
{
	//Set wireless address.
	body.dwp.wirelessAddress[0] = (_UINT8)(address >> 40);
	body.dwp.wirelessAddress[1] = (_UINT8)(address >> 32);
	body.dwp.wirelessAddress[2] = (_UINT8)(address >> 24);
	body.dwp.wirelessAddress[3] = (_UINT8)(address >> 16);
	body.dwp.wirelessAddress[4] = (_UINT8)(address >>  8);
	body.dwp.wirelessAddress[5] = (_UINT8)(address >>  0);
}

/**
 * Make packet.
 *
 * <p>Make packet before transmission.</p>
 *
 * @param packet Device packet.
 * @return
 *     <p>Size of packet.</p>
 */
_UINT16 DevicePacket::makePacket(DevicePacket& packet)
{
	//Set checksum16.
	packet.checksum16 = 0x0000;
	//Check version.
	if(packet.version != _PROTOCOL_VERSION) return 0;
	//Check command.
	if(packet.command == DevicePacket::DEVICE_STATUS)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_STATUS_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.ds.deviceType = SWAP32(packet.body.ds.deviceType);
		//Convert to network order.
		packet.body.ds.sampleRate = SWAP16(packet.body.ds.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_CONTROL)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_CONTROL_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dc.sampleRate = SWAP16(packet.body.dc.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_RELEASE)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_RELEASE_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dr.sampleRate = SWAP16(packet.body.dr.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_READ_DATA &&
		(packet.body.drd.deviceValue.sampleCount >= 0 && packet.body.drd.deviceValue.sampleCount <= 16))
	{
		//Get total length.
		_UINT16 totalLength = DEVICE_READ_DATA_PACKET_SIZE(packet.body.drd.deviceValue.sampleCount);
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Do while.
		for(_UINT8 i = 0;i < packet.body.drd.deviceValue.sampleCount;i ++)
		{
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].timestamp =
				SWAP32(packet.body.drd.deviceValue.sampleValues[i].timestamp);
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].sequenceID =
				SWAP16(packet.body.drd.deviceValue.sampleValues[i].sequenceID);
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].pinValue =
				SWAP32(packet.body.drd.deviceValue.sampleValues[i].pinValue);
			//Check result.
			if(packet.body.drd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_SHORT_TYPE)
			{
				//Convert to network order.
				packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue =
					SWAP16(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(packet.body.drd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_FLOAT_TYPE ||
					packet.body.drd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_INTEGER_TYPE)
			{
				//Convert to network order.
				packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue =
					SWAP32(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WRITE_DATA &&
		(packet.body.dwd.deviceValue.sampleCount >= 0 && packet.body.dwd.deviceValue.sampleCount <= 16))
	{
		//Get total length.
		_UINT16 totalLength = DEVICE_WRITE_DATA_PACKET_SIZE(packet.body.dwd.deviceValue.sampleCount);
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Do while.
		for(_UINT8 i = 0;i < packet.body.dwd.deviceValue.sampleCount;i ++)
		{
			//Convert to network order.
			packet.body.dwd.deviceValue.sampleValues[i].timestamp =
				SWAP32(packet.body.dwd.deviceValue.sampleValues[i].timestamp);
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].sequenceID =
				SWAP16(packet.body.dwd.deviceValue.sampleValues[i].sequenceID);
			//Convert to network order.
			packet.body.dwd.deviceValue.sampleValues[i].pinValue =
				SWAP32(packet.body.dwd.deviceValue.sampleValues[i].pinValue);
			//Check result.
			if(packet.body.dwd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_SHORT_TYPE)
			{
				//Convert to network order.
				packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue =
					SWAP16(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(packet.body.dwd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_FLOAT_TYPE ||
					packet.body.dwd.deviceValue.sampleValues[i].generalValue.valueType == GENERAL_INTEGER_TYPE)
			{
				//Convert to network order.
				packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue =
					SWAP32(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_READ_STORAGE)
	{
		//Get value type.
		_UINT8 valueType = packet.body.drs.generalValue.valueType;
		//Get length.
		_UINT32 length = (valueType != GENERAL_LENGTH_TYPE) ?
							0 : packet.body.drs.generalValue.dataValue.length;
		//Set total length.
		_UINT16 totalLength = DEVICE_READ_STORAGE_PACKET_SIZE + length;
#ifdef _DEBUG
		_ASSERT(totalLength <= 255);
#endif
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.drs.offset = SWAP32(packet.body.drs.offset);
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.drs.generalValue.dataValue.shortValue =
				SWAP16(packet.body.drs.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_LENGTH_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.drs.generalValue.dataValue.integerValue =
				SWAP32(packet.body.drs.generalValue.dataValue.integerValue);
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return length.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WRITE_STORAGE)
	{
		//Get value type.
		_UINT8 valueType = packet.body.dws.generalValue.valueType;
		//Get length.
		_UINT32 length = (valueType != GENERAL_LENGTH_TYPE) ?
							0 : packet.body.dws.generalValue.dataValue.length;
		//Set total length.
		_UINT16 totalLength = DEVICE_WRITE_STORAGE_PACKET_SIZE + length;
#ifdef _DEBUG
		_ASSERT(totalLength <= 255);
#endif
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dws.offset = SWAP32(packet.body.dws.offset);
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dws.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dws.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_LENGTH_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dws.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dws.generalValue.dataValue.integerValue);
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return length.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_STATUS)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_WIRELESS_STATUS_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dwps.deviceType = SWAP32(packet.body.dwps.deviceType);
		//Convert to network order.
		packet.body.dwps.sampleRate = SWAP16(packet.body.dwps.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return length.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_CONTROL)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_WIRELESS_CONTROL_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dwpc.sampleRate = SWAP16(packet.body.dwpc.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_RELEASE)
	{
		//Set total length.
		_UINT16 totalLength = DEVICE_WIRELESS_RELEASE_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dwpr.sampleRate = SWAP16(packet.body.dwpr.sampleRate);
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_READ_DATA)
	{
		//Get total length.
		_UINT16 totalLength = DEVICE_WIRELESS_READ_DATA_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dwprd.sampleValue.timestamp =
			SWAP32(packet.body.dwprd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwprd.sampleValue.sequenceID =
			SWAP16(packet.body.dwprd.sampleValue.sequenceID);
		//Convert to network order.
		packet.body.dwprd.sampleValue.pinValue =
			SWAP32(packet.body.dwprd.sampleValue.pinValue);
		//Check result.
		if(packet.body.dwprd.sampleValue.generalValue.valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(packet.body.dwprd.sampleValue.generalValue.valueType == GENERAL_FLOAT_TYPE ||
				packet.body.dwprd.sampleValue.generalValue.valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue);
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_WRITE_DATA)
	{
		//Get total length.
		_UINT16 totalLength = DEVICE_WIRELESS_WRITE_DATA_PACKET_SIZE;
		//Convert to network order.
		packet.totalLength = SWAP16(totalLength);
		//Convert to network order.
		packet.body.dwpwd.sampleValue.timestamp =
			SWAP32(packet.body.dwpwd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwpwd.sampleValue.sequenceID =
			SWAP16(packet.body.dwpwd.sampleValue.sequenceID);
		//Convert to network order.
		packet.body.dwpwd.sampleValue.pinValue =
			SWAP32(packet.body.dwpwd.sampleValue.pinValue);
		//Check result.
		if(packet.body.dwpwd.sampleValue.generalValue.valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(packet.body.dwpwd.sampleValue.generalValue.valueType == GENERAL_FLOAT_TYPE ||
				packet.body.dwpwd.sampleValue.generalValue.valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue);
		}
		//Calculate checksum16.
		packet.checksum16 = SWAP16(Checksum16Coder::encode((_UINT8 *)&packet,totalLength));
		//Return true.
		return totalLength;
	}
	//Reurn 0.
	return 0;
}

/**
 * Clear packet.
 *
 * @param packet Packet for clear.
 * @param command Command of packet.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::clearPacket(DevicePacket& packet,_UINT8 command)
{
	//Clear packet.
	memset((_UINT8 *)&packet,0,sizeof(DevicePacket));
	//Set default command.
	packet.command = command;
	//Set default version.
	packet.version = _PROTOCOL_VERSION;
	//Check command.
	if(command == DevicePacket::DEVICE_STATUS)
	{
		//Set default total length.
		packet.totalLength = DEVICE_STATUS_PACKET_SIZE;
		//Set default device type.
		packet.body.ds.deviceType = 0x00000000; //Self defined device.
		//Set default device flags.
		packet.body.ds.deviceFlags	= 0x00; //Slave device.
		//Set default device status.
		packet.body.ds.deviceStatus = 0x00; //Idle.
		//Set default sample rate.
		packet.body.ds.sampleRate = 0;//Unlimited.
	}
	else if(command == DevicePacket::DEVICE_CONTROL)
	{
		//Set default total length.
		packet.totalLength = DEVICE_CONTROL_PACKET_SIZE;
		//Set default sample rate.
		packet.body.dc.sampleRate = 0;
	}
	else if(command == DevicePacket::DEVICE_RELEASE)
	{
		//Set default total length.
		packet.totalLength = DEVICE_RELEASE_PACKET_SIZE;
		//Set default sample rate.
		packet.body.dc.sampleRate = 0;
	}
	else if(command == DevicePacket::DEVICE_READ_DATA)
	{
		//Set default total length.
		packet.totalLength = DEVICE_READ_DATA_PACKET_SIZE(0);
		//Set default sample count.
		packet.body.drd.deviceValue.sampleCount = 0;
	}
	else if(command == DevicePacket::DEVICE_WRITE_DATA)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WRITE_DATA_PACKET_SIZE(0);
		//Set default sample count.
		packet.body.drd.deviceValue.sampleCount = 0;
	}
	else if(command == DevicePacket::DEVICE_READ_STORAGE)
	{
		//Set default total length.
		packet.totalLength = DEVICE_READ_STORAGE_PACKET_SIZE;
		//Set default offset.
		packet.body.drs.offset = 0;
		//Set default type.
		packet.body.drs.generalValue.valueType == GENERAL_NULL_TYPE;
	}
	else if(command == DevicePacket::DEVICE_WRITE_STORAGE)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WRITE_STORAGE_PACKET_SIZE;
		//Set default offset.
		packet.body.dws.offset = 0;
		//Set default type.
		packet.body.dws.generalValue.valueType == GENERAL_NULL_TYPE;
	}
	else if(command == DevicePacket::DEVICE_WIRELESS_STATUS)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WIRELESS_STATUS_PACKET_SIZE;
		//Set default device type.
		packet.body.dwps.deviceType = 0x00000000; //Self defined device.
		//Set default device flags.
		packet.body.dwps.deviceFlags = 0x00; //Slave device.
		//Set default device status.
		packet.body.dwps.deviceStatus = 0x00; //Idle.
		//Set default sample rate.
		packet.body.dwps.sampleRate = 0;//Unlimited.
	}
	else if(command == DevicePacket::DEVICE_WIRELESS_CONTROL)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WIRELESS_CONTROL_PACKET_SIZE;
		//Set default sample rate.
		packet.body.dwpc.sampleRate = 0;
	}
	else if(command == DevicePacket::DEVICE_WIRELESS_RELEASE)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WIRELESS_RELEASE_PACKET_SIZE;
		//Set default sample rate.
		packet.body.dwpr.sampleRate = 0;
	}
	else if(command == DevicePacket::DEVICE_WIRELESS_READ_DATA)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WIRELESS_READ_DATA_PACKET_SIZE;
		//Set default flags.
		packet.body.dwprd.flags = 0x00;
	}
	else if(command == DevicePacket::DEVICE_WIRELESS_WRITE_DATA)
	{
		//Set default total length.
		packet.totalLength = DEVICE_WIRELESS_WRITE_DATA_PACKET_SIZE;
		//Set default flags.
		packet.body.dwpwd.flags = 0x00;
	}
}

/**
 * Verify packet.
 *
 * @param packet Packet for verify.
 * @param packetSize Size of packet.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL DevicePacket::verifyPacket(DevicePacket& packet,_UINT16 packetSize)
{
    //Network to host.        
    _UINT16 totalLength = SWAP16(packet.totalLength);
    //Check total length.
    if(totalLength != packetSize)
    {
#ifdef _DEBUG_NETWORK_MODULE
        //Print result.
        _PRINT0("DevicePacket::verifyPacket : the total length of packet is not equal to packet size !");
#endif
        return _FALSE;
    }
	//Check version.
	if(packet.version != _PROTOCOL_VERSION)
	{
#ifdef _DEBUG_NETWORK_MODULE
        //Print result.
        _PRINT0("DevicePacket::verifyPacket : version is not correct !");
#endif
        return _FALSE;
	}
    //Get checksum16.
    _UINT16 checksum16 = SWAP16(packet.checksum16);
    //Reset checksum16.
    packet.checksum16 = 0x0000;
    //Get verify value.
    _UINT16 verify16 = Checksum16Coder::encode((_UINT8 *)&packet,totalLength);
    //Check fcs16.
    if(verify16 != checksum16)
    {
#ifdef _DEBUG_NETWORK_MODULE
        //Print result.
        _PRINT2("The checksum16(0x%04x) of packet is not correct(0x%04x) !",checksum16,verify16);
#endif
        return _FALSE;
    }
    //Set checksum16.
    packet.checksum16 = checksum16;
    //Set total length.
    packet.totalLength = totalLength;
	//Return result.
	return _TRUE;
}

/**
 * Dump samples.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::dumpSamples()
{
	//Print.
	_PRINT0("DevicePacket::dumpSamples : show samples !");
    //Print size.
    _PRINT1("\tSize of byte is %d",sizeof(byte));
    _PRINT1("\tSize of int is %d",sizeof(int));
    _PRINT1("\tSize of long is %d",sizeof(long));
    _PRINT1("\tSize of float is %d",sizeof(float));
    
	_PRINT1("\tSize of GeneralValue is %d",sizeof(GeneralValue));
    _PRINT1("\tSize of SampleValue is %d",sizeof(SampleValue));
    _PRINT1("\tSize of DeviceValue is %d",sizeof(DeviceValue));

    _PRINT1("\tSize of DeviceStatus is %d",sizeof(DeviceStatus));
    _PRINT1("\tSize of DeviceControl is %d",sizeof(DeviceControl));
    _PRINT1("\tSize of DeviceRelease is %d",sizeof(DeviceRelease));
    _PRINT1("\tSize of DeviceReadData is %d",sizeof(DeviceReadData));
    _PRINT1("\tSize of DeviceWriteData is %d",sizeof(DeviceWriteData));
    _PRINT1("\tSize of DeviceReadStorage is %d",sizeof(DeviceReadStorage));
    _PRINT1("\tSize of DeviceWriteStorage is %d",sizeof(DeviceWriteStorage));
	_PRINT1("\tSize of DeviceWirelessStatus is %d",sizeof(DeviceWirelessStatus));
	_PRINT1("\tSize of DeviceWirelessReadData is %d",sizeof(DeviceWirelessReadData));
	_PRINT1("\tSize of DeviceWirelessWriteData is %d",sizeof(DeviceWirelessWriteData));

    _PRINT1("\tSize of PacketBody is %d",sizeof(PacketBody));
    _PRINT1("\tSize of DevicePacket is %d",sizeof(DevicePacket));

	//Do while.
	for(_UINT8 i = 0;i < 16;i ++)
	{
	    _PRINT2("\tDEVICE_READ_DATA_PACKET_SIZE(%d) is %d",i,DEVICE_READ_DATA_PACKET_SIZE(i));
	}
	//Do while.
	for(_UINT8 i = 0;i < 16;i ++)
	{
	    _PRINT2("\tDEVICE_WRITE_DATA_PACKET_SIZE(%d) is %d",i,DEVICE_WRITE_DATA_PACKET_SIZE(i));
	}

	//Device packet.
    DevicePacket packet;
    //Clear packet.
	clearPacket(packet,DEVICE_STATUS);
    //Dump packet.
    dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_CONTROL);
    //Dump packet.
	dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_RELEASE);
    //Dump packet.
    dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_READ_DATA);
    //Dump packet.
	dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_WRITE_DATA);
    //Dump packet.
	dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_READ_STORAGE);
    //Dump packet.
	dumpPacket(packet);
    //Clear packet.
    clearPacket(packet,DEVICE_WRITE_STORAGE);
    //Dump packet.
	dumpPacket(packet);
	//Clear packet.
	clearPacket(packet,DEVICE_WIRELESS_STATUS);
	//Dump packet.
	dumpPacket(packet);
	//Clear packet.
	clearPacket(packet,DEVICE_WIRELESS_CONTROL);
	//Dump packet.
	dumpPacket(packet);
	//Clear packet.
	clearPacket(packet,DEVICE_WIRELESS_RELEASE);
	//Dump packet.
	dumpPacket(packet);
	//Clear packet.
	clearPacket(packet,DEVICE_WIRELESS_READ_DATA);
	//Dump packet.
	dumpPacket(packet);
	//Clear packet.
	clearPacket(packet,DEVICE_WIRELESS_WRITE_DATA);
	//Dump packet.
	dumpPacket(packet);
}

/**
 * Dump buffer.
 *
 * @param packet Packet.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::dumpBuffer(const DevicePacket& packet)
{
	//Buffer.
	_CHAR buffer[256];
	//Print result.
	_PRINT0("DevicePacket::dumpBuffer : dump buffer of packet !");
	//Clear buffer.
	memset(buffer,0,256 * sizeof(_CHAR));
	//Format.
	_FORMAT0(buffer,"\tbytes = 0x");Serial.print(buffer);
    //Print hex.
    for(_UINT16 i = 0;i < sizeof(DevicePacket);i ++)
    {
		//Get value.
		_UINT8 value = ((_UINT8 *)&packet)[i];
		//Check value.
		if(value < 16) Serial.print('0');Serial.print(value,HEX);
    }
    //Print new line.
    Serial.println();
}

/**
 * Dump buffer.
 *
 * @param packet Packet.
 * @param length Length of buffer.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::dumpBuffer(const DevicePacket& packet,_UINT16 length)
{
	//Buffer.
	_CHAR buffer[256];
	//Print result.
	_PRINT0("DevicePacket::dumpBuffer : dump buffer of packet !");
	//Clear buffer.
	memset(buffer,0,256 * sizeof(_CHAR));
	//Format.
	_FORMAT0(buffer,"\tbytes = 0x");Serial.print(buffer);
    //Print hex.
    for(_UINT16 i = 0;i < sizeof(DevicePacket) && i < length;i ++)
    {
		//Get value.
		uint8_t value = ((uint8_t *)&packet)[i];
		//Check value.
		if(value < 16) Serial.print('0');Serial.print(value,HEX);
    }
    //Print new line.
    Serial.println();
}

/**
 * Dump packet.
 *
 * @param packet Packet.
 * @return
 *     <p>No results returned.</p>
 */
void DevicePacket::dumpPacket(const DevicePacket& packet)
{
	//Print result.
	_PRINT0("DevicePacket::dumpPacket : dump device packet !");
	_PRINT1("\ttotalLength = %u",packet.totalLength);
	//Check command.
	if(packet.command == DEVICE_STATUS)
	{
		_PRINT1("\tcommand = 0x%02x (device status)",packet.command);
	}
	else if(packet.command == DEVICE_CONTROL)
	{
		_PRINT1("\tcommand = 0x%02x (device control)",packet.command);
	}
	else if(packet.command == DEVICE_RELEASE)
	{
		_PRINT1("\tcommand = 0x%02x (device release)",packet.command);
	}
	else if(packet.command == DEVICE_READ_DATA)
	{
		_PRINT1("\tcommand = 0x%02x (device read data)",packet.command);
	}
	else if(packet.command == DEVICE_WRITE_DATA)
	{
		_PRINT1("\tcommand = 0x%02x (device write data)",packet.command);
	}
	else if(packet.command == DEVICE_READ_STORAGE)
	{
		_PRINT1("\tcommand = 0x%02x (device read storage)",packet.command);
	}
	else if(packet.command == DEVICE_WRITE_STORAGE)
	{
		_PRINT1("\tcommand = 0x%02x (device write storage)",packet.command);
	}
	else if(packet.command == DEVICE_WIRELESS_STATUS)
	{
		_PRINT1("\tcommand = 0x%02x (device wirelsss status)",packet.command);
	}
	else if(packet.command == DEVICE_WIRELESS_CONTROL)
	{
		_PRINT1("\tcommand = 0x%02x (device wirelsss control)",packet.command);
	}
	else if(packet.command == DEVICE_WIRELESS_RELEASE)
	{
		_PRINT1("\tcommand = 0x%02x (device wirelsss release)",packet.command);
	}
	else if(packet.command == DEVICE_WIRELESS_READ_DATA)
	{
		_PRINT1("\tcommand = 0x%02x (device wirelsss read data)",packet.command);
	}
	else if(packet.command == DEVICE_WIRELESS_WRITE_DATA)
	{
		_PRINT1("\tcommand = 0x%02x (device wirelsss write data)",packet.command);
	}
	else
	{
		_PRINT1("\tcommand = 0x%02x (unknown)",packet.command);
	}
	_PRINT1("\tversion = 0x%02x",packet.version);
	_PRINT1("\tchecksum16 = 0x%04x",packet.checksum16);
	//Check command.
	if(packet.command == DevicePacket::DEVICE_STATUS)
	{
		//Print result.
		_PRINT1("Dump device status packet(%d) !",sizeof(DeviceStatus));
		//Print result.
		_PRINT1("\tdeviceType = 0x%08lx",packet.body.ds.deviceType);
		//Print result.
		_PRINT1("\tdeviceFlags = 0x%02x",packet.body.ds.deviceFlags);
		//Print result.
		_PRINT1("\tdeviceStatus = 0x%02x",packet.body.ds.deviceStatus);
		//Print result.
		_PRINT6("\tmacAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.ds.macAddress[0],(_UINT8)packet.body.ds.macAddress[1],(_UINT8)packet.body.ds.macAddress[2],
			(_UINT8)packet.body.ds.macAddress[3],(_UINT8)packet.body.ds.macAddress[4],(_UINT8)packet.body.ds.macAddress[5]);
		//Print result.
		_PRINT4("\tipv4Address = %u.%u.%u.%u",
			(_UINT8)packet.body.ds.ipv4Address[0],(_UINT8)packet.body.ds.ipv4Address[1],
			(_UINT8)packet.body.ds.ipv4Address[2],(_UINT8)packet.body.ds.ipv4Address[3]);
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.ds.sampleRate);
	}
	//Check command.
	else if(packet.command == DevicePacket::DEVICE_CONTROL)
	{
		//Print result.
		_PRINT1("Dump device control packet(%d) !",sizeof(DeviceControl));
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.dc.sampleRate);
	}
	else if(packet.command == DevicePacket::DEVICE_RELEASE)
	{
		//Print result.
		_PRINT1("Dump device release packet(%d) !",sizeof(DeviceRelease));
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.dr.sampleRate);
	}
	else if(packet.command == DevicePacket::DEVICE_READ_DATA)
	{
		//Print result.
		_PRINT1("Dump read data packet(%d) !",sizeof(DeviceReadData));
		//Print sample count.
		_PRINT1("\tsampleCount = %d",packet.body.drd.deviceValue.sampleCount);
		//Do while.
		for(_UINT8 i = 0;i < packet.body.drd.deviceValue.sampleCount;i ++)
		{
			//Print timestamp.
			_PRINT2("\tsample[%d].timestamp = 0x%08lx",
				i,packet.body.drd.deviceValue.sampleValues[i].timestamp);
			//Print sequence id.
			_PRINT2("\tsample[%d].sequenceID = %u",
				i,packet.body.drd.deviceValue.sampleValues[i].sequenceID);
			//Print pin value.
			_PRINT2("\tsample[%d].pinValue = 0x%08lx",
				i,packet.body.drd.deviceValue.sampleValues[i].pinValue);
			//Get value type.
			_UINT8 valueType = packet.body.drd.deviceValue.sampleValues[i].generalValue.valueType;
			//Print value type.
			_PRINT2("\tsample[%d].valueType = 0x%02x",i,valueType);
			//Check result.
			if(valueType == GENERAL_BOOLEAN_TYPE)
			{
				//Check result.
				if(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.boolValue)
				{
					//Print value.
					_PRINT1("\tsample[%d].value = true (boolean)",i);
				}
				else
				{
					//Print value.
					_PRINT1("\tsample[%d].value = false (boolean)",i);
				}
			}
			else if(valueType == GENERAL_BYTE_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = %d (byte)",
					i,packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.byteValue);
			}
			else if(valueType == GENERAL_CHAR_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = '%c' (char)",
					i,packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.charValue);
			}
			else if(valueType == GENERAL_SHORT_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = %d (short)",
					i,packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(valueType == GENERAL_INTEGER_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = 0x%08lx (integer)",
					i,packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
			else if(valueType == GENERAL_FLOAT_TYPE)
			{
				//Buffer.
				uint8_t formatBuffer[32];
				//Clear buffer.
				memset(formatBuffer,0,32);
				//Convert to string.
				dtostre(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.floatValue,(char *)formatBuffer,8,true); 
				//Print value.
				_PRINT2("\tsample[%d].value = %s (float)",i,formatBuffer);
			}
			else
			{
				//Print value.
				_PRINT2("\tsample[i].value = 0x%08lx (unknown)",
					i,packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
	}
	else if(packet.command == DevicePacket::DEVICE_WRITE_DATA)
	{
		//Print result.
		_PRINT1("Dump write data packet(%d) !",sizeof(DeviceReadData));
		//Print sample count.
		_PRINT1("\tsampleCount = %d",packet.body.dwd.deviceValue.sampleCount);
		//Do while.
		for(_UINT8 i = 0;i < packet.body.dwd.deviceValue.sampleCount;i ++)
		{
			//Print timestamp.
			_PRINT2("\tsample[%d].timestamp = 0x%08l",
				i,packet.body.dwd.deviceValue.sampleValues[i].timestamp);
			//Print sequence id.
			_PRINT2("\tsample[%d].sequenceID = %u",
				i,packet.body.dwd.deviceValue.sampleValues[i].sequenceID);
			//Print pin value.
			_PRINT2("\tsample[%d].pinValue = 0x%08lx",
				i,packet.body.dwd.deviceValue.sampleValues[i].pinValue);
			//Get value type.
			_UINT8 valueType = packet.body.dwd.deviceValue.sampleValues[i].generalValue.valueType;
			//Print value type.
			_PRINT2("\tsample[%d].valueType = 0x%02x",i,valueType);
			//Check result.
			if(valueType == GENERAL_BOOLEAN_TYPE)
			{
				//Check result.
				if(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.boolValue)
				{
					//Print value.
					_PRINT1("\tsample[%d].value = true (boolean)",i);
				}
				else
				{
					//Print value.
					_PRINT1("\tsample[%d].value = false (boolean)",i);
				}
			}
			else if(valueType == GENERAL_BYTE_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = %d (byte)",
					i,packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.byteValue);
			}
			else if(valueType == GENERAL_CHAR_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = '%c' (char)",
					i,packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.charValue);
			}
			else if(valueType == GENERAL_SHORT_TYPE)
			{
				//Print value.
				_PRINT2("\tsample[%d].value = %d (short)",
					i,packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(valueType == GENERAL_INTEGER_TYPE)
			{
				//Print value.
				_PRINT3("\tsample[%d].value = 0x%04x%04x (integer)",
					i,(uint16_t)(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue >> 16),
					(uint16_t)packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
			else if(valueType == GENERAL_FLOAT_TYPE)
			{
				//Buffer.
				uint8_t formatBuffer[32];
				//Clear buffer.
				memset(formatBuffer,0,32);
				//Convert to string.
				dtostre(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.floatValue,(char *)formatBuffer,8,true); 
				//Print value.
				_PRINT2("\tsample[i].value = %s (float)",i,formatBuffer);
			}
			else
			{
				//Print value.
				_PRINT2("\tsample[i].value = 0x%08lx (unknown)",
					i,packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
	}
	else if(packet.command == DevicePacket::DEVICE_READ_STORAGE)
	{
		//Print result.
		_PRINT1("Dump read external packet(%d) !",sizeof(DeviceReadStorage));
		//Print offset.
		_PRINT1("\toffset = 0x%08lx",
			packet.body.drs.offset);
		//Get value type.
		_UINT8 valueType = packet.body.drs.generalValue.valueType;
		//Print value type.
		_PRINT1("\tvalueType = 0x%02x",valueType);
		//Check result.
		if(valueType == GENERAL_BOOLEAN_TYPE)
		{
			//Check result.
			if(packet.body.drs.generalValue.dataValue.boolValue)
			{
				//Print value.
				_PRINT0("\tvalue = true (boolean)");
			}
			else
			{
				//Print value.
				_PRINT0("\tvalue = false (boolean)");
			}
		}
		else if(valueType == GENERAL_BYTE_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %d (byte)",
				packet.body.drs.generalValue.dataValue.byteValue);
		}
		else if(valueType == GENERAL_CHAR_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = '%c' (char)",
				packet.body.drs.generalValue.dataValue.charValue);
		}
		else if(valueType == GENERAL_SHORT_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %d (short)",
				packet.body.drs.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_INTEGER_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = 0x%08lx (integer)",
				(_UINT32)packet.body.drs.generalValue.dataValue.integerValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE)
		{
			//Buffer.
			_CHAR formatBuffer[32];
			//Clear buffer.
			memset(formatBuffer,0,32);
			//Convert to string.
			dtostre(packet.body.drs.generalValue.dataValue.floatValue,formatBuffer,8,_TRUE); 
			//Print value.
			_PRINT1("\tvalue = %s (float)",formatBuffer);
		}
		else if(valueType == GENERAL_LENGTH_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %lu (length)",
				(_UINT32)packet.body.drs.generalValue.dataValue.length);
		}
		else
		{
			//Print value.
			_PRINT1("\tvalue = 0x%08lx (unknown)",
				packet.body.drs.generalValue.dataValue.integerValue);
		}
	}
	else if(packet.command == DevicePacket::DEVICE_WRITE_STORAGE)
	{
		//Print result.
		_PRINT1("Dump write external packet(%d) !",sizeof(DeviceWriteStorage));
		//Print offset.
		_PRINT1("\toffset = 0x%08lx",
			packet.body.dws.offset);
		//Get value type.
		_UINT8 valueType = packet.body.dws.generalValue.valueType;
		//Print value type.
		_PRINT1("\tvalueType = 0x%02x",valueType);
		//Check result.
		if(valueType == GENERAL_BOOLEAN_TYPE)
		{
			//Check result.
			if(packet.body.dws.generalValue.dataValue.boolValue)
			{
				//Print value.
				_PRINT0("\tvalue = true (boolean)");
			}
			else
			{
				//Print value.
				_PRINT0("\tvalue = false (boolean)");
			}
		}
		else if(valueType == GENERAL_BYTE_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %d (byte)",
				packet.body.dws.generalValue.dataValue.byteValue);
		}
		else if(valueType == GENERAL_CHAR_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = '%c' (char)",
				packet.body.dws.generalValue.dataValue.charValue);
		}
		else if(valueType == GENERAL_SHORT_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %d (short)",
				packet.body.dws.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_INTEGER_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = 0x%08lx (long)",
				packet.body.dws.generalValue.dataValue.integerValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE)
		{
			//Buffer.
			uint8_t formatBuffer[32];
			//Clear buffer.
			memset(formatBuffer,0,32);
			//Convert to string.
			dtostre(packet.body.dws.generalValue.dataValue.floatValue,(char *)formatBuffer,8,true); 
			//Print value.
			_PRINT1("\tvalue = %s (float)",formatBuffer);
		}
		else if(valueType == GENERAL_LENGTH_TYPE)
		{
			//Print value.
			_PRINT1("\tvalue = %lu (length)",
				(_UINT32)packet.body.drs.generalValue.dataValue.length);
		}
		else
		{
			//Print value.
			_PRINT1("\tvalue = 0x%08lx (unknown)",
				packet.body.dws.generalValue.dataValue.integerValue);
		}
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_STATUS)
	{
		//Print result.
		_PRINT1("Dump wireless status packet(%d) !",sizeof(DeviceWirelessStatus));
		//Print result.
		_PRINT6("\twirelessAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwps.wirelessAddress[0],(_UINT8)packet.body.dwps.wirelessAddress[1],(_UINT8)packet.body.dwps.wirelessAddress[2],
			(_UINT8)packet.body.dwps.wirelessAddress[3],(_UINT8)packet.body.dwps.wirelessAddress[4],(_UINT8)packet.body.dwps.wirelessAddress[5]);
		//Print result.
		_PRINT1("\tdeviceType = 0x%08lx",packet.body.dwps.deviceType);
		//Print result.
		_PRINT1("\tdeviceFlags = 0x%02x",packet.body.dwps.deviceFlags);
		//Print result.
		_PRINT1("\tdeviceStatus = 0x%02x",packet.body.dwps.deviceStatus);
		//Print result.
		_PRINT6("\tmacAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwps.macAddress[0],(_UINT8)packet.body.dwps.macAddress[1],(_UINT8)packet.body.dwps.macAddress[2],
			(_UINT8)packet.body.dwps.macAddress[3],(_UINT8)packet.body.dwps.macAddress[4],(_UINT8)packet.body.dwps.macAddress[5]);
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.dwps.sampleRate);
	}
	//Check command.
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_CONTROL)
	{
		//Print result.
		_PRINT1("Dump wireless control packet(%d) !",sizeof(DeviceWirelessControl));
		//Print result.
		_PRINT6("\twirelessAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwpc.wirelessAddress[0],(_UINT8)packet.body.dwpc.wirelessAddress[1],(_UINT8)packet.body.dwpc.wirelessAddress[2],
			(_UINT8)packet.body.dwpc.wirelessAddress[3],(_UINT8)packet.body.dwpc.wirelessAddress[4],(_UINT8)packet.body.dwpc.wirelessAddress[5]);
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.dwpc.sampleRate);
		//Print channel.
		_PRINT1("\tchannel = %d",packet.body.dwpc.channel);
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_RELEASE)
	{
		//Print result.
		_PRINT1("Dump wireless release packet(%d) !",sizeof(DeviceWirelessRelease));
		//Print result.
		_PRINT6("\twirelessAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwpr.wirelessAddress[0],(_UINT8)packet.body.dwpr.wirelessAddress[1],(_UINT8)packet.body.dwpr.wirelessAddress[2],
			(_UINT8)packet.body.dwpr.wirelessAddress[3],(_UINT8)packet.body.dwpr.wirelessAddress[4],(_UINT8)packet.body.dwpr.wirelessAddress[5]);
		//Print sample rate.
		_PRINT1("\tsampleRate = %d",packet.body.dwpr.sampleRate);
		//Print channel.
		_PRINT1("\tchannel = %d",packet.body.dwpr.channel);
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_READ_DATA)
	{
		//Print result.
		_PRINT1("Dump wireless read data packet(%d) !",sizeof(DeviceWirelessReadData));
		//Print result.
		_PRINT6("\twirelessAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwprd.wirelessAddress[0],(_UINT8)packet.body.dwprd.wirelessAddress[1],(_UINT8)packet.body.dwprd.wirelessAddress[2],
			(_UINT8)packet.body.dwprd.wirelessAddress[3],(_UINT8)packet.body.dwprd.wirelessAddress[4],(_UINT8)packet.body.dwprd.wirelessAddress[5]);
		//Print flags.
		_PRINT1("\tflags = 0x%02x",packet.body.dwprd.flags);
		//Print timestamp.
		_PRINT1("\tsample.timestamp = 0x%08lx",
			packet.body.dwprd.sampleValue.timestamp);
		//Print sequence id.
		_PRINT1("\tsample.sequenceID = %u",
			packet.body.dwprd.sampleValue.sequenceID);
		//Print pin value.
		_PRINT1("\tsample.pinValue = 0x%08lx",
			packet.body.dwprd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwprd.sampleValue.generalValue.valueType;
		//Print value type.
		_PRINT1("\tsample.valueType = 0x%02x",valueType);
		//Check result.
		if(valueType == GENERAL_BOOLEAN_TYPE)
		{
			//Check result.
			if(packet.body.dwprd.sampleValue.generalValue.dataValue.boolValue)
			{
				//Print value.
				_PRINT0("\tsample.value = true (boolean)");
			}
			else
			{
				//Print value.
				_PRINT0("\tsample.value = false (boolean)");
			}
		}
		else if(valueType == GENERAL_BYTE_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = %d (byte)",
				packet.body.dwprd.sampleValue.generalValue.dataValue.byteValue);
		}
		else if(valueType == GENERAL_CHAR_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = '%c' (char)",
				packet.body.dwprd.sampleValue.generalValue.dataValue.charValue);
		}
		else if(valueType == GENERAL_SHORT_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = %d (short)",
				packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_INTEGER_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = 0x%08lx (integer)",
				packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE)
		{
			//Buffer.
			uint8_t formatBuffer[32];
			//Clear buffer.
			memset(formatBuffer,0,32);
			//Convert to string.
			dtostre(packet.body.dwprd.sampleValue.generalValue.dataValue.floatValue,(char *)formatBuffer,8,true);
			//Print value.
			_PRINT1("\tsample.value = %s (float)",formatBuffer);
		}
		else
		{
			//Print value.
			_PRINT1("\tsample.value = 0x%08lx (unknown)",
				packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue);
		}
	}
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_WRITE_DATA)
	{
		//Print result.
		_PRINT1("Dump wireless write data packet(%d) !",sizeof(DeviceWirelessWriteData));
		//Print result.
		_PRINT6("\twirelessAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)packet.body.dwpwd.wirelessAddress[0],(_UINT8)packet.body.dwpwd.wirelessAddress[1],(_UINT8)packet.body.dwpwd.wirelessAddress[2],
			(_UINT8)packet.body.dwpwd.wirelessAddress[3],(_UINT8)packet.body.dwpwd.wirelessAddress[4],(_UINT8)packet.body.dwpwd.wirelessAddress[5]);
		//Print flags.
		_PRINT1("\tflags = 0x%02x",packet.body.dwpwd.flags);
		//Print timestamp.
		_PRINT1("\tsample.timestamp = 0x%08lx",
			packet.body.dwpwd.sampleValue.timestamp);
		//Print sequence id.
		_PRINT1("\tsample.sequenceID = %u",
			packet.body.dwpwd.sampleValue.sequenceID);
		//Print pin value.
		_PRINT1("\tsample.pinValue = 0x%08lx",
			packet.body.dwpwd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwpwd.sampleValue.generalValue.valueType;
		//Print value type.
		_PRINT1("\tsample.valueType = 0x%02x",valueType);
		//Check result.
		if(valueType == GENERAL_BOOLEAN_TYPE)
		{
			//Check result.
			if(packet.body.dwpwd.sampleValue.generalValue.dataValue.boolValue)
			{
				//Print value.
				_PRINT0("\tsample.value = true (boolean)");
			}
			else
			{
				//Print value.
				_PRINT0("\tsample.value = false (boolean)");
			}
		}
		else if(valueType == GENERAL_BYTE_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = %d (byte)",
				packet.body.dwpwd.sampleValue.generalValue.dataValue.byteValue);
		}
		else if(valueType == GENERAL_CHAR_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = '%c' (char)",
				packet.body.dwpwd.sampleValue.generalValue.dataValue.charValue);
		}
		else if(valueType == GENERAL_SHORT_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = %d (short)",
				packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_INTEGER_TYPE)
		{
			//Print value.
			_PRINT1("\tsample.value = 0x%08lx (integer)",
				packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE)
		{
			//Buffer.
			uint8_t formatBuffer[32];
			//Clear buffer.
			memset(formatBuffer,0,32);
			//Convert to string.
			dtostre(packet.body.dwpwd.sampleValue.generalValue.dataValue.floatValue,(char *)formatBuffer,8,true);
			//Print value.
			_PRINT1("\tsample.value = %s (float)",formatBuffer);
		}
		else
		{
			//Print value.
			_PRINT1("\tsample.value = 0x%08lx (unknown)",
				packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue);
		}
	}
}
