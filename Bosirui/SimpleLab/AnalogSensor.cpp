////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <AnalogSensor.h>

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
AnalogSensor::~AnalogSensor(void)
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
AnalogSensor::AnalogSensor(_UINT16 id,AnalogPin pinIn)
	: SimpleSensor(id)
{
	//Set pin.
	this->pinIn = pinIn;
#ifdef _DEBUG
	_PRINT0(">AnalogSensor::AnalogSensor : set pins !");
	_PRINT2(">\tid = \"%c%c\"",SID_MAJOR(id),SID_MINOR(id));
	_PRINT1(">\tpinIn = %d",pinIn);
#endif
}

/**
 * Get value.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Anglog value.</p>
 */
int AnalogSensor::getValue(void)
{
	//Return result.
	return analogRead(pinIn);
}
