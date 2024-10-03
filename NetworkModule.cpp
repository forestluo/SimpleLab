////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <NetworkModule.h>

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
NetworkModule::~NetworkModule(void)
{

}

/**
 * Default construction.
 *
 * @param chipW5100SelectPin Pin for selecting W5100 chip.
 * @return
 *     <p>No results returned.</p>
 */
NetworkModule::NetworkModule(DigitalPin chipW5100SelectPin)
	: chipW5100(chipW5100SelectPin)
{
	//Clear flags.
	flags = 0x00;
}

/**
 * Whether network connected.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if network connected.</p>
 */
_BOOL NetworkModule::isConnected(void)
{
	//Return result.
	return ((flags & 0x01) == 0x01) ? _TRUE : _FALSE;
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void NetworkModule::dumpConfig(void)
{
	//Print.
	_PRINT0("NetworkModule::dumpConfig : show configs !");
	//Print.
	_PRINT1("\tconnected = %d",isConnected());
	//Dump packet samples.
	DevicePacket::dumpSamples();
}

/**
 * Build connection.
 *
 * @param macAddress MAC address.
 * @param localAddress Local IP address.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL NetworkModule::buildConnection(_UINT64 macAddress,IPAddress& localAddress)
{
	//Set default device status.
    flags = 0;
	//Clear local address.
	memset(&localAddress,0,sizeof(IPAddress));

	//MAC address.
	_UINT8 addressBytes[6];
	//Set mac address.
	addressBytes[0] = (_UINT8)(macAddress >> 40); addressBytes[1] = (_UINT8)(macAddress >> 32);
	addressBytes[2] = (_UINT8)(macAddress >> 24); addressBytes[3] = (_UINT8)(macAddress >> 16);
	addressBytes[4] = (_UINT8)(macAddress >>  8); addressBytes[5] = (_UINT8)(macAddress >>  0);
#ifdef _DEBUG
    //Print your local IP address:
    _PRINT6("NetworkModule::buildConnection : MAC address(%02x-%02x-%02x-%02x-%02x-%02x) !",
		addressBytes[0],addressBytes[1],addressBytes[2],addressBytes[3],addressBytes[4],addressBytes[5]);
#endif

	//Select chip.
	chipW5100.selectChip();
#ifdef _DEBUG
	//Print.
	_PRINT0("NetworkModule::buildConnection : begin to configure ethernet using DHCP !");
#endif
	//Check result.
	if(Ethernet.begin(addressBytes) == 0)
	{
#ifdef _DEBUG
		//Print result.
		_PRINT0("NetworkModule::buildConnection : failed to configure ethernet using DHCP !");
#endif
	}
	else
	{
#ifdef _DEBUG
		//Print.
		_PRINT0("NetworkModule::buildConnection : IP was initialized by DHCP !");
#endif
	    //Get local address.
		localAddress = Ethernet.localIP();
#ifdef _DEBUG
	    //Print your local IP address:
		_PRINT4("NetworkModule::buildConnection : IP address(%u.%u.%u.%u) !",
			localAddress[0],localAddress[1],localAddress[2],localAddress[3]);
#endif

#ifdef _DEBUG
		//Print.
		_PRINT0("NetworkModule::buildConnection : begin to startup UDP !");
#endif
        //Check result.
        if(udpDevice.begin(_PROTOCOL_PORT) == 0)
		{
#ifdef _DEBUG
	        //Print result.
		    _PRINT0("NetworkModule::buildConnection : failed to startup UDP !");
#endif
		}
		else
        {
			//Set flag.
			flags |= 0x01;
#ifdef _DEBUG
            //Print.
            _PRINT0("NetworkModule::buildConnection : successfully startup UDP !");
#endif
        }
	}
	//Unselect chip.
	chipW5100.unselectChip();
#ifdef _DEBUG
    //Print.
    _PRINT0("NetworkModule::buildConnection : UDP service startup !");
#endif
	//Return result.
	return isConnected();
}

/**
 * Receive device packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if there is a valid packet.</p>
 */
_BOOL NetworkModule::receiveDevicePacket(DevicePacket& packet,IPAddress& address)
{
	//Result.
	_BOOL result = _FALSE;
	//Select chip.
	chipW5100.selectChip();
    //If there's data available, read a packet.
    _SHORT packetSize = udpDevice.parsePacket();
    //Check result and return false.
    if(packetSize > 0)
    {
        //Get remote address.
        address = udpDevice.remoteIP();
        //Get remote port.
        _UINT16 remotePort = udpDevice.remotePort();
#ifdef _DEBUG_NETWORK_MODULE
        //Print result.
        _PRINT6("NetworkModule::receiveDevicePacket : packet(%d) from %u.%u.%u.%u:%d",
					packetSize,address[0],address[1],address[2],address[3],remotePort);
#endif
        //Check result.
        if(packetSize < sizeof(DevicePacket))
		{
	        //Clear packet.
		    memset((_UINT8 *)&packet,0,packetSize);
	        //Read the packet into device packet.
		    udpDevice.read((_UINT8 *)&packet,packetSize);
#ifdef _DEBUG_NETWORK_MODULE
		    //Dump buffer of packet.
	        DevicePacket::dumpBuffer(packet,packetSize);
#endif
			//Verify packet.
			if(DevicePacket::verifyPacket(packet,packetSize))
			{
				//Set result.
				result = _TRUE;
#ifdef _DEBUG_NETWORK_MODULE
	            //Print result.
		        _PRINT0("NetworkModule::receiveDevicePacket : received packet is valid !");
#endif
			}
			else
			{
#ifdef _DEBUG_NETWORK_MODULE
	            //Print result.
		        _PRINT0("NetworkModule::receiveDevicePacket : fail to verify the received packet !");
#endif
			}
		}
		else
        {
#ifdef _DEBUG_NETWORK_MODULE
            //Print result.
            _PRINT0("NetworkModule::receiveDevicePacket : the packet size exceeds the max size of device packet.");
#endif
        }
    }
	//Unselect chip.
	chipW5100.unselectChip();
	//Return result.
	return result;
}

/**
 * Send device packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL NetworkModule::sendDevicePacket(DevicePacket& packet,const IPAddress& address)
{
#ifdef _DEBUG_NETWORK_MODULE
	//Dump packet.
	DevicePacket::dumpPacket(packet);
#endif
    //Check fcs16.
    _UINT16 totalLength = DevicePacket::makePacket(packet);
    //Check result.
    if(totalLength <= 0) return _FALSE;
#ifdef _DEBUG_NETWORK_MODULE
	//Dump buffer.
	DevicePacket::dumpBuffer(packet,totalLength);
#endif

	//Result.
	_BOOL result = _FALSE;
	//Select chip.
	chipW5100.selectChip();
	//Send packet.
	if(!udpDevice.beginPacket(address,_PROTOCOL_PORT))
	{
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("NetworkModule::sendDevicePacket : fail to begin packet !");
#endif
	}
	else if(udpDevice.write((_UINT8 *)&packet,totalLength) != totalLength)
	{
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("NetworkModule::sendDevicePacket : fail to write into packet !");
#endif
	}
	else if(!udpDevice.endPacket())
	{
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("NetworkModule::sendDevicePacket : fail to send packet !");
#endif
	}
	else
	{
		//Set flag.
		result = _TRUE;
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("NetworkModule::sendDevicePacket : packet was successfully sent !");
#endif
	}
	//Check result.
	if(!result)
	{
		//Clear flag.
		flags &= ~0x01;
		//Stop udp device.
		udpDevice.stop();
#ifdef _DEBUG_NETWORK_MODULE
		//Close udp device.
		_PRINT0("NetworkModule::sendDevicePacket : close udp device !");
#endif
	}
	//Unselect chip.
	chipW5100.unselectChip();
	//Return result.
	return result;
}
