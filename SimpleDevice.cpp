////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <DevicePacket.h>
#include <SimpleString.h>
#include <SimpleConsole.h>
#include <DeviceDisplay.h>

#include <SimpleKey.h>
#include <SimpleBuzz.h>
#include <SimpleTimer3.h>
#include <DigitalConnection.h>

#include <HZK16File.h>
#include <ConsoleFile.h>
#include <RecorderFile.h>
#include <RecorderModule.h>

#include <SimpleDevice.h>
#include <PhotogateDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Buzz Pin
#define BUZZ_PIN											DigitalPin3
//Backup Key Pin
#define BACKUP_KEY_PIN										DigitalPin49
//Network Key Pin
#define NETWORK_KEY_PIN										DigitalPin22
//Information Key Pin
#define INFORMATION_KEY_PIN									DigitalPin23
//Digital Connection Pin
#define DIGITAL_CONNECTION_PIN								DigitalPin24
//Unused Digital Pin (D32, D26, D27)
#define NETWORK_CONNECTION_LINKED							DigitalPin13

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
SimpleDevice::~SimpleDevice(void)
{

}

/**
 * Default construction.
 *
 * @param chipAT24C128NAddress Address for AT24C128N chip.
 * @param chipW5100SelectPin Pin for selecting W5100 chip.
 * @param chipADS1247SelectPin Pin for selecting ADS1247 chip.
 * @param chipAT45DB161DSelectPin Pin for selecting AT45DB161D chip.
 * @param chipNRF24L01EnablePinA Pin for enabling NRF24L01 chip A.
 * @param chipNRF24L01SelectePinA Pin for selecting NRF24L01 chip A.
 * @param chipNRF24L01EnablePinB Pin for enabling NRF24L01 chip B.
 * @param chipNRF24L01SelectePinB Pin for selecting NRF24L01 chip B.
 * @param chipAdafruitDCPin DC pin for Adafruit SSD1306 chip.
 * @param chipAdafruitCLKPin CLK pin for Adafruit SSD1306 chip.
 * @param chipAdafruitMOSIPin MOSI pin for Adafruit SSD1306 chip.
 * @param chipAdafruitRESETPin RESET pin for Adafruit SSD1306 chip.
 * @return
 *     <p>No results returned.</p>
 */
SimpleDevice::SimpleDevice(_UINT8 chipAT24C128NAddress,
						   DigitalPin chipW5100SelectPin,
						   DigitalPin chipADS1247SelectPin,
						   DigitalPin chipAT45DB161DSelectPin,
						   DigitalPin chipNRF24L01EnablePinA,
						   DigitalPin chipNRF24L01SelectePinA,
						   DigitalPin chipNRF24L01EnablePinB,
						   DigitalPin chipNRF24L01SelectePinB,
						   DigitalPin chipAdafruitDCPin,
			  			   DigitalPin chipAdafruitCLKPin,
						   DigitalPin chipAdafruitMOSIPin,
				           DigitalPin chipAdafruitRESETPin)
	: displayModule(chipAdafruitDCPin,chipAdafruitCLKPin,
					chipAdafruitMOSIPin,chipAdafruitRESETPin),
	  dataModule(chipADS1247SelectPin),
	  networkModule(chipW5100SelectPin),
	  fileModule(chipAT45DB161DSelectPin),
	  configModule(chipAT24C128NAddress),
	  wirelessModule(chipNRF24L01EnablePinA,chipNRF24L01SelectePinA,
						chipNRF24L01EnablePinB,chipNRF24L01SelectePinB)
{
	//Set flags.
	flags = 0x00;
	//Clear master address.
	memset(&masterAddress,0,sizeof(_UINT64));
	//Clear local address.
	memset(&localAddress,0,sizeof(IPAddress));
	//Get mac address.
	macAddress = configModule.readMACAddress();

	//Set pin mode.
	pinMode(BUZZ_PIN,OUTPUT);
	//Set pin mode.
	pinMode(NETWORK_KEY_PIN,INPUT);
	//Set pin mode.
	pinMode(INFORMATION_KEY_PIN,INPUT);
	//Set pin mode.
	pinMode(DIGITAL_CONNECTION_PIN,INPUT);
	//Initialize connection pin.
	digitalWrite(DIGITAL_CONNECTION_PIN,HIGH);

	//Close buzz.
	SimpleBuzz::close(BUZZ_PIN);
    //Buzz for a while.
	//It sounds for online.
    SimpleBuzz::warning(BUZZ_PIN);
	//Initialize.
	fileModule.initialize();
#ifdef _DEBUG
	_ASSERT(fileModule.fileExists());
#endif
	//Initialize console file.
	ConsoleFile::initialize(fileModule);
	//Initialize recorder file.
	RecorderFile::initialize(fileModule);

	//Initialize recorder module.
	RecorderModule::initialize();
	//Initialize wireless module.
	//Open 1 major pipe and 4 data pipes.
	wirelessModule.initialize(macAddress);

	//Format.
	_CONSOLE1("MEM  [%d]",freeMemory());
	//Format.
	_CONSOLE4("VER  [%x.%x/%x.%x]",
		(_UINT8)(_CURRENT_VERSION >> 4),(_UINT8)(_CURRENT_VERSION & 0x0F),
		(_UINT8)(_PROTOCOL_VERSION >> 4),(_UINT8)(_PROTOCOL_VERSION & 0x0F));
	//Print your local MAC address:
	_CONSOLE6("MAC  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(macAddress >> 40),(_UINT8)(macAddress >> 32),(_UINT8)(macAddress >> 24),
		(_UINT8)(macAddress >> 16),(_UINT8)(macAddress >>  8),(_UINT8)(macAddress >>  0));
}

/**
 * Whether network is engaged.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if network is engaged.</p>
 */
_BOOL SimpleDevice::isEngaged(void)
{
	//Return result.
	return ((flags & 0x01) == 0x01) ? _TRUE : _FALSE;
}

/**
 * Set engaged.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::setEngaged(void)
{
	//Set engaged.
	flags |= 0x01;
}

/**
 * Clear engaged.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::clearEngaged(void)
{
	//Clear flag.
	flags &= ~0x01;
}

/**
 * Whether show console.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if showing console.</p>
 */
_BOOL SimpleDevice::showConsole(void)
{
	//Return result.
	return (flags & 0x08) ? _TRUE : _FALSE;
}

/**
 * Whether show background.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if showing background.</p>
 */
_BOOL SimpleDevice::showBackground(void)
{
	//Return result.
	return (flags & 0x04) ? _TRUE : _FALSE;
}

/**
 * Whether show information.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if showing information.</p>
 */
_BOOL SimpleDevice::showInformation(void)
{
	//Return result.
	return (flags & 0x02) ? _TRUE : _FALSE;
}

/**
 * Get local address.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Local address.</p>
 */
IPAddress SimpleDevice::getLocalAddress(void)
{
	//Return result.
	return localAddress;
}

/**
 * Whether local address is valid.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if local address is valid.</p>
 */
_BOOL SimpleDevice::isValidLocalAddress(void)
{
	//Return result.
	return (localAddress[0] == 0x00 && localAddress[1] == 0x00 &&
			localAddress[2] == 0x00 && localAddress[3] == 0x00) ? _FALSE : _TRUE;
}

/**
 * Clear master address.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::clearMasterAddress(void)
{
	//Clear ipv4 address of master device.
	memset(&masterAddress,0,sizeof(_UINT64));
}

/**
 * Get remote address.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Local address.</p>
 */
IPAddress SimpleDevice::getRemoteAddress(void)
{
	//Address.
	IPAddress address;
	//Set address.
	address[0] = (_UINT8)(masterAddress >> 24);
	address[1] = (_UINT8)(masterAddress >> 16);
	address[2] = (_UINT8)(masterAddress >>  8);
	address[3] = (_UINT8)(masterAddress >>  0);
	//Return result.
	return address;
}

/**
 * Whether remote is master.
 *
 * @param remoteAddress Address of remote.
 * @return
 *     <p>Return true, if remote is mater.</p>
 */
