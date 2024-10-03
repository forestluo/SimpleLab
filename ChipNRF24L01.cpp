////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>

#include <SPIChip.h>
#include <ChipNRF24L01.h>

#include <RF24.h>
#include <nRF24L01.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define NRF24L01(o)											((RF24 *)(o))

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
ChipNRF24L01::~ChipNRF24L01(void)
{
	//Check result.
	if(chipCore != _NULL)
	{
		//Delete object.
		delete NRF24L01(chipCore);
		//Clear object.
		chipCore = (RF24 *)_NULL;
	}
}

/**
 * Default construction.
 *
 * @param enabledPin Pin for enabled.
 * @param selectedPin Pin for selection.
 * @return
 *     <p>No results returned.</p>
 */
ChipNRF24L01::ChipNRF24L01(DigitalPin enabledPin,DigitalPin selectedPin)
	: SPIChip(selectedPin)
{
	//Create object.
	chipCore = new RF24(enabledPin,selectedPin);
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
}

/**
 * Power up.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipNRF24L01::powerUp(void)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Power up.
	NRF24L01(chipCore)->powerUp();
	//Unselect chip.
	unselectChip();
}

/**
 * Power down.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipNRF24L01::powerDown(void)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Power down.
	NRF24L01(chipCore)->powerDown();
	//Unselect chip.
	unselectChip();
}

/**
 * Dump config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipNRF24L01::dumpConfig(void)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Print details.
	NRF24L01(chipCore)->printDetails();
	//Unselect chip.
	unselectChip();
}

/**
 * Initialize.
 *
 * @param pipe Pipe.
 * @param dataMode Whether it is a data mode.
 * @return
 *     <p>No results returned.</p>
 */
void ChipNRF24L01::initialize(_UINT64 pipe,_BOOL dataMode)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Begin.
	NRF24L01(chipCore)->begin();
	//Enable dynamic payloads.
	NRF24L01(chipCore)->enableDynamicPayloads();
	//Optionally, increase the delay between retries & # of retries.
	NRF24L01(chipCore)->setRetries(15,15);
	//Enable auto ack.
	NRF24L01(chipCore)->setAutoAck(true);
	//Set CRC length.
	NRF24L01(chipCore)->setCRCLength(RF24_CRC_8);
	//Do while.
	for(_UINT8 i = 0;i < 5;i ++)
	{
		//Get data pipe.
		_UINT64 dataPipe = (pipe & 0xFFFFFFFFF0LL) | (i + (dataMode ? 6 : 1));
#ifdef _DEBUG
		_PRINT2("ChipNRF24L01.initialize : data pipe(0x%08lx%8lx) was opened !",(_UINT32)(dataPipe >> 32),(_UINT32)dataPipe);
#endif
		//Open reading pipe.
		//All pipes should sharing the first 32bits.
		NRF24L01(chipCore)->openReadingPipe(i + 1,dataPipe);
	}
	//Start listening.
	NRF24L01(chipCore)->startListening();
	//Unselect chip.
	unselectChip();
}

/**
 * Send device packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipNRF24L01::sendDevicePacket(DevicePacket& packet,_UINT64 address)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif

#ifdef _DEBUG_WIRELESS_MODULE
	//Dump packet.
	DevicePacket::dumpPacket(packet);
#endif
    //Check fcs16.
    _UINT16 totalLength = DevicePacket::makePacket(packet);
    //Check result.
    if(totalLength <= 0 || totalLength > 32) return _FALSE;
#ifdef _DEBUG_WIRELESS_MODULE
	//Dump buffer.
	DevicePacket::dumpBuffer(packet,totalLength);
#endif
	//Select chip.
	selectChip();
    //First, stop listening so we can talk.
    NRF24L01(chipCore)->stopListening();
    //Open the correct pipe for writing.
    NRF24L01(chipCore)->openWritingPipe(address);
	//Write payload.
	NRF24L01(chipCore)->write((_UINT8 *)&packet,totalLength);
	//Now, resume listening so we catch the next packets.
	NRF24L01(chipCore)->startListening();
#ifdef _DEBUG_WIRELESS_MODULE
	//Print.
	_PRINT6("ChipNRF24L01::sendDevicePacket : packet was sent (%02x-%02x-%02x-%02x-%02x-%02x) !",
		(_UINT8)(address >> 40),(_UINT8)(address >> 32),(_UINT8)(address >> 24),
		(_UINT8)(address >> 16),(_UINT8)(address >>  8),(_UINT8)(address >>  0));
#endif
	//Unselect chip.
	unselectChip();
	//Return true.
	return _TRUE;
}

/**
 * Receive device packet.
 *
 * @param packet Packet.
 * @param address Remote address.
 * @return
 *     <p>Return true, if there is a valid packet.</p>
 */	
_BOOL ChipNRF24L01::receiveDevicePacket(DevicePacket& packet,_UINT64& address)
{
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Result.
	_BOOL result = _FALSE;
	//Select chip.
	selectChip();
	//Check available.
	if(NRF24L01(chipCore)->available())
	{
		//Read payload size.
		_UINT8 packetSize = NRF24L01(chipCore)->getDynamicPayloadSize();
        //Check result.
        if(packetSize < sizeof(DevicePacket))
		{
			//Clear packet.
			memset((_UINT8 *)&packet,0,packetSize);
	        //Read the packet into device packet.
		    NRF24L01(chipCore)->read((_UINT8 *)&packet,packetSize);
#ifdef _DEBUG_WIRELESS_MODULE
		    //Dump buffer of packet.
	        DevicePacket::dumpBuffer(packet,packetSize);
#endif
			//Verify packet.
			if(DevicePacket::verifyPacket(packet,packetSize))
			{
				//Set result.
				result = _TRUE;
				//Get wireless address.
				address = packet.getWirelessAddress();
#ifdef _DEBUG_WIRELESS_MODULE
	            //Print result.
		        _PRINT6("ChipNRF24L01::receiveDevicePacket : received packet (%02x-%02x-%02x-%02x-%02x-%02x) !",
					(_UINT8)(address >> 40),(_UINT8)(address >> 32),(_UINT8)(address >> 24),
					(_UINT8)(address >> 16),(_UINT8)(address >>  8),(_UINT8)(address >>  0));
#endif
			}
			else
			{
#ifdef _DEBUG_WIRELESS_MODULE
	            //Print result.
		        _PRINT0("ChipNRF24L01::receiveDevicePacket : fail to verify the received packet !");
#endif
			}
		}
		else
        {
#ifdef _DEBUG_WIRELESS_MODULE
            //Print result.
            _PRINT0("ChipNRF24L01::receiveDevicePacket : the packet size exceeds the max size of device packet.");
#endif
        }
	}
	//Unselect chip.
	unselectChip();
	//Return result.
	return result;
}
