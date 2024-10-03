////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <WirelessModule.h>

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
WirelessModule::~WirelessModule(void)
{

}

/**
 * Default construction.
 *
 * @param chipNRF24L01EnabledPinA Pin for enabling NRF24L01 chip A.
 * @param chipNRF24L01SelectedPinA Pin for selecting NRF24L01 chip A.
 * @param chipNRF24L01EnabledPinB Pin for enabling NRF24L01 chip B.
 * @param chipNRF24L01SelectedPinB Pin for selecting NRF24L01 chip B.
 * @return
 *     <p>No results returned.</p>
 */
WirelessModule::WirelessModule(DigitalPin chipNRF24L01EnabledPinA,
								DigitalPin chipNRF24L01SelectedPinA,
								DigitalPin chipNRF24L01EnabledPinB,
								DigitalPin chipNRF24L01SelectedPinB)
	: chipA(chipNRF24L01EnabledPinA,chipNRF24L01SelectedPinA),
		chipB(chipNRF24L01EnabledPinB,chipNRF24L01SelectedPinB)
{
	//Clear flags.
	flags = 0x01;//It is online.
}

/**
 * Power up.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void WirelessModule::powerUp(void)
{
	//Set flags.
	flags |= 0x01;
	//Power up.
	chipA.powerUp();
	//Power up.
	chipB.powerUp();
}

/**
 * Power down.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void WirelessModule::powerDown(void)
{
	//Set flags.
	flags &= ~0x01;
	//Power down.
	chipA.powerDown();
	//Power down.
	chipB.powerDown();
}

/**
 * Initialize.
 *
 * @param pipe Pipe.
 * @return
 *     <p>No results returned.</p>
 */
void WirelessModule::initialize(_UINT64 pipe)
{
	//Initialize as command pipe.
	chipA.initialize(pipe,_FALSE);
	//Initialize as sample data pipe.
	chipB.initialize(pipe,_TRUE);
}

/**
 * Whether wireless is connected.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if wireless is online.</p>
 */
_BOOL WirelessModule::isConnected(void)
{
	//Return result.
	return ((flags & 0x01) == 0x01) ? _TRUE : _FALSE;
}

/**
 * Whether wireless is a proxy.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if wireless is a proxy.</p>
 */
_BOOL WirelessModule::isProxy(void)
{
	//Return result.
	return ((flags & 0x02) == 0x02) ? _TRUE : _FALSE;
}

/**
 * Set proxy.
 *
 * @param status Status of proxy.
 * @return
 *     <p>No results returned.</p>
 */
void WirelessModule::setProxy(_BOOL status)
{
	//Check status.
	if(status)
	{
		//Set flag.
		flags |= 0x02;
	}
	else
	{
		//Clear flag.
		flags &= 0x02;
	}
}

/**
 * Send command packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL WirelessModule::sendCommandPacket(DevicePacket& packet,_UINT64 address)
{
	//Return result.
	return chipA.sendDevicePacket(packet,address);
}

/**
 * Receive command packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if there is a valid packet.</p>
 */	
_BOOL WirelessModule::receiveCommandPacket(DevicePacket& packet,_UINT64& address)
{
	//Return result.
	return chipA.receiveDevicePacket(packet,address);
}

/**
 * Send data packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL WirelessModule::sendDataPacket(DevicePacket& packet,_UINT64 address)
{
	//Return result.
	return chipB.sendDevicePacket(packet,address);
}

/**
 * Receive data packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if there is a valid packet.</p>
 */	
_BOOL WirelessModule::receiveDataPacket(DevicePacket& packet,_UINT64& address)
{
	//Return result.
	return chipB.receiveDevicePacket(packet,address);
}