_BOOL SimpleDevice::isMasterAddress(const IPAddress& remoteAddress)
{
	//Check result.
	if((_UINT8)(masterAddress >> 24) != remoteAddress[0]) return _FALSE;
	if((_UINT8)(masterAddress >> 16) != remoteAddress[1]) return _FALSE;
	if((_UINT8)(masterAddress >>  8) != remoteAddress[2]) return _FALSE;
	if((_UINT8)(masterAddress >>  0) != remoteAddress[3]) return _FALSE;
	//Return result.
	return _TRUE;
}

/**
 * Set master address.
 *
 * @param remoteAddress Address of remote.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::setMasterAddress(const IPAddress& remoteAddress)
{
	//Clear master address.
	masterAddress = 0LL;
	//Set remote address of master address.
	masterAddress |= (remoteAddress[0] & 0xFFLL) << 24;
	masterAddress |= (remoteAddress[1] & 0xFFLL) << 16;
	masterAddress |= (remoteAddress[2] & 0xFFLL) <<  8;
	masterAddress |= (remoteAddress[3] & 0xFFLL) <<  0;
}

/**
 * Do loop.
 *
 * @param None No paramters needed.
 * @return
 *     <p>No results return.</p>
 */
void SimpleDevice::doLoop(void)
{
	//Do config action.
	doConfigAction();
	//Do network key action.
	doNetworkKeyAction();
	//Do informatin key action.
	doInformationKeyAction();

	//Packet.
	DevicePacket packet;
	//Display main.
	if(!isEngaged())
	{
		////////////////////////////////////////
		//
		// Get pin value and sample value of device.
		//
		//Clear packet.
		DevicePacket::clearPacket(packet,DevicePacket::DEVICE_READ_DATA);
		//Get sample count.
		_UINT8 sampleCount = device.readDataModule(dataModule,packet.body.drd.deviceValue.sampleValues[0]) ? 1 : 0;
		//Set sample count.
		packet.body.drd.deviceValue.sampleCount = sampleCount;
		//Read device value.
		packet.totalLength = DEVICE_READ_DATA_PACKET_SIZE(sampleCount);
		//
		////////////////////////////////////////
		//Display main.
		displayMain();
		//Check recorder module.
		if(RecorderModule::readNextSampleValue(packet.body.drd.deviceValue.sampleValues[0]))
		{
			//Recorder it into file.
			//Automatically recorder data into falsh.
			RecorderFile::writeRecorder(fileModule,packet.body.drd.deviceValue.sampleValues[0]);
		}
	}
	//Check network module.
	if(networkModule.isConnected())
	{
		//Remote address.
		IPAddress address = getRemoteAddress();
		//Check status of device.
		if(isEngaged() && dataModule.isSampleTimeout())
		{
			////////////////////////////////////////
			//
			// Get pin value and sample value of device.
			//
			//Clear packet.
			DevicePacket::clearPacket(packet,DevicePacket::DEVICE_READ_DATA);
			//Get sample count.
			_UINT8 sampleCount = device.readDataModule(dataModule,packet.body.drd.deviceValue.sampleValues[0]) ? 1 : 0;
			//Check recorder module.
			if(RecorderModule::readNextSampleValue(packet.body.drd.deviceValue.sampleValues[1])) sampleCount ++;
			//Set sample count.
			packet.body.drd.deviceValue.sampleCount = sampleCount;
			//Read device value.
			packet.totalLength = DEVICE_READ_DATA_PACKET_SIZE(sampleCount);
			//
			////////////////////////////////////////
			//Send device packet to receiving port.
			if(sampleCount > 0) networkModule.sendDevicePacket(packet,address);
		}
		//Do receive device packet.
		if(networkModule.receiveDevicePacket(packet,address))
		{
			//Do receive packet and send back response packet.
			if(doReceive(packet,address)) networkModule.sendDevicePacket(packet,address);
		}
	}
	//Check wireless module.
	if(wirelessModule.isConnected())
	{
		//Remote address.
		_UINT64 address = masterAddress;
		//Check status.
		if(!wirelessModule.isProxy() &&
			isEngaged() && dataModule.isSampleTimeout())
		{
			////////////////////////////////////////
			//
			// Get pin value and sample value of device.
			//
			//Clear packet.
			DevicePacket::clearPacket(packet,DevicePacket::DEVICE_WIRELESS_READ_DATA);
			//Get sample count.
			_UINT8 sampleCount = 0;
			//Check recorder module.
			if(RecorderModule::readNextSampleValue(packet.body.dwprd.sampleValue))
			{
				//Add count.
				sampleCount ++;
				//Set flags.
				packet.body.dwprd.flags |= 0x01;
			}
			//If there is no recorder module, then read it as normal.
			else if(device.readDataModule(dataModule,packet.body.dwprd.sampleValue)) sampleCount ++;
			//Read device value.
			packet.totalLength = DEVICE_WIRELESS_READ_DATA_PACKET_SIZE;
			//
			////////////////////////////////////////
			//Send device packet to data pipe.
			//It select a random data pipe to send the data.
			if(sampleCount > 0)
			{
				//Set wireless address.
				packet.setWirelessAddress(macAddress);
				//Send data packet.
				wirelessModule.sendDataPacket(packet,DATA_PIPEn(address));
			}
		}
		//Do receive data packet.
		if(wirelessModule.receiveDataPacket(packet,address))
		{
			//Do receive packet and send back response packet.
			if(doReceive(packet,address))
			{
				//Send the response packet to major pipe.
				wirelessModule.sendCommandPacket(packet,MAJOR_PIPE(address));
			}
		}
		//Do receive command packet.
		if(wirelessModule.receiveCommandPacket(packet,address))
		{
			//Do receive packet and send back response packet.
			if(doReceive(packet,address))
			{
				//Send the response packet to major pipe.
				wirelessModule.sendCommandPacket(packet,MAJOR_PIPE(address));
			}
		}
	}
}

