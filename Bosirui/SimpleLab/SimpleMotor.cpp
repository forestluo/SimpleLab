////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleMotor.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleMotor::~SimpleMotor(void)
{

}

/**
 * Default construction.
 *
 * @param id ID of motor.
 * @return
 *     <p>No results returned.</p>
 */
SimpleMotor::SimpleMotor(char id)
{
	//Set id.
	this->id = id;
/*
#ifdef _DEBUG
	_PRINT1(">SimpleMotor::SimpleMotor: id('%c') was initialized !",id);
#endif
*/
}

/**
 * Get id.
 *
 * @param None No parameters needed.
 * @return
 *     <p>ID of motor.</p>
 */
char SimpleMotor::getID(void)
{
	//Return id.
	return id;
}

/**
 * Reset timer.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleMotor::resetTimer(void)
{
	//Set timer.
	timestamp = millis();
}

/**
 * Get elapsed time.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Elapsed time.</p>
 */
_UINT32 SimpleMotor::getElapsedTime(void)
{
	//Return result.
	return millis() - timestamp;
}

/**
 * Stop.
 *
 * @param None No parmaeters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleMotor::stop(void)
{
#ifdef _DEBUG
	_PRINT0(">SimpleMotor::stop : motor was stopped !");
#endif
	//Set timer.
	timestamp = millis();
}

/**
 * Start clockwise.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleMotor::startCW(void)
{
#ifdef _DEBUG
	_PRINT0(">SimpleMotor::startCW : motor was started !");
#endif
	//Set timer.
	timestamp = millis();
}

/**
 * Start counterclockwise.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleMotor::startCCW(void)
{
#ifdef _DEBUG
	_PRINT0(">SimpleMotor::startCCW : motor was started !");
#endif
	//Set timer.
	timestamp = millis();
}
