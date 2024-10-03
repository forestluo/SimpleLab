////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <UltrasonicDevice.h>

#include <SimpleTimer3.h>
#include <RecorderModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//Instance.
UltrasonicDevice* UltrasonicDevice::instance				= (UltrasonicDevice *)_NULL;

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default construction.
 *
 * @param trigPin Trig pin.
 * @param echoPin Echo pin.
 * @return
 *     <p>No results returned.</p>
 */
UltrasonicDevice::UltrasonicDevice(DigitalPin trigPin,DigitalPin echoPin)
{
	//Set trig pin.
	this->trigPin = trigPin;
	//Set echo pin.
	this->echoPin = echoPin;

	//Set pin mode.
	//Set echo pin.
	pinMode(echoPin,INPUT);
	//Set trig pin.
	pinMode(trigPin,OUTPUT);
}

/**
 * Get trig pin.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
DigitalPin UltrasonicDevice::getTrigPin(void)
{
	//Return result.
	return trigPin;
}

/**
 * Get echo pin.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
DigitalPin UltrasonicDevice::getEchoPin(void)
{
	//Return result.
	return echoPin;
}

/**
 * Uninitialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void UltrasonicDevice::uninitialize(void)
{
	//Check instance.
	if(instance != _NULL)
	{
		//Delete instance.
		delete (UltrasonicDevice *)instance;
		//Clear instance.
		instance = (UltrasonicDevice *)_NULL;;
	}
}

/**
 * Initialize.
 *
 * @param trigPin Trig pin.
 * @param echoPin Echo pin.
 * @return
 *     <p>No results returned.</p>
 */
void UltrasonicDevice::initialize(DigitalPin trigPin,DigitalPin echoPin)
{
#ifdef _DEBUG
	_ASSERT(instance == _NULL);
#endif
	//Create instance.
	instance = new UltrasonicDevice(trigPin,echoPin);
#ifdef _DEBUG
	_ASSERT(instance != _NULL);
#endif
}

/**
 * Get flight distance.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Distance of flight.</p>
 */
_FLOAT UltrasonicDevice::getFlightDistance(void)
{
#ifdef _DEBUG
	_ASSERT(instance != _NULL);
#endif
	//Send a pulse to trig pin.
	digitalWrite(instance->getTrigPin(),LOW);
	//Delay.
	delayMicroseconds(2);
	//Write high.
	digitalWrite(instance->getTrigPin(),HIGH);
	//Delay.
	delayMicroseconds(10);
	//Write low.
	digitalWrite(instance->getTrigPin(),LOW);
	//Return result.
	_FLOAT value = pulseIn(instance->getEchoPin(),HIGH) * 0.1716;
	//Return value.
	return value;
}