/**
 * Do config action.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::doConfigAction(void)
{
	//Check config module.
	if(configModule.isAvailable())
	{
		//Check connected.
		if(!DigitalConnection::isConnected(DIGITAL_CONNECTION_PIN))
		{
			//Write console.
			_CONSOLE0("CFG  [INVALID]");
			//Warning.
			SimpleBuzz::warning(BUZZ_PIN);
			//Clear device type.
			device.invalidate();
			//Check engaged.
			if(isEngaged())
			{
				//Clear flag.
				//Do not engaged any longer.
				clearEngaged();

				//Device packet.
				DevicePacket devicePacket;
				//Check network.
				if(networkModule.isConnected())
				{
					//Fill device status.
					fillDeviceStatus(devicePacket);
					//Send device packet.
					networkModule.sendDevicePacket(devicePacket,getRemoteAddress());
				}
				//Check wireless.
				if(wirelessModule.isConnected())
				{
					//Fill device wireless status.
					fillDeviceWirelessStatus(devicePacket);
					//Send device packet to the major pipe.
					wirelessModule.sendCommandPacket(devicePacket,MAJOR_PIPE(masterAddress));
				}
			}
			//Clear flags.
			flags &= ~0x06;
			//Invalidate config.
			configModule.invalidate();
			//Set sample rate.
			dataModule.setSampleRate(1);
		}
	}
	else
	{
		//Check engaged.
		if(isEngaged()) return;
		//If it is not connected, return directly.
		if(!DigitalConnection::isConnected(DIGITAL_CONNECTION_PIN)) return;
		//If it is not long connected, return directly.
		if(!DigitalConnection::isConnected(DIGITAL_CONNECTION_PIN,1000)) return;

		//Write console.
		_CONSOLE0("CFG  [CONNECTED]");
		//Warning.
		SimpleBuzz::warning(BUZZ_PIN);
		//The version was not correct, return directly.
		if(!configModule.checkVersion(_CURRENT_VERSION)) return;

		//Warning.
		SimpleBuzz::warning(BUZZ_PIN);
		//Try to load config.
		if(!device.loadConfig(configModule))
		{
			//Invalidate device.
			device.invalidate();
			
			//Write console.
			_CONSOLE0("CFG  [LOAD FAILURE]");
		}
		else
		{
			//Initialize recorder module.
			RecorderModule::initialize();
			//Initialize recorder file.
			RecorderFile::initialize(fileModule);
			//Activate data module.
			device.activateDataModule(dataModule);

			//Write console.
			_CONSOLE0("CFG  [LOAD SUCCESS]");
			//Format.
			_CONSOLE1("TYPE [%08lx]",device.getType());
			//Get registers.
			_UINT64 ads1247Mode = dataModule.readRegisters();
			//Print.
			_CONSOLE6("ADS  [%02x%02x%02x%02x%02x%02x]",
				(_UINT8)(ads1247Mode >> 40),(_UINT8)(ads1247Mode >> 32),(_UINT8)(ads1247Mode >> 24),
				(_UINT8)(ads1247Mode >> 16),(_UINT8)(ads1247Mode >>  8),(_UINT8)(ads1247Mode >>  0));
		}
	}
}

/**
 * Do network key action.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::doNetworkKeyAction(void)
{
	//Check connected.
	if(networkModule.isConnected()) return;
	//Check pressed.
	if(!SimpleKey::isPressed(NETWORK_KEY_PIN)) return;
#ifdef _DEBUG
	_PRINT0("SimpleDevice::doNetworkKeyAction : network key was pressed !");
#endif
	//Wait for releasing key.
	while(SimpleKey::isPressed(NETWORK_KEY_PIN)) delay(1);

	//It sounds for key pressed.
	SimpleBuzz::warning(BUZZ_PIN);
#ifdef _DEBUG
	_PRINT0("SimpleDevice::doNetworkKeyAction : try to build connection !");
#endif
	//Try to build connection.
	if(!networkModule.buildConnection(macAddress,localAddress))
	{
#ifdef _DEBUG
		_PRINT0("SimpleDevice::doNetworkKeyAction : fail to build connection !");
#endif
		//Write console.
		_CONSOLE0("DHCP [FAILURE]");
	}
	else
	{
#ifdef _DEBUG
		_PRINT0("SimpleDevice::doNetworkKeyAction : network connection was built !");
#endif
		//Write console.
		_CONSOLE0("DHCP [SUCCESS]");
		//Print your local IP address:
		_CONSOLE4("IP   [%u.%u.%u.%u]",
			localAddress[0],localAddress[1],localAddress[2],localAddress[3]);

		//Shutdown wireless.
		wirelessModule.powerDown();
		//Write console.
		_CONSOLE0("WM   [POWER DOWN]");
#ifdef _DEBUG
		_PRINT0("SimpleDevice::doNetworkKeyAction : shutdown wireless module !");
#endif
	}
}

/**
 * Do information key action.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::doInformationKeyAction(void)
{
	//Check pressed.
	if(!SimpleKey::isPressed(INFORMATION_KEY_PIN)) return;
#ifdef _DEBUG
	_PRINT0("SimpleDevice::doInformationKeyAction : do action !");
#endif
	//Wait for releasing key.
	while(SimpleKey::isPressed(INFORMATION_KEY_PIN)) delay(1);

	//Buzz.
	//It sounds for key pressed.
	SimpleBuzz::warning(BUZZ_PIN);
	//Check engaged.
	if(isEngaged())
	{
		//Write console.
		_CONSOLE0("INFO [SELF RELEASED]");
	    //Buzz for a while.
		SimpleBuzz::warning(BUZZ_PIN);
		//Set show information.
		flags |= 0x02;
		//Clear engaged flag.
		clearEngaged();

		//Device packet.
		DevicePacket devicePacket;
		//Check network.
		if(networkModule.isConnected())
		{
			//Fill device status.
			fillDeviceStatus(devicePacket);
			//Send device packet.
			networkModule.sendDevicePacket(devicePacket,getRemoteAddress());
		}
		//Check wireless.
		if(wirelessModule.isConnected())
		{
			//Fill device wireless status.
			fillDeviceWirelessStatus(devicePacket);
			//Send device packet to major pipe.
			wirelessModule.sendCommandPacket(devicePacket,MAJOR_PIPE(masterAddress));
		}
	}
	else
	{
		//Check flags.
		switch(flags & 0x0E)
		{
		//Major screen.
		case 0x00:
			//Set flags.
			flags |= 0x02;
			break;
		//Information screen.
		case 0x02:
			//Clear flags.
			flags &= ~0x02;
			//Set flags.
			flags |= (!EXPERIMENT_DEVICE(device.getType()) && configModule.isAvailable()) ? 0x04 : 0x08;
			break;
		//Minor screen.
		case 0x04:
			//Clear flags.
			flags &= ~0x04;
			//Set flags.
			flags |= 0x08;
			break;
		//Console screen.
		case 0x08:
			//Clear flags.
			flags &= ~0x08;
			break;
		default:
			//Clear flags.
			//Back to the beginning.
			flags &= ~0x0E;
			break;
		}
	}
}

/**
 * Check HZK
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::checkHZK(void)
{
	//High code.
	static _UINT16 hCode = 0xA1;
	//Low code.
	static _UINT16 lCode = 0xA0;

    //HZK bitmap.
    _HZKBITMAP bitmap;
    //Clear buffer.
    displayModule.clearBuffer();
    //Do while.
    for(_UINT16 i = 0;i < 8;i ++)
    {
        for(_UINT16 j = 0;j < 4;j ++)
        {
            //Clear bitmap.
            memset(bitmap,0,sizeof(_HZKBITMAP));
            //HZ code.
            _UINT16 hzCode;

			//Add lcode.
			lCode ++;
			//Check result.
			if(lCode > 0xC0)
			{
				//Reset lcode.
				lCode = 0xA1;
			  
				//Add hcode.
				hCode ++;
				//Check result.
				if(hCode > 0xF7) hCode = 0xA1;
			}
			//Default hz code.
			hzCode = (hCode << 8) | lCode;
			//Load HZK bitmap.
			HZK16File::loadHZKBitmap(fileModule,hzCode,bitmap);
            //Draw bitmap.
            displayModule.drawHZKBitmap(i * 16,j * 16,bitmap,1);//White.
        }
    }
    //Display buffer.
    displayModule.displayBuffer();
}

/**
 * Dump device.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::dumpDevice(void)
{
	//Print.
	_PRINT0("SimpleDevice::dumpDevice : show configs !");
	//Print.
	_PRINT1("\tmemory = %d",freeMemory());
	//Print.
	_PRINT1("\tengaged = %d",isEngaged());
	//Print.
	_PRINT1("\tdeviceType = 0x%08lx",device.getType());
	//Print.
	_PRINT1("\tshowBackground = %d",showBackground());
	//Print.
	_PRINT1("\tshowInformation = %d",showInformation());
	//Print.
	_PRINT4("\tlocalAddress = %u.%u.%u.%u",
		localAddress[0],localAddress[1],localAddress[2],localAddress[3]);
	//Check result.
	if((masterAddress & 0xFFFF00000000LL) == 0)
	{
		//Print.
		_PRINT4("\tmasterAddress = %u.%u.%u.%u",
			(_UINT8)(masterAddress >> 24),(_UINT8)(masterAddress >> 16),
			(_UINT8)(masterAddress >>  8),(_UINT8)(masterAddress >>  0));
	}
	else
	{
		//Print.
		_PRINT6("masterAddress = %02x-%02x-%02x-%02x-%02x-%02x",
			(_UINT8)(masterAddress >> 40),(_UINT8)(masterAddress >> 32),(_UINT8)(masterAddress >> 24),
			(_UINT8)(masterAddress >> 16),(_UINT8)(masterAddress >>  8),(_UINT8)(masterAddress >>  0));
	}

	//Dump config.
	dataModule.dumpConfig();
	//Dump config.
	fileModule.dumpConfig();
	//Dump config.
	configModule.dumpConfig();
	//Dump config.
	displayModule.dumpConfig();
	//Dump config.
	networkModule.dumpConfig();
}

/**
 * Display main.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayMain(void)
{
	//Clear buffer.
	displayModule.clearBuffer();
	//Display header.
	displayModule.displayHeader(networkModule.isConnected());
	//Check status.
	if(isEngaged())
	{
		//Display engaged.
		displayEngaged();
	}
	else if(showConsole())
	{
		//Display console.
		displayConsole();
	}
	else if(showInformation())
	{
		//Display information.
		displayInformation();
	}
	//Check config module.
	else if(!configModule.isAvailable())
	{
		//Display no config.
		displayNoConfig();
	}
	else if(showBackground())
	{
		//Display background.
		displayBackground();
	}
	else
	{
		//Display sample result.
		displaySampleResult();
	}
	//Display buffer.
	displayModule.displayBuffer();
}

/**
 * Display value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayValue(void)
{
	//Format value.
	//Buffer.
	_CHAR formatBuffer[32];
	//Clear buffer.
	memset(formatBuffer,0,32);
	//Check type of device.
	if(EXPERIMENT_DEVICE(device.getType()))
	{
		//Convert to string.
		_FORMAT1(formatBuffer,"%ld",dataModule.getPinValue());
	}
	else if(PHOTOGATE(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,3,formatBuffer);
	}
	else if(ULTRASONIC_DISTANCE_DEVICE(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,1,formatBuffer);
	}
	else if(DS18B20(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,2,formatBuffer);
	}
	else if(dataModule.getPinValue() < device.getMinIndex() ||
			dataModule.getPinValue() > device.getMaxIndex())
	{
		//Convert to string.
		_FORMAT0(formatBuffer,"?!?");
	}
	else if(E900(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,2,formatBuffer);
	}
	else if(MPX10DP(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,3,formatBuffer);
	}
	else if(GQY_WL0001(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,3,formatBuffer);
	}
	else if(ACS712(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,1,formatBuffer);
	}
	else if(GQY_WL0008(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,3,formatBuffer);
	}
	else if(INFRARED_DISTANCE_DEVICE(device.getType()))
	{
		//Convert to string.
		dtostrf(device.getSampleValue(),7,2,formatBuffer);
	}
	//Return.
	else return;
	//Convert to double char.
	_CHAR doubleBuffer[32];
	//Clear buffer.
	memset(doubleBuffer,0,32);
	//Left trim string.
	LTRIM_STRING(formatBuffer,32);
	//Double ascii.
	DOUBLE_ASCII(formatBuffer,doubleBuffer);
	//Display string.
	displayModule.displayString(fileModule,(128 - SimpleString::getLength(doubleBuffer) * 8) / 2,29,doubleBuffer);
}

/**
 * Display engaged.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayEngaged(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));

	//Format.
	_FORMAT0(buffer,"\xc9\xe8\xb1\xb8\xb1\xbb\xcb\xf8\xb6\xa8");
	//Display string.
	displayModule.displayString(fileModule,(128 - 8 * SimpleString::getLength(buffer)) / 2,29,buffer);
}

/**
 * Display console.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayConsole(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Move cursor.
	displayModule.setCursor(0,11);
	//Do while.
	for(_UINT8 i = 0;i < 6;i ++)
	{
		//Clear buffer.
		memset(buffer,0,32 * sizeof(_CHAR));
		//Read console.
		ConsoleFile::readConsole(fileModule,6 - i,buffer);
		//Print result.
		if(strlen(buffer) > 0) displayModule.println(buffer);
	}
}

/**
 * Display no config.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayNoConfig(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));

	//Format string.
	_FORMAT0(buffer,"\xb4\xab\xd4\xaa\xce\xb4\xc1\xac\xbd\xd3");
	//Display string.
	displayModule.displayString(fileModule,(128 - 8 * SimpleString::getLength(buffer)) / 2,29,buffer);
}

/**
 * Display background.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayBackground(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));

	//Format.
	_FORMAT0(buffer,"\xb2\xce\xbf\xbc\xca\xfd\xbe\xdd");
	//Display string.
	displayModule.displayString(fileModule,0,11,buffer);

	//Check device type.
	if(PHOTOGATE(device.getType()))
	{
		//Pulses.
		_UINT32 pulses[8];
		//Get pulses.
		PhotogateDevice::readPulses(pulses,8);

		//Move cursor.
		displayModule.setCursor(0,29);
		//Do while.
		for(int i = 0;i < 4;i ++)
		{
			//Format buffer.
			_CHAR formatBuffer1[32];
			//Convert to string.
			dtostrf(pulses[2 * i] / 1000.0f,10,3,formatBuffer1);
			//Format buffer.
			_CHAR formatBuffer2[32];
			//Convert to string.
			dtostrf(pulses[2 * i + 1] / 1000.0f,10,3,formatBuffer2);
			//Format.
			_FORMAT2(buffer,"%s %s",formatBuffer1,formatBuffer2);
			//Print.
			displayModule.println(buffer);
		}
	}
	else
	{
		//Convert to string.
		_FORMAT1(buffer,"%ld",dataModule.getPinValue());
		//Convert to double char.
		_CHAR doubleBuffer[32];
		//Clear buffer.
		memset(doubleBuffer,0,32);
		//Left trim and double ascii.
		LTRIM_STRING(buffer,32); DOUBLE_ASCII(buffer,doubleBuffer);
		//Display string.
		displayModule.displayString(fileModule,(128 - SimpleString::getLength(doubleBuffer) * 8) / 2,29,doubleBuffer);

		//Move cursor.
		displayModule.setCursor(0,47);
		
		//Format.
		_FORMAT1(buffer,"AVRP  [%ld]",RecorderModule::getAveragePinValue());
		//Print.
		displayModule.println(buffer);

		//Format buffer.
		_CHAR formatBuffer[32];
		//Convert to string.
		dtostrf(device.getAverageValue(),8,3,formatBuffer);
		//Left trim string.
		LTRIM_STRING(formatBuffer,32);
		//Format.
		_FORMAT1(buffer,"AVRS  [%s]",formatBuffer);
		//Print.
		displayModule.println(buffer);
	}
}

/**
 * Display information.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displayInformation(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));

	//Move cursor.
	displayModule.setCursor(0,11);
	
	//Format.
	_FORMAT1(buffer,"MEM  [%d]",freeMemory());
	//Print.
	displayModule.println(buffer);

	/*
	//Format.
	_FORMAT4(buffer,"VER  [%x.%x/%x.%x]",
		(_UINT8)(_CURRENT_VERSION >> 4),(_UINT8)(_CURRENT_VERSION & 0x0F),
		(_UINT8)(_PROTOCOL_VERSION >> 4),(_UINT8)(_PROTOCOL_VERSION & 0x0F));
	*/
	{
		//Buffer.
		_CHAR formatBuffer[32];
		//Clear buffer.
		memset(formatBuffer,0,32);
		//Convert to string.
		dtostrf(dataModule.readAVDD(_TRUE),1,3,formatBuffer);
		//Format.
		_FORMAT1(buffer,"AVDD [%s]",formatBuffer);
	}
	//Print.
	displayModule.println(buffer);

	//Format.
	_FORMAT1(buffer,"TYPE [%08lx]",device.getType());
	//Print.
	displayModule.println(buffer);

	//Get registers.
	_UINT64 ads1247Mode = dataModule.readRegisters();
	//Print.
	_FORMAT6(buffer,"ADS  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(ads1247Mode >> 40),(_UINT8)(ads1247Mode >> 32),(_UINT8)(ads1247Mode >> 24),
		(_UINT8)(ads1247Mode >> 16),(_UINT8)(ads1247Mode >>  8),(_UINT8)(ads1247Mode >>  0));
	//Print.
	displayModule.println(buffer);

	//Print your local IP address:
	_FORMAT4(buffer,"IP   [%u.%u.%u.%u]",
		localAddress[0],localAddress[1],localAddress[2],localAddress[3]);
	//Print.
	displayModule.println(buffer);

	//Print your local MAC address:
	_FORMAT6(buffer,"MAC  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(macAddress >> 40),(_UINT8)(macAddress >> 32),(_UINT8)(macAddress >> 24),
		(_UINT8)(macAddress >> 16),(_UINT8)(macAddress >>  8),(_UINT8)(macAddress >>  0));
	//Print.
	displayModule.println(buffer);
}

