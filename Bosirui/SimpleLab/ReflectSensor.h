#ifndef _REFLECT_SENSOR_H
#define _REFLECT_SENSOR_H

////////////////////////////////////////////////////////////////////////////////
//
// Reflect Sensor
//
////////////////////////////////////////////////////////////////////////////////

class ReflectSensor :
	public SimpleSensor
{
private:
	/**
	 * Pin of sensor.
	 */
	int pinIn;
	/**
	 * Whether is digital.
	 */
	_BOOL digital;

public:	
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~ReflectSensor(void);

	/**
     * Default construction.
	 *
	 * @param id ID of sensor.
	 * @param pinIn Input pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ReflectSensor(_UINT16 id,AnalogPin pinIn);

	/**
     * Default construction.
	 *
	 * @param id ID of sensor.
	 * @param pinIn Input pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ReflectSensor(_UINT16 id,DigitalPin pinIn);

public:
	/**
	 * Whether is low.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is low.</p>
	 */
	virtual _BOOL isLow(void);

	/**
	 * Whether is high.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is high.</p>
	 */
	virtual _BOOL isHigh(void);

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