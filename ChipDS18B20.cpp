////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <ChipDS18B20.h>

#include <OneWire.h>
#include <DallasTemperature.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define ONE_WIRE(o)											((OneWire *)(o))
#define DALLAS_TEMPERATURE(o)								((DallasTemperature *)(o))

//Instance
ChipDS18B20* ChipDS18B20::instance							= (ChipDS18B20 *)_NULL;

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Clear.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
ChipDS18B20::~ChipDS18B20()
{
	//Check result.
	if(chipCores[0] != _NULL)
	{
		//Delete object.
		delete ONE_WIRE(chipCores[0]);
		//Clear object.
		chipCores[0] = (OneWire *)_NULL;
	}
	//Check result.
	if(chipCores[1] != _NULL)
	{
		//Delete object.
		delete DALLAS_TEMPERATURE(chipCores[1]);
		//Clear object.
		chipCores[1] = (DallasTemperature *)_NULL;
	}
}

/**
 * Default construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
ChipDS18B20::ChipDS18B20(DigitalPin pin)
{
	//Create chip core.
	chipCores[0] = new OneWire(pin);
#ifdef _DEBUG
	_ASSERT(chipCores[0] != _NULL);
#endif

	//Create chip core.
	chipCores[1] = new DallasTemperature(ONE_WIRE(chipCores[0]));
#ifdef _DEBUG
	_ASSERT(chipCores[1] != _NULL);
#endif
}

/**
 * Setup.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipDS18B20::setup(void)
{
#ifdef _DEBUG
	_ASSERT(chipCores[0] != _NULL);
	_ASSERT(chipCores[1] != _NULL);
#endif

#ifdef _DEBUG
	_PRINT0("ChipDS18B20::setup : begin to setup dallas temperature IC.");
#endif
	//Locate devices on the bus.
	DALLAS_TEMPERATURE(chipCores[1])->begin();
#ifdef _DEBUG
	_PRINT1("ChipDS18B20::setup : %d devices was found !",
		DALLAS_TEMPERATURE(chipCores[1])->getDeviceCount());
	_PRINT1("ChipDS18B20::setup : parasite power is %d",
		DALLAS_TEMPERATURE(chipCores[1])->isParasitePowerMode());
#endif
	// Method 1:
	// search for devices on the bus and assign based on an index.  ideally,
	// you would do this to initially discover addresses on the bus and then 
	// use those addresses and manually assign them (see above) once you know 
	// the devices on your bus (and assuming they don't change).
	if(!DALLAS_TEMPERATURE(chipCores[1])->getAddress(deviceAddress,0))
	{
#ifdef _DEBUG
		_PRINT0("ChipDS18B20::setup : unable to find device address for device0.");
#endif
		return _FALSE;
	}
	//Set the resolution to 9 bit.
	//Each Dallas/Maxim device is capable of several different resolutions.
	DALLAS_TEMPERATURE(chipCores[1])->setResolution(deviceAddress,12);
#ifdef _DEBUG
	_PRINT1("ChipDS18B20::setup : the resolution of device0 is %d.",
		DALLAS_TEMPERATURE(chipCores[1])->getResolution(deviceAddress));
#endif
	return _TRUE;
}

/**
 * Read temperature.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Temperature.</p>
 */
_FLOAT ChipDS18B20::readTemperature(void)
{
#ifdef _DEBUG
	_ASSERT(chipCores[0] != _NULL);
	_ASSERT(chipCores[1] != _NULL);
#endif
	//Call sensors.requestTemperatures() to issue a global temperature 
	//request to all devices on the bus.
	DALLAS_TEMPERATURE(chipCores[1])->requestTemperatures();
	//Return result.
	return DALLAS_TEMPERATURE(chipCores[1])->getTempC(deviceAddress);
}

/**
 * Uninitialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void ChipDS18B20::uninitialize(void)
{
	//Check result.
	if(instance != _NULL)
	{
		//Delete instance.
		delete (ChipDS18B20 *)instance;
		//Clear instance.
		instance = (ChipDS18B20 *)_NULL;
	}
}

/**
 * Initialize.
 *
 * @param pin Data pin.
 * @return
 *     <p>No results returned.</p>
 */
void ChipDS18B20::initialize(DigitalPin pin)
{
#ifdef _DEBUG
	_ASSERT(instance == _NULL);
#endif
	//Create instance.
	instance = new ChipDS18B20(pin);
#ifdef _DEBUG
	_ASSERT(instance != _NULL);
#endif
	//Setup.
	if(!instance->setup())
	{
#ifdef _DEBUG
		_PRINT0("ChipDS18B20::initialize : fail to setup instance !");
#endif
		//Delete instance.
		delete (ChipDS18B20 *)instance;
		//Clear instance.
		instance = (ChipDS18B20 *)_NULL;
	}
}

/**
 * Read.
 *
 * @param temperature Temperature.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipDS18B20::read(_FLOAT& temperature)
{
	//Return result.
	if(instance == _NULL) return _FALSE;
	//Read temperature.
	temperature = instance->readTemperature(); return _TRUE;
}