/**
 * Display sample result.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::displaySampleResult(void)
{
	//Buffer.
	_CHAR buffer[32];
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));

	//Display type.
	//Check type.
	if(EXPERIMENT_DEVICE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xca\xb5\xd1\xe9\xc9\xe8\xb1\xb8");
	}
	else if(GQY_WL0001(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb5\xe7\xd1\xb9");
	}
	else if(ACS712(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb5\xe7\xc1\xf7");
	}
	else if(GQY_WL0008(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc0\xad\xd1\xb9\xc1\xa6");
	}
	else if(PHOTOGATE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb9\xe2\xb5\xe7\xc3\xc5");
	}
	else if(ULTRASONIC_DISTANCE_DEVICE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb3\xac\xc9\xf9\xb2\xa8\xb2\xe2\xbe\xe0");
	}
	else if(INFRARED_DISTANCE_DEVICE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xba\xec\xcd\xe2\xb2\xe2\xbe\xe0");
	}
	else if(DS18B20(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc6\xd5\xcd\xa8\xce\xc2\xb6\xc8");
	}
	else if(MPX10DP(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xcf\xe0\xb6\xd4\xb4\xf3\xc6\xf8\xd1\xb9\xc7\xbf");
	}
	else if(E900(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc8\xdc\xd2\xba\xa3\xf0\xa3\xc8\xd6\xb5");
	}
	else
	{
		//Format.
		_FORMAT0(buffer,"\xa1\xc1\xce\xb4\xd6\xaa\xa1\xc1");
	}
	//Display string.
	displayModule.displayString(fileModule,0,11,buffer);

	//Display value.
	displayValue();

	//Display unit.
	//Check type.
	if(EXPERIMENT_DEVICE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xca\xb5\xd1\xe9\xb5\xa5\xce\xbb");
	}
	else if(GQY_WL0001(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb7\xfc\xcc\xd8");
	}
	else if(ACS712(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xba\xc1\xb0\xb2");
	}
	else if(GQY_WL0008(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc5\xa3\xb6\xd9");
	}
	else if(PHOTOGATE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xba\xc1\xc3\xeb");
	}
	else if(INFRARED_DISTANCE_DEVICE(device.getType()) ||
			ULTRASONIC_DISTANCE_DEVICE(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xba\xc1\xc3\xd7");
	}
	else if(DS18B20(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc9\xe3\xca\xcf\xb6\xc8");
	}
	else if(MPX10DP(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xc7\xa7\xc5\xc1");
	}
	else if(E900(device.getType()))
	{
		//Format.
		_FORMAT0(buffer,"\xb6\xd4\xca\xfd\xd6\xb8\xb1\xea");
	}
	else
	{
		//Format.
		_FORMAT0(buffer,"\xa1\xc1\xce\xb4\xd6\xaa\xa1\xc1");
	}
	//Display string.
	displayModule.displayString(fileModule,128 - 8 * SimpleString::getLength(buffer),47,buffer);
}

/**
 * Fill device status.
 *
 * @param packet Device packet.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::fillDeviceStatus(DevicePacket& packet)
{
    //Clear device packet.
    DevicePacket::clearPacket(packet,DevicePacket::DEVICE_STATUS);
	//Set device type.
	packet.body.ds.deviceType = device.getType();
    //Set default device flags.
    packet.body.ds.deviceFlags = 0x00;//Slave device (0x00).
    //Set current status of device.
    packet.body.ds.deviceStatus = isEngaged() ? 0x01 : 0x00;
	//Set network status of device.
	packet.body.ds.deviceStatus |= networkModule.isConnected() ? 0x02 : 0x00;
	//Set wireless status of device.
	packet.body.ds.deviceStatus |= wirelessModule.isConnected() ? 0x04 : 0x00;
	//Set machine address.
	packet.body.ds.macAddress[0] = (_UINT8)(macAddress >> 40);
	packet.body.ds.macAddress[1] = (_UINT8)(macAddress >> 32);
	packet.body.ds.macAddress[2] = (_UINT8)(macAddress >> 24);
	packet.body.ds.macAddress[3] = (_UINT8)(macAddress >> 16);
	packet.body.ds.macAddress[4] = (_UINT8)(macAddress >>  8);
	packet.body.ds.macAddress[5] = (_UINT8)(macAddress >>  0);
	//Check result.
	if(!isEngaged())
	{
		//Set ipv4 address.
		packet.body.ds.ipv4Address[0] = localAddress[0];
		packet.body.ds.ipv4Address[1] = localAddress[1];
		packet.body.ds.ipv4Address[2] = localAddress[2];
		packet.body.ds.ipv4Address[3] = localAddress[3];
	}
	else
	{
		//Set ipv4 address.
		packet.body.ds.ipv4Address[0] = (_UINT8)(masterAddress >> 24);
		packet.body.ds.ipv4Address[1] = (_UINT8)(masterAddress >> 16);
		packet.body.ds.ipv4Address[2] = (_UINT8)(masterAddress >>  8);
		packet.body.ds.ipv4Address[3] = (_UINT8)(masterAddress >>  0);
	}
	//Set sample rate.
	packet.body.ds.sampleRate = dataModule.getSampleRate();
}

/**
 * Fill device wireless status.
 *
 * @param packet Device packet.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::fillDeviceWirelessStatus(DevicePacket& packet)
{
    //Clear device packet.
    DevicePacket::clearPacket(packet,DevicePacket::DEVICE_WIRELESS_STATUS);
	//Set wireless address.
	packet.setWirelessAddress(macAddress);
	//Set device type.
	packet.body.dwps.deviceType = device.getType();
    //Set default device flags.
    packet.body.dwps.deviceFlags = wirelessModule.isProxy() ? 0x01 : 0x00;
    //Set current status of device.
    packet.body.dwps.deviceStatus = isEngaged() ? 0x01 : 0x00;
	//Set network status of device.
	packet.body.dwps.deviceStatus |= networkModule.isConnected() ? 0x02 : 0x00;
	//Set wireless status of device.
	packet.body.dwps.deviceStatus |= wirelessModule.isConnected() ? 0x04 : 0x00;
	//Check result.
	if(!isEngaged())
	{
		//Set local address.
		packet.body.dwps.macAddress[0] = (_UINT8)(macAddress >> 40);
		packet.body.dwps.macAddress[1] = (_UINT8)(macAddress >> 32);
		packet.body.dwps.macAddress[2] = (_UINT8)(macAddress >> 24);
		packet.body.dwps.macAddress[3] = (_UINT8)(macAddress >> 16);
		packet.body.dwps.macAddress[4] = (_UINT8)(macAddress >>  8);
		packet.body.dwps.macAddress[5] = (_UINT8)(macAddress >>  0);
	}
	else
	{
		//Set master address.
		packet.body.dwps.macAddress[0] = (_UINT8)(masterAddress >> 40);
		packet.body.dwps.macAddress[1] = (_UINT8)(masterAddress >> 32);
		packet.body.dwps.macAddress[2] = (_UINT8)(masterAddress >> 24);
		packet.body.dwps.macAddress[3] = (_UINT8)(masterAddress >> 16);
		packet.body.dwps.macAddress[4] = (_UINT8)(masterAddress >>  8);
		packet.body.dwps.macAddress[5] = (_UINT8)(masterAddress >>  0);
	}
	//Set sample rate.
	packet.body.dwps.sampleRate = dataModule.getSampleRate();
}

/**
 * Do receive.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::doReceive(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check command.
	if(packet.command == DevicePacket::DEVICE_WIRELESS_STATUS)
	{
        //Convert to host order.
        packet.body.dwps.deviceType = SWAP32(packet.body.dwps.deviceType);
		//Convert to host order.
		packet.body.dwps.sampleRate = SWAP16(packet.body.dwps.sampleRate);
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessStatus(packet,remoteAddress);
	}
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_CONTROL)
    {
		//Convert to host order.
		packet.body.dwpc.sampleRate = SWAP16(packet.body.dwpc.sampleRate);
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessControl(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_RELEASE)
    {
		//Convert to host order.
		packet.body.dwpr.sampleRate = SWAP16(packet.body.dwpr.sampleRate);
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessRelease(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_READ_DATA)
    {
		//Convert to network order.
		packet.body.dwprd.sampleValue.timestamp =
			SWAP32(packet.body.dwprd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwprd.sampleValue.pinValue =
			SWAP32(packet.body.dwprd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwprd.sampleValue.generalValue.valueType;
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue);
		}
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessReadData(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_WRITE_DATA)
    {
		//Convert to network order.
		packet.body.dwpwd.sampleValue.timestamp =
			SWAP32(packet.body.dwpwd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwpwd.sampleValue.pinValue =
			SWAP32(packet.body.dwpwd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwpwd.sampleValue.generalValue.valueType;
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue);
		}
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessWriteData(packet,remoteAddress);
    }
    else
    {
#ifdef _DEBUG_WIRELESS_MODULE
        //Print result.
        _PRINT0("SimpleDevice::doReceive : the command of packet is not correct !");
#endif
    }
	//Return false.
	return _FALSE;
}

/**
 * Do receive.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::doReceive(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check command.
    if(packet.command == DevicePacket::DEVICE_STATUS)
    {
        //Convert to host order.
        packet.body.ds.deviceType = SWAP32(packet.body.ds.deviceType);
		//Convert to host order.
		packet.body.ds.sampleRate = SWAP16(packet.body.ds.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Give respone as soon as possible.
		return onDeviceStatus(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_CONTROL)
    {
		//Convert to host order.
		packet.body.dc.sampleRate = SWAP16(packet.body.dc.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceControl(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_RELEASE)
    {
		//Convert to host order.
		packet.body.dr.sampleRate = SWAP16(packet.body.dr.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceRelease(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_READ_DATA)
    {
		//Do while.
		for(_UINT8 i = 0;i < packet.body.drd.deviceValue.sampleCount;i ++)
		{
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].timestamp =
				SWAP32(packet.body.drd.deviceValue.sampleValues[i].timestamp);
			//Convert to network order.
			packet.body.drd.deviceValue.sampleValues[i].pinValue =
				SWAP32(packet.body.drd.deviceValue.sampleValues[i].pinValue);
			//Get value type.
			_UINT8 valueType = packet.body.drd.deviceValue.sampleValues[i].generalValue.valueType;
			//Check result.
			if(valueType == GENERAL_SHORT_TYPE)
			{
				//Convert to network order.
				packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue =
					SWAP16(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(valueType == GENERAL_FLOAT_TYPE ||
					valueType == GENERAL_INTEGER_TYPE)
			{
				//Convert to network order.
				packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue =
					SWAP32(packet.body.drd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceReadData(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WRITE_DATA)
    {
		//Do while.
		for(_UINT8 i = 0;i < packet.body.dwd.deviceValue.sampleCount;i ++)
		{
			//Convert to network order.
			packet.body.dwd.deviceValue.sampleValues[i].timestamp =
				SWAP32(packet.body.dwd.deviceValue.sampleValues[i].timestamp);
			//Convert to network order.
			packet.body.dwd.deviceValue.sampleValues[i].pinValue =
				SWAP32(packet.body.dwd.deviceValue.sampleValues[i].pinValue);
			//Get value type.
			_UINT8 valueType = packet.body.dwd.deviceValue.sampleValues[i].generalValue.valueType;
			//Check result.
			if(valueType == GENERAL_SHORT_TYPE)
			{
				//Convert to network order.
				packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue =
					SWAP16(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.shortValue);
			}
			else if(valueType == GENERAL_FLOAT_TYPE ||
					valueType == GENERAL_INTEGER_TYPE)
			{
				//Convert to network order.
				packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue =
					SWAP32(packet.body.dwd.deviceValue.sampleValues[i].generalValue.dataValue.integerValue);
			}
		}
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWriteData(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_READ_STORAGE)
    {
		//Convert to network order.
		packet.body.drs.offset =
			SWAP32(packet.body.drs.offset);
		//Get value type.
		_UINT8 valueType = packet.body.drs.generalValue.valueType;
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
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceReadStorage(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WRITE_STORAGE)
    {
		//Convert to network order.
		packet.body.dws.offset =
			SWAP32(packet.body.dws.offset);
		//Get value type.
		_UINT8 valueType = packet.body.dws.generalValue.valueType;
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
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWriteStorage(packet,remoteAddress);
    }
	//Check command.
	else if(packet.command == DevicePacket::DEVICE_WIRELESS_STATUS)
	{
        //Convert to host order.
        packet.body.dwps.deviceType = SWAP32(packet.body.dwps.deviceType);
		//Convert to host order.
		packet.body.dwps.sampleRate = SWAP16(packet.body.dwps.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessStatus(packet,remoteAddress);
	}
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_CONTROL)
    {
		//Convert to host order.
		packet.body.dwpc.sampleRate = SWAP16(packet.body.dwpc.sampleRate);
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessControl(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_RELEASE)
    {
		//Convert to host order.
		packet.body.dwpr.sampleRate = SWAP16(packet.body.dwpr.sampleRate);
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessRelease(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_READ_DATA)
    {
		//Convert to network order.
		packet.body.dwprd.sampleValue.timestamp =
			SWAP32(packet.body.dwprd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwprd.sampleValue.pinValue =
			SWAP32(packet.body.dwprd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwprd.sampleValue.generalValue.valueType;
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwprd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwprd.sampleValue.generalValue.dataValue.integerValue);
		}
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessReadData(packet,remoteAddress);
    }
    else if(packet.command == DevicePacket::DEVICE_WIRELESS_WRITE_DATA)
    {
		//Convert to network order.
		packet.body.dwpwd.sampleValue.timestamp =
			SWAP32(packet.body.dwpwd.sampleValue.timestamp);
		//Convert to network order.
		packet.body.dwpwd.sampleValue.pinValue =
			SWAP32(packet.body.dwpwd.sampleValue.pinValue);
		//Get value type.
		_UINT8 valueType = packet.body.dwpwd.sampleValue.generalValue.valueType;
		//Check result.
		if(valueType == GENERAL_SHORT_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue =
				SWAP16(packet.body.dwpwd.sampleValue.generalValue.dataValue.shortValue);
		}
		else if(valueType == GENERAL_FLOAT_TYPE ||
				valueType == GENERAL_INTEGER_TYPE)
		{
			//Convert to network order.
			packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue =
				SWAP32(packet.body.dwpwd.sampleValue.generalValue.dataValue.integerValue);
		}
#ifdef _DEBUG_WIRELESS_MODULE
		//Dump packet.
        DevicePacket::dumpPacket(packet);
#endif
        //Do process.
        return onDeviceWirelessWriteData(packet,remoteAddress);
    }
    else
    {
#ifdef _DEBUG_NETWORK_MODULE
        //Print result.
        _PRINT0("SimpleDevice::doReceive : the command of packet is not correct !");
#endif
    }
	//Return false.
	return _FALSE;
}

/**
 * On device status.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceStatus(DevicePacket& packet,const IPAddress& remoteAddress)
{
	//Fill device status.
	fillDeviceStatus(packet);
#ifdef _DEBUG_NETWORK_MODULE
	//Print.
	_PRINT0("SimpleDevice::onDeviceStatus : device status returned !");
#endif
	//Print your local IP address:
	_CONSOLE4("DS   [%u.%u.%u.%u]",
		remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
	//Return true.
	return _TRUE;
}

/**
 * On device control.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceControl(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status and remote address.
	if(isEngaged() && !isMasterAddress(remoteAddress)) return _FALSE;
	//Reset timer.
	SimpleTimer3::reset();
	//Print console.
	_CONSOLE4("DC   [%u.%u.%u.%u]",
		remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
	//Print your local IP address:
	_CONSOLE1("SAMP [%d]",packet.body.dc.sampleRate);
	//Set engaged.
	setEngaged();
	//Set remote address of master address.
	setMasterAddress(remoteAddress);
	//Set sample rate.
	dataModule.setSampleRate(packet.body.dc.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
	//Print.
	_PRINT1("SimpleDevice::onDeviceControl : set sample rate as %dHz !",packet.body.dc.sampleRate);
#endif
	//Display main.
	displayMain();
	//Fill device status.
	fillDeviceStatus(packet);

	//Check config module.
	if(!configModule.isAvailable())
	{
		//Wireless module powerup.
		wirelessModule.powerUp();
		//Print mode.
		_CONSOLE0("WM   [POWER UP]");
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("SimpleDevice::onDeviceControl : wireless power up !");
#endif
		//Set proxy of wireless module.
		wirelessModule.setProxy(_TRUE);
		//Print mode.
		_CONSOLE0("WM   [PROXY MODE]");
#ifdef _DEBUG_NETWORK_MODULE
		//Print.
		_PRINT0("SimpleDevice::onDeviceControl : entering server mode !");
#endif
	}
	//Return true.
	return _TRUE;
}

/**
 * On device release.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceRelease(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(!isEngaged() || !isMasterAddress(remoteAddress)) return _FALSE;

	//Print console.
	_CONSOLE4("DR   [%u.%u.%u.%u]",
		remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
	//Print your local IP address:
	_CONSOLE1("SAMP [%d]",packet.body.dc.sampleRate);

	//Clear flag.
	clearEngaged();
	//Set sample rate.
	dataModule.setSampleRate(packet.body.dc.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
	//Print.
	_PRINT1("SimpleDevice::onDeviceRelease : set sample rate as %dHz !",packet.body.dc.sampleRate);
#endif
	//Fill device status.
	fillDeviceStatus(packet);

	//Check status.
	if(wirelessModule.isProxy())
	{
		//Clear proxy of wireless module.
		wirelessModule.setProxy(_FALSE);
		//Print mode.
		_CONSOLE0("WM   [CLOSE PROXY]");
#ifdef _DEBUG_WIRELESS_MODULE
		//Print.
		_PRINT0("SimpleDevice::onDeviceRelease : entering client mode !");
#endif
		//Wireless module powerdown.
		wirelessModule.powerDown();
		//Print mode.
		_CONSOLE0("WM   [POWER DOWN]");
#ifdef _DEBUG_WIRELESS_MODULE
		//Print.
		_PRINT0("SimpleDevice::onDeviceRelease : wireless power down !");
#endif
	}
	//Return true.
	return _TRUE;
}

/**
 * On device read data .
 *
 * <p>The salve device would not process the data from other slave.</p>
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceReadData(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //It is a slave and would do not thing with the slave data.
#ifdef _DEBUG_NETWOKR_MODULE
	//Print
	_PRINT0("SimpleDevice::onDeviceReadData : need not to support !");
#endif
	//Print console.
	_CONSOLE4("DRD  [%u.%u.%u.%u]",
		remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
	//Return false.
	return _FALSE;
}

/**
 * On device write data .
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceWriteData(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Print console.
			_CONSOLE4("DWD  [%u.%u.%u.%u]",
				remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
#ifdef _DEBUG_NETWORK_MODULE
			//Print
		    _PRINT0("SimpleDevice::onDeviceWriteData : not supported yet !");
#endif
        }
    }
	//Return false.
	return _FALSE;
}

/**
 * On device read storage.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceReadStorage(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Get offset.
			_UINT32 offset = packet.body.drs.offset;
			//Get value type.
			_UINT8 valueType = packet.body.drs.generalValue.valueType;
			//Get length.
			_UINT32 length = (valueType != GENERAL_LENGTH_TYPE) ?
								0 : packet.body.drs.generalValue.dataValue.length;

			//Clear device packet.
			DevicePacket::clearPacket(packet,DevicePacket::DEVICE_READ_STORAGE);
			//Set offset.
			packet.body.drs.offset = offset;
			//Set value type.
			packet.body.drs.generalValue.valueType = valueType;
			//Check result.
			if(valueType == GENERAL_BOOLEAN_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.boolValue = 
						fileModule.readUint8(offset) ? _TRUE : _FALSE;
					break;
				//External E2PROM writing.
				case 2:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.boolValue = 
						configModule.readUint8(offset) ? _TRUE : _FALSE;
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_BYTE_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.byteValue = 
						(_BYTE)fileModule.readUint8(offset);
					break;
				//External E2PROM writing.
				case 2:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.byteValue = 
						(_BYTE)configModule.readUint8(offset);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_CHAR_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.charValue = 
						(_CHAR)fileModule.readUint8(offset);
					break;
				//External E2PROM writing.
				case 2:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.charValue = 
						(_CHAR)configModule.readUint8(offset);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_SHORT_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.shortValue = 
						(_SHORT)fileModule.readUint16(offset);
					break;
				//External E2PROM writing.
				case 2:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.shortValue = 
						(_SHORT)configModule.readUint16(offset);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_FLOAT_TYPE ||
					valueType == GENERAL_INTEGER_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.integerValue = 
						(_INTEGER)fileModule.readUint32(offset);
					break;
				//External E2PROM writing.
				case 2:
					//Read value from external.
					packet.body.drs.generalValue.dataValue.integerValue = 
						(_INTEGER)configModule.readUint32(offset);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_LENGTH_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Check length.
					if(length > 0 && length <= DEVICE_READ_STORAGE_PACKET_LEFT_SIZE)
					{
						//Set length.
						packet.body.drs.generalValue.dataValue.length = length;
						//Read buffer.
						fileModule.readBuffer(offset,
							((_BUFFER)&packet.body.drs.generalValue.dataValue.length) + sizeof(_INTEGER),length);
					}
					break;
				//External E2PROM writing.
				case 2:
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceReadStorage : invalid offset type !");
#endif
					break;
				}
			}
			else
			{
#ifdef _DEBUG_NETWORK_MODULE
				//Print
				_PRINT0("SimpleDevice::onDeviceReadStorage : invalid value type !");
#endif
				//Return false.
				return _FALSE;
			}
			//Return true.
			return _TRUE;
        }
    }
	//Return false.
	return _FALSE;
}

/**
 * On device write storage.
 *
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>No results returned.</p>
 */
