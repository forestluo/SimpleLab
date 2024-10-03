////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SwitchSensor.h>

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
SwitchSensor::~SwitchSensor(void)
{

}

/**
 * Default construction.
 *
 * @param id ID of sensor.
 * @param pinIn Input pin.
 * @return
 *     <p>No results returned.</p>
 */
SwitchSensor::SwitchSensor(_UINT16 id,AnalogPin pinIn)
	: SimpleSensor(id)
{
	//Set digital.
	digital = _FALSE;
	//Set pin.
	this->pinIn = pinIn;
#ifdef _DEBUG
	_PRINT0(">SwitchSensor::SwitchSensor : set pins !");
	_PRINT2(">\tid = \"%c%c\"",SID_MAJOR(id),SID_MINOR(id));
	_PRINT1(">\tdigital = %c",digital ? 'T' : 'F');
	_PRINT1(">\tpinIn = %d",pinIn);
#endif
}

/**
 * Default construction.
 *
 * @param id ID of sensor.
 * @param pinIn Input pin.
 * @return
 *     <p>No results returned.</p>
 */
SwitchSensor::SwitchSensor(_UINT16 id,DigitalPin pinIn)
	: SimpleSensor(id)
{
	//Set digital.
	digital = _TRUE;
	//Set pin.
	this->pinIn = pinIn;
#ifdef _DEBUG
	_PRINT0(">SwitchSensor::SwitchSensor : set pins !");
	_PRINT2(">\tid = \"%c%c\"",SID_MAJOR(id),SID_MINOR(id));
	_PRINT1(">\tdigital = %c",digital ? 'T' : 'F');
	_PRINT1(">\tpinIn = %d",pinIn);
#endif
}

/**
 * Whether is low.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if it is low.</p>
 */
_BOOL SwitchSensor::isLow(void)
{
	//Check flag.
	if(!digital)
	{
		//Return result.
		return analogRead(pinIn) <= 3.0 ? _TRUE : _FALSE;
	}
	//Return result.
	return digitalRead(pinIn) == LOW ? _TRUE : _FALSE;
}

/**
 * Whether is high.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if it is high.</p>
 */
_BOOL SwitchSensor::isHigh(void)
{
	//Check flag.
	if(!digital)
	{
		//Return result.
		return analogRead(pinIn) > 3.0 ? _TRUE : _FALSE;
	}
	//Return result.
	return digitalRead(pinIn) == HIGH ? _TRUE : _FALSE;
}

/**
 * Get value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Anglog value.</p>
 */
int SwitchSensor::getValue(void)
{
	//Check flag.
	if(!digital)
	{
		//Return result.
		return analogRead(pinIn);
	}
	//Return result.
	return digitalRead(pinIn) == LOW ? 0 : 1023;
}
