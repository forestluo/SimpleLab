#ifndef _DC_MOTOR_H
#define _DC_MOTOR_H

////////////////////////////////////////////////////////////////////////////////
//
// DC Motor
//
////////////////////////////////////////////////////////////////////////////////

class DCMotor :
	public SimpleMotor
{
private:
	/**
     * Speed.
	 */
	int speed;
	/**
	 * Pins.
	 */
	int pinEnable;
	int pinIn1, pinIn2;

public:
	/**
	 * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~DCMotor(void);

	/**
	 * Default construction.
	 *
	 * @param cID ID of motor.
	 * @param pinIn1 In1 pin.
	 * @param pinIn2 In2 pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DCMotor(char cID,
				DigitalPin pinIn1,
				DigitalPin pinIn2);

	/**
	 * Default construction.
	 *
	 * @param cID ID of motor.
	 * @param pinEnable Enable pin.
	 * @param pinIn1 In1 pin.
	 * @param pinIn2 In2 pin.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DCMotor(char cID,DigitalPin pinEnable,
				DigitalPin pinIn1,DigitalPin pinIn2);

public:
	/**
	 * Get speed.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Speed of motor.</p>
	 */
	int getSpeed(void);

	/**
	 * Set speed.
	 *
	 * @param speed Speed of motor.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSpeed(int speed);

public:
	/**
	 * Stop.
	 *
	 * @param None No parmaeters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void stop(void);

	/**
	 * Start clockwise.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void startCW(void);

	/**
	 * Start counterclockwise.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void startCCW(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