_BOOL SimpleDevice::onDeviceWriteStorage(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Get offset.
			_UINT32 offset = packet.body.dws.offset;
			//Get value type.
			_UINT8 valueType = packet.body.dws.generalValue.valueType;
			//Get length.
			_UINT32 length = (valueType != GENERAL_LENGTH_TYPE) ?
								0 : packet.body.drs.generalValue.dataValue.length;
			//Check result.
			if(valueType == GENERAL_BOOLEAN_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Write value.
					fileModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.boolValue ? 0x01 : 0x00);
					break;
				//External E2PROM writing.
				case 2:
					//Write value.
					configModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.boolValue ? 0x01 : 0x00);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_BYTE_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Write value.
					fileModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.byteValue);
					break;
				//External E2PROM writing.
				case 2:
					//Write value.
					configModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.byteValue);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_CHAR_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Write value.
					fileModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.charValue);
					break;
				//External E2PROM writing.
				case 2:
					//Write value.
					configModule.writeUint8(offset,
						packet.body.dws.generalValue.dataValue.charValue);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_SHORT_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Write value.
					fileModule.writeUint16(offset,
						packet.body.dws.generalValue.dataValue.shortValue);
					break;
				//External E2PROM writing.
				case 2:
					//Write value.
					configModule.writeUint16(offset,
						packet.body.dws.generalValue.dataValue.shortValue);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_FLOAT_TYPE ||
					valueType == GENERAL_INTEGER_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Write value.
					fileModule.writeUint32(offset,
						packet.body.dws.generalValue.dataValue.integerValue);
					break;
				//External E2PROM writing.
				case 2:
					//Write value.
					configModule.writeUint32(offset,
						packet.body.dws.generalValue.dataValue.integerValue);
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else if(valueType == GENERAL_LENGTH_TYPE)
			{
				//Check offset.
				switch((_UINT8)(offset >> 28))
				{
				//Internal E2PROM writing.
				case 0:
					//Not supported yet.
					break;
				//Internal flash writing.
				case 1:
					//Check length.
					if(length > 0 && length <= DEVICE_WRITE_STORAGE_PACKET_LEFT_SIZE)
					{
						//Write buffer.
						fileModule.writeBuffer(offset,
							((_BUFFER)&packet.body.dws.generalValue.dataValue.length) + sizeof(_INTEGER),length);
					}
					break;
				//External E2PROM writing.
				case 2:
					break;
				default:
#ifdef _DEBUG_NETWORK_MODULE
					//Print
					_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid offset type !");
#endif
					break;
				}
			}
			else
			{
#ifdef _DEBUG_NETWORK_MODULE
				//Print
				_PRINT0("SimpleDevice::onDeviceWriteStorage : invalid value type !");
#endif
			}
        }
    }
	//Return false.
	return _FALSE;
}

