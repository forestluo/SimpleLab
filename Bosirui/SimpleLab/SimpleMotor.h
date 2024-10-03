#ifndef _SIMPLE_MOTOR_H
#define _SIMPLE_MOTOR_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Motor
//
////////////////////////////////////////////////////////////////////////////////

class SimpleMotor
{
private:
	/**
	 * ID
	 */
	char id;
	/**
	 * Timestamp.
	 */
	_UINT32 timestamp;


public:
	/**
	 * Default construction.
	 *
	 * @param nID ID of motor.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleMotor(char id);

	/**
	 * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~SimpleMotor(void);

public:
	/**
	 * Get id.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>ID of motor.</p>
	 */
	char getID(void);

public:
	/**
	 * Reset timer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void resetTimer(void);

	/**
	 * Get elapsed time.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Elapsed time.</p>
	 */
	_UINT32 getElapsedTime(void);

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
