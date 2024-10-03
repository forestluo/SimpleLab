////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include "FilmDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Film Device
static FilmDevice* pFilmDevice = _NULL;

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
FilmDevice::~FilmDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
FilmDevice::FilmDevice()
	: motorC('C',DigitalPin3,DigitalPin11,DigitalPin12),
		sensorC1(SID('C','1'),DigitalPin10),sensorC2(SID('C','2'),DigitalPin8)
{
	//Set status.
	status = 0;
	//Set speed.
	motorC.setSpeed(64);
#ifdef _DEBUG
	_PRINT0(">FilmDevice::FilmDevice : device was initialized !");
#endif
}

/**
 * List motors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void FilmDevice::listMotors(void)
{
	//Print motor C.
	_PRINT3("%c\tDC\t%d\t%u",motorC.getID(),motorC.getSpeed(),motorC.getElapsedTime());
}

/**
 * List sensors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void FilmDevice::listSensors(void)
{
	//Print sensor A1.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorC1.getID()),
		SID_MINOR(sensorC1.getID()),
		sensorC1.isHigh() ? 'H' : 'L',sensorC1.getValue());
	//Print sensor A2.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorC2.getID()),
		SID_MINOR(sensorC2.getID()),
		sensorC2.isHigh() ? 'H' : 'L',sensorC2.getValue());
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL FilmDevice::begin(void)
{
	//Begin.
	SimpleDevice::begin();
#ifdef _DEBUG
	_PRINT0(">FilmDevice::begin : begin to execute !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_ECS:
		//Print result.
		_PRINT0("Film");
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_LAM:
		//List all motors.
		listMotors();
		//Print end of list.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_LAS:
		//List all sensors.
		listSensors();
		//Print end of list.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SINGLE:
		//Check sensor A2.
		if(sensorC2.isHigh())
		{
			//Start motor.
			motorC.startCCW();
			//Set status.
			status = sensorC1.isLow() ? 0 : 1;
		}
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">FilmDevice::begin : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}

/**
 * Cancel.
 *
 * @param None No results returned.</p>
 * @return
 *     <p>No results returned.</p>
 */
void FilmDevice::cancel(void)
{
	//Cancel.
	SimpleDevice::cancel();
#ifdef _DEBUG
	_PRINT0(">FilmDevice::cancel : cancel command !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_SINGLE:
		//Clear status.
		status = 0;
		//Stop motor.
		motorC.stop();
		//Print result.
		_PRINT0("OK");
		break;
	default:
		//Print result.
		_PRINT0("Error");
#ifdef _DEBUG
		_PRINT1(">FilmDevice::cancel : unsupported command(\"%s\") !",getDescription());
#endif
	}
}

/**
 * Do loop.
 *
 * @param None No results returned.</p>
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL FilmDevice::doLoop(void)
{
	//Do loop.
	SimpleDevice::doLoop();
/*
#ifdef _DEBUG
	_PRINT0(">FilmDevice::doLoop : do device loop !");
#endif
*/
	//Check command.
	switch(getCommand())
	{
	case CMD_SINGLE:
		//Check status.
		switch(status)
		{
		case 0x00:
			//Get value.
			if(sensorC1.isHigh()
				|| sensorC2.isLow())
			{
				//Set status.
				status = 0x02;
			}
			break;
		case 0x01:
			//Get value.
			if(sensorC1.isLow()
				|| sensorC2.isLow())
			{
				//Stop.
				motorC.stop();
				//Print.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		case 0x02:
			//Get value.
			if(sensorC1.isLow()
				|| sensorC2.isLow())
			{
				//Stop.
				motorC.stop();
				//Print.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		}
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">FilmDevice::doLoop : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
