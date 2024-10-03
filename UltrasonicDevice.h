#ifndef _ULTRASONIC_DEVICE_H
#define _ULTRASONIC_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Ultrasonic Device
//
////////////////////////////////////////////////////////////////////////////////

class UltrasonicDevice
{
private:
	/**
     * Trig pin.
	 */
	DigitalPin trigPin;
	/**
	 * Echo pin.
	 */
	DigitalPin echoPin;

	/**
	 * Instance.
	 */
	static UltrasonicDevice* instance;

public:
	/**
	 * Default construction.
	 *
	 * @param trigPin Trig pin.
	 * @param echoPin Echo pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	UltrasonicDevice(DigitalPin trigPin,DigitalPin echoPin);

public:
	/**
	 * Get trig pin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DigitalPin getTrigPin(void);

	/**
	 * Get echo pin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DigitalPin getEchoPin(void);

public:
	/**
     * Uninitialize.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void uninitialize(void);

	/**
	 * Initialize.
	 *
	 * @param trigPin Trig pin.
	 * @param echoPin Echo pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(DigitalPin trigPin,DigitalPin echoPin);

public:
	/**
	 * Get flight distance.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Distance of flight.</p>
	 */
	static _FLOAT getFlightDistance(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !