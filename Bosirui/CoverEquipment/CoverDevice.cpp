////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include "CoverDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Cover Device
static CoverDevice* pCoverDevice = _NULL;

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
CoverDevice::~CoverDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
CoverDevice::CoverDevice()
	: motorB('C',DigitalPin3,DigitalPin11,DigitalPin12),
		sensorB1(SID('B','1'),DigitalPin10),sensorB2(SID('B','2'),DigitalPin8)
{
	//Set status.
	status = 0;
	//Set speed.
	motorB.setSpeed(64);
#ifdef _DEBUG
	_PRINT0(">CoverDevice::CoverDevice : device was initialized !");
#endif
}

/**
 * List motors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void CoverDevice::listMotors(void)
{
	//Print motor C.
	_PRINT3("%c\tDC\t%d\t%u",motorB.getID(),motorB.getSpeed(),motorB.getElapsedTime());
}

/**
 * List sensors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void CoverDevice::listSensors(void)
{
	//Print sensor A1.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorB1.getID()),
		SID_MINOR(sensorB1.getID()),
		sensorB1.isHigh() ? 'H' : 'L',sensorB1.getValue());
	//Print sensor A2.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorB2.getID()),
		SID_MINOR(sensorB2.getID()),
		sensorB2.isHigh() ? 'H' : 'L',sensorB2.getValue());
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL CoverDevice::begin(void)
{
	//Begin.
	SimpleDevice::begin();
#ifdef _DEBUG
	_PRINT0(">CoverDevice::begin : begin to execute !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_ECS:
		//Print result.
		_PRINT0("Cover");
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
		//Set status.
		status = 0;
		//Check sensor A2.
		if(sensorB2.isHigh())
		{
			//Start motor.
			motorB.startCCW();
			//Set status.
			status = sensorB1.isLow() ? 0 : 1;
		}
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">CoverDevice::begin : unsupported command(\"%s\") !",getDescription());
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
void CoverDevice::cancel(void)
{
	//Cancel.
	SimpleDevice::cancel();
#ifdef _DEBUG
	_PRINT0(">CoverDevice::cancel : cancel command !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_SINGLE:
		//Stop motor.
		motorB.stop();
		//Print result.
		_PRINT0("OK");
		break;
	default:
		//Print result.
		_PRINT0("Error");
#ifdef _DEBUG
		_PRINT1(">CoverDevice::cancel : unsupported command(\"%s\") !",getDescription());
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
_BOOL CoverDevice::doLoop(void)
{
	//Do loop.
	SimpleDevice::doLoop();
/*
#ifdef _DEBUG
	_PRINT0(">CoverDevice::doLoop : do device loop !");
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
			if(sensorB1.isHigh()
				|| sensorB2.isLow())
			{
				//Set status.
				status = 0x02;
			}
			break;
		case 0x01:
			//Get value.
			if(sensorB1.isLow()
				|| sensorB2.isLow())
			{
				//Stop.
				motorB.stop();
				//Print.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		case 0x02:
			//Get value.
			if(sensorB1.isLow()
				|| sensorB2.isLow())
			{
				//Stop.
				motorB.stop();
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
		_PRINT1(">CoverDevice::doLoop : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
