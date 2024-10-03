////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <DCMotor.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
DCMotor::~DCMotor(void)
{

}

/**
 * Default construction.
 *
 * @param cID ID of motor.
 * @param pinIn1 In1 pin.
 * @param pinIn2 In2 pin.
 * @return
 *     <p>No results returned.</p>
 */
DCMotor::DCMotor(char cID,
					DigitalPin pinIn1,
					DigitalPin pinIn2)
	: SimpleMotor(cID)
{

	//Set speed.
	speed = 255;
	//Disable pin.
	pinEnable = -1;
	//Set pins.
	this->pinIn1 = pinIn1;
	this->pinIn2 = pinIn2;
#ifdef _DEBUG
	_PRINT0(">DCMotor::DCMotor : set pins !");
	_PRINT1(">\tcID = '%c'",cID);
	_PRINT1(">\tpinIn1 = %d",pinIn1);
	_PRINT1(">\tpinIn2 = %d",pinIn2);
#endif
	//Set pin mode.
	pinMode(pinIn1,OUTPUT);
	//Set pin mode.
	pinMode(pinIn2,OUTPUT);

	//Reset timer.
	resetTimer();
	//Initialize.
	digitalWrite(pinIn1,HIGH);
	//Initialize.
	digitalWrite(pinIn2,HIGH);
}

/**
 * Default construction.
 *
 * @param cID ID of motor.
 * @param pinEnable Enable pin.
 * @param pinIn1 In1 pin.
 * @param pinIn2 In2 pin.
 * @return
 *     <p>No results returned.</p>
 */
DCMotor::DCMotor(char cID,
					DigitalPin pinEnable,
					DigitalPin pinIn1,
					DigitalPin pinIn2)
	: SimpleMotor(cID)
{
	//Set speed.
	speed = 255;
	//Set pins.
	this->pinEnable = pinEnable;
	this->pinIn1 = pinIn1;
	this->pinIn2 = pinIn2;
#ifdef _DEBUG
	_PRINT0(">DCMotor::DCMotor : set pins !");
	_PRINT1(">\tcID = '%c'",cID);
	_PRINT1(">\tpinEnable = %d",pinEnable);
	_PRINT1(">\tpinIn1 = %d",pinIn1);
	_PRINT1(">\tpinIn2 = %d",pinIn2);
#endif
	//Set pin mode.
	pinMode(pinEnable,OUTPUT);
	//Set pin mode.
	pinMode(pinIn1,OUTPUT);
	//Set pin mode.
	pinMode(pinIn2,OUTPUT);

	//Reset timer.
	resetTimer();
	//Initialize.
	analogWrite(pinEnable,0);
	//Initialize.
	digitalWrite(pinIn1,HIGH);
	//Initialize.
	digitalWrite(pinIn2,HIGH);
}

/**
 * Get speed.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Speed of motor.</p>
 */
int DCMotor::getSpeed(void)
{
	//Return result.
	return speed;
}

/**
 * Set speed.
 *
 * @param speed Speed of motor.
 * @return
 *     <p>No results returned.</p>
 */
void DCMotor::setSpeed(int speed)
{
	//Check speed.
	if(speed < 0)
	{
		//Adjust.
		speed = 0;
	}
	else
	if(speed > 255)
	{
		//Adjust.
		speed = 255;
	}
	//Set speed.
	this->speed = speed;
}

/**
 * Stop.
 *
 * @param None No parmaeters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DCMotor::stop(void)
{
	//Stop.
	SimpleMotor::stop();
#ifdef _DEBUG
	_PRINT0(">DCMotor::stop : motor was stopped !");
#endif
	//Check pin.
	if(pinEnable != -1)
	{
		//Write out.
		analogWrite(pinEnable,0);
	}
	//Write out.
	digitalWrite(pinIn1,HIGH);
	//Write out.
	digitalWrite(pinIn2,HIGH);
}

/**
 * Start clockwise.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DCMotor::startCW(void)
{
	//Start clockwise.
	SimpleMotor::startCW();
#ifdef _DEBUG
	_PRINT0(">DCMotor::startCW : start clockwise !");
#endif
	//Write out.
	digitalWrite(pinIn1,HIGH);
	//Write out.
	digitalWrite(pinIn2,LOW);
	//Check pin.
	if(pinEnable != -1)
	{
		//Write out.
		analogWrite(pinEnable,speed);
	}
}

/**
 * Start counterclockwise.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void DCMotor::startCCW(void)
{
	//Start counterclockwise.
	SimpleMotor::startCCW();
#ifdef _DEBUG
	_PRINT0(">DCMotor::startCCW : start counterclockwise !");
#endif
	//Write out.
	digitalWrite(pinIn1,LOW);
	//Write out.
	digitalWrite(pinIn2,HIGH);
	//Check pin.
	if(pinEnable != -1)
	{
		//Write out.
		analogWrite(pinEnable,speed);
	}
}