/**
 * On device wireless status.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessStatus(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check wireless status.
	//Proxy would process tihs command.
	if(wirelessModule.isProxy())
	{
		//Check device flag.
		//It is from an another master.
		if(!(packet.body.dwps.deviceFlags & 0x01))
		{
			//Transfer it to the master machine.
			networkModule.sendDevicePacket(packet,getRemoteAddress());
#ifdef _DEBUG_WIRELESS_MODULE
			//Print
			_PRINT0("SimpleDevice::onDeviceWirelessStatus : transfer client packet to remote master !");
#endif
		}
		//Return false.
		return _FALSE;
	}
	//Do client process.
	//Check device flag.
	if(!(packet.body.dwps.deviceFlags & 0x01)) return _FALSE;
	//Print console.
	_CONSOLE6("DWS  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(remoteAddress >> 40),(_UINT8)(remoteAddress >> 32),(_UINT8)(remoteAddress >> 24),
		(_UINT8)(remoteAddress >> 16),(_UINT8)(remoteAddress >>  8),(_UINT8)(remoteAddress >>  0));
	//Check engaged.
	if(!isEngaged()) SimpleBuzz::warning(BUZZ_PIN);
	//Fill device wireless status.
	fillDeviceWirelessStatus(packet);
	//Return true.
	return _TRUE;
}

/**
 * On device wireless status.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessStatus(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Check wireless status.
			//Only transfer the packet which is from master machine.
			if(wirelessModule.isProxy())
			{
				//Get wireless address.
				_UINT64 wirelessAddress = packet.getWirelessAddress();
				//Set wireless address.
				packet.setWirelessAddress(macAddress);
				//Send wireless packet.
				wirelessModule.sendCommandPacket(packet,MAJOR_PIPE(wirelessAddress));

				//Print console.
				_CONSOLE4("DWS  [%u.%u.%u.%u]",
					remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
#ifdef _DEBUG_WIRELESS_MODULE
				//Print.
				_PRINT0("SimpleDevice::onDeviceWirelessStatus : wireless packet wss sent !");
#endif
			}
		}
	}
	//Return false.
	return _FALSE;
}

/**
 * On device wireless control.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessControl(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check wireless status.
	//Proxy would not process tihs command.
	if(wirelessModule.isProxy()) return _FALSE;
    //Check device status and remote address.
	if(isEngaged() && (masterAddress != remoteAddress)) return _FALSE;
	//Reset timer.
	SimpleTimer3::reset();
	//Print console.
	_CONSOLE6("DWC  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(remoteAddress >> 40),(_UINT8)(remoteAddress >> 32),(_UINT8)(remoteAddress >> 24),
		(_UINT8)(remoteAddress >> 16),(_UINT8)(remoteAddress >>  8),(_UINT8)(remoteAddress >>  0));
	//Set engaged.
	setEngaged();
	//Set remote address of master address.
	masterAddress = remoteAddress;
	//Set sample rate.
	dataModule.setSampleRate(packet.body.dwpc.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
	//Print.
	_PRINT1("SimpleDevice::onDeviceWirelessControl : set sample rate as %dHz !",packet.body.dwpc.sampleRate);
#endif
	//Display main.
	displayMain();
	//Fill device wireless status.
	fillDeviceWirelessStatus(packet);
	//Return true.
	return _TRUE;
}

/**
 * On device wireless control.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessControl(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Check wireless status.
			//Only transfer the packet which is from master machine.
			if(wirelessModule.isProxy())
			{
				//Get wireless address.
				_UINT64 wirelessAddress = packet.getWirelessAddress();
				//Set wireless address.
				packet.setWirelessAddress(macAddress);
				//Send wireless packet.
				wirelessModule.sendCommandPacket(packet,MAJOR_PIPE(wirelessAddress));

				//Print console.
				_CONSOLE4("DWC  [%u.%u.%u.%u]",
					remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
#ifdef _DEBUG_WIRELESS_MODULE
				//Print.
				_PRINT0("SimpleDevice::onDeviceWirelessControl : wireless packet was sent !");
#endif
			}
		}
	}
	//Return false.
	return _FALSE;
}

/**
 * On device wireless release.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessRelease(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check wireless status.
	//Proxy would not process tihs command.
	if(wirelessModule.isProxy()) return _FALSE;
    //Check device status and remote address.
	if(!isEngaged() || (masterAddress != remoteAddress)) return _FALSE;
	//Print remote address:
	_CONSOLE6("DWR  [%02x%02x%02x%02x%02x%02x]",
		(_UINT8)(remoteAddress >> 40),(_UINT8)(remoteAddress >> 32),(_UINT8)(remoteAddress >> 24),
		(_UINT8)(remoteAddress >> 16),(_UINT8)(remoteAddress >>  8),(_UINT8)(remoteAddress >>  0));
	//Clear engaged.
	clearEngaged();
	//Clear master address.
	masterAddress = 0LL;
	//Set sample rate.
	dataModule.setSampleRate(packet.body.dwpr.sampleRate);
#ifdef _DEBUG_NETWORK_MODULE
	//Print.
	_PRINT1("SimpleDevice::onDeviceWirelessRelease : set sample rate as %dHz !",packet.body.dwpc.sampleRate);
#endif
	//Buzz.
	SimpleBuzz::warning(BUZZ_PIN);
	//Fill device wireless status.
	fillDeviceWirelessStatus(packet);
	//Return true.
	return _TRUE;
}

/**
 * On device wireless release.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessRelease(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Check wireless status.
			//Only transfer the packet which is from master machine.
			if(wirelessModule.isProxy())
			{
				//Get wireless address.
				_UINT64 wirelessAddress = packet.getWirelessAddress();
				//Set wireless address.
				packet.setWirelessAddress(macAddress);
				//Send wireless packet.
				wirelessModule.sendCommandPacket(packet,MAJOR_PIPE(wirelessAddress));

				//Print console.
				_CONSOLE4("DWR  [%u.%u.%u.%u]",
					remoteAddress[0],remoteAddress[1],remoteAddress[2],remoteAddress[3]);
#ifdef _DEBUG_WIRELESS_MODULE
				//Print.
				_PRINT0("SimpleDevice::onDeviceWirelessRelease : wireless packet was sent !");
#endif
			}
		}
	}
	//Return false.
	return _FALSE;
}

/**
 * On device wireless read data.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessReadData(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check wireless status.
	//Proxy would process tihs command.
	if(wirelessModule.isProxy())
	{
		//Transfer it to the master machine.
		networkModule.sendDevicePacket(packet,getRemoteAddress());
#ifdef _DEBUG_WIRELESS_MODULE
		//Print
		_PRINT0("SimpleDevice::onDeviceWirelessReadData : transfer client packet to remote master !");
#endif
	}
	//Return false.
	return _FALSE;
}

/**
 * On device wireless read data.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessReadData(DevicePacket& packet,const IPAddress& remoteAddress)
{
#ifdef _DEBUG_WIRELESS_MODULE
	//Print
	_PRINT0("SimpleDevice::onDeviceWirelessReadData : need not support !");
#endif
	return _FALSE;
}

/**
 * On device wireless write data.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessWriteData(DevicePacket& packet,const _UINT64 remoteAddress)
{
	//Check wireless status.
	//Proxy would not process tihs command.
	if(wirelessModule.isProxy()) return _FALSE;
#ifdef _DEBUG_WIRELESS_MODULE
	//Print
	_PRINT0("SimpleDevice::onDeviceWirelessWriteData : not supported yet !");
#endif
	//Return false.
	return _FALSE;
}

/**
 * On device wireless write data.
 * 
 * @param packet Device packet.
 * @param remoteAddress Remote address.
 * @return
 *     <p>Return true, if there is a return packet.</p>
 */
_BOOL SimpleDevice::onDeviceWirelessWriteData(DevicePacket& packet,const IPAddress& remoteAddress)
{
    //Check device status.
    if(isEngaged())
    {
        //Check device.
        if(isMasterAddress(remoteAddress))
        {
			//Check wireless status.
			//Only transfer the packet which is from master machine.
			if(wirelessModule.isProxy())
			{
				//Get wireless address.
				_UINT64 wirelessAddress = packet.getWirelessAddress();
				//Set wireless address.
				packet.setWirelessAddress(macAddress);
				//Send wireless packet to a random data pipe.
				wirelessModule.sendCommandPacket(packet,DATA_PIPEx(wirelessAddress));
			}
		}
	}
}
