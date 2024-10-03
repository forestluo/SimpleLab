#ifndef _CARD_DEVICE_H
#define _CARD_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Card Device
//
////////////////////////////////////////////////////////////////////////////////

class CardDevice :
	public SimpleDevice
{
private:
	/**
	 * Motor D
	 */
	DCMotor motorA;
	/**
	 * Sensor A2
	 */
	SwitchSensor sensorA2;
	/**
	 * Sensor A1
	 */
	ReflectSensor sensorA1;

	/**
	 * Status
	 */
	_UINT8 status;
	/**
	 * Timestamp.
	 */
	_UINT32 timestamp;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~CardDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	CardDevice();

private:
	/**
	 * List motors.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void listMotors(void);
	/**
	 * List sensors.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void listSensors(void);

public:
	/**
     * Begin to execute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL begin(void);

	/**
	 * Cancel.
	 *
	 * @param None No results returned.</p>
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void cancel(void);

	/**
	 * Do loop.
	 *
	 * @param None No results returned.</p>
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL doLoop(void);
};

////////////////////////////////////////////////////////////////////////////////
//
// Application
//
////////////////////////////////////////////////////////////////////////////////

//Card Device
extern CardDevice* pCardDevice;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !