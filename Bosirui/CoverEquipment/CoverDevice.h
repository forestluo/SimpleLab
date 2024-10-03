#ifndef _COVER_DEVICE_H
#define _COVER_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Cover Device
//
////////////////////////////////////////////////////////////////////////////////

class CoverDevice :
	public SimpleDevice
{
private:
	/**
	 * Status
	 */
	_UINT8 status;
	/**
	 * Motor B
	 */
	DCMotor motorB;
	/**
	 * Sensor B2
	 */
	SwitchSensor sensorB2;
	/**
	 * Sensor B1
	 */
	ReflectSensor sensorB1;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~CoverDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	CoverDevice();

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

//Film Device
extern CoverDevice* pCoverDevice;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !