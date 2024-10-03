#ifndef _MAJOR_DEVICE_H
#define _MAJOR_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Major Device
//
////////////////////////////////////////////////////////////////////////////////

class MajorDevice :
	public SimpleDevice
{
private:
	/**
	 * Status
	 */
	int status;
	/**
	 * Motors
	 */
	DCMotor motorD;
	DCMotor motorE;
	DCMotor motorF;
	DCMotor motorT;
	/**
	 * Sensors
	 */
	AnalogSensor sensorV1;
	AnalogSensor sensorV2;
	SwitchSensor sensorD1;
	SwitchSensor sensorD2;
	ReflectSensor sensorE1;
	ReflectSensor sensorE2;
	ReflectSensor sensorE3;
	ReflectSensor sensorE4;
	ReflectSensor sensorF1;
	ReflectSensor sensorF2;
	ReflectSensor sensorF3;
	ReflectSensor sensorF4;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~MajorDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	MajorDevice();

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

//Major Device
extern MajorDevice* pMajorDevice;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !