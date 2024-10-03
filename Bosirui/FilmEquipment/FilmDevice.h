#ifndef _FILM_DEVICE_H
#define _FILM_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Film Device
//
////////////////////////////////////////////////////////////////////////////////

class FilmDevice :
	public SimpleDevice
{
private:
	/**
	 * Status
	 */
	_UINT8 status;
	/**
	 * Motor C
	 */
	DCMotor motorC;
	/**
	 * Sensor C2
	 */
	SwitchSensor sensorC2;
	/**
	 * Sensor C1
	 */
	ReflectSensor sensorC1;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~FilmDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	FilmDevice();

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
extern FilmDevice* pFilmDevice;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !