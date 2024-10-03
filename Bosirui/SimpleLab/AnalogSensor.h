#ifndef _ANALOG_SENSOR_H
#define _ANALOG_SENSOR_H

////////////////////////////////////////////////////////////////////////////////
//
// Analog Sensor
//
////////////////////////////////////////////////////////////////////////////////

class AnalogSensor :
	public SimpleSensor
{
private:
	/**
	 * Pin of sensor.
	 */
	int pinIn;

public:	
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~AnalogSensor(void);

	/**
     * Default construction.
	 *
	 * @param id ID of sensor.
	 * @param pinIn Input pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	AnalogSensor(_UINT16 id,AnalogPin pinIn);

public:
	/**
	 * Get value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Anglog value.</p>
	 */
	virtual int getValue(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !