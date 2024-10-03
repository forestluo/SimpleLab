#ifndef _MINOR_DEVICE_H
#define _MINOR_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Minor Device
//
////////////////////////////////////////////////////////////////////////////////

class MinorDevice :
	public SimpleDevice
{
private:
	/**
     * Status
	 */
	int status;
	/**
	 * Timestamp
	 */
	_UINT32 timestamp;

private:
	/**
	 * Motors
	 */
	DCMotor motorG;
	DCMotor motorH;
	DCMotor motorK;
	DCMotor motorL;
	DCMotor motorMN;
	DCMotor motorX;
	/**
	 * Sensors
	 */
	AnalogSensor sensorV1;
	AnalogSensor sensorV2;
	SwitchSensor sensorK1;
	SwitchSensor sensorK2;
	SwitchSensor sensorL1;
	SwitchSensor sensorL2;
	ReflectSensor sensorG1;
	ReflectSensor sensorG2;
	ReflectSensor sensorG3;
	ReflectSensor sensorG4;
	ReflectSensor sensorH1;
	ReflectSensor sensorH2;
	ReflectSensor sensorH3;
	ReflectSensor sensorK3;
	ReflectSensor sensorL3;
	ReflectSensor sensorM1;
	ReflectSensor sensorN1;
	ReflectSensor sensorX1;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~MinorDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	MinorDevice();

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

//Minor Device
extern MinorDevice* pMinorDevice;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !