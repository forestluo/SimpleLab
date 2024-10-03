////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include "MajorDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// Application
//
////////////////////////////////////////////////////////////////////////////////

//Major Device
static MajorDevice* pMajorDevice = _NULL;

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
MajorDevice::~MajorDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
MajorDevice::MajorDevice()
	: motorD('D',DigitalPin14,DigitalPin15),
	  motorE('E',DigitalPin20,DigitalPin21),
	  motorF('F',DigitalPin18,DigitalPin19),
	  motorT('T',DigitalPin16,DigitalPin17),
		sensorV1(SID('V','1'),AnalogPin0),
		sensorV2(SID('V','2'),AnalogPin1),
		sensorD1(SID('D','1'),DigitalPin26),
		sensorD2(SID('D','2'),DigitalPin27),
		sensorE1(SID('E','1'),DigitalPin30),
		sensorE2(SID('E','2'),DigitalPin31),
		sensorE3(SID('E','3'),DigitalPin32),
		sensorE4(SID('E','4'),DigitalPin33),
		sensorF1(SID('F','1'),DigitalPin34),
		sensorF2(SID('F','2'),DigitalPin35),
		sensorF3(SID('F','3'),DigitalPin36),
		sensorF4(SID('F','4'),DigitalPin37)
{
#ifdef _DEBUG
	_PRINT0(">MajorDevice::MajorDevice : device was initialized !");
#endif
}

/**
 * List motors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void MajorDevice::listMotors(void)
{
	//Print motors.
	_PRINT3("%c\tDC\t%d\t%u",motorD.getID(),motorD.getSpeed(),motorD.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorE.getID(),motorE.getSpeed(),motorE.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorF.getID(),motorF.getSpeed(),motorF.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorT.getID(),motorT.getSpeed(),motorT.getElapsedTime());
}

/**
 * List sensors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void MajorDevice::listSensors(void)
{
	//Print sensors.
	_PRINT4("%c%c\tA\t%c\t%d",
		SID_MAJOR(sensorV1.getID()),
		SID_MINOR(sensorV1.getID()),
		'-',sensorV1.getValue());
	_PRINT4("%c%c\tA\t%c\t%d",
		SID_MAJOR(sensorV2.getID()),
		SID_MINOR(sensorV2.getID()),
		'-',sensorV2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorD1.getID()),
		SID_MINOR(sensorD1.getID()),
		sensorD1.isHigh() ? 'H' : 'L',sensorD1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorD2.getID()),
		SID_MINOR(sensorD2.getID()),
		sensorD2.isHigh() ? 'H' : 'L',sensorD2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorE1.getID()),
		SID_MINOR(sensorE1.getID()),
		sensorE1.isHigh() ? 'H' : 'L',sensorE1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorE2.getID()),
		SID_MINOR(sensorE2.getID()),
		sensorE2.isHigh() ? 'H' : 'L',sensorE2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorE3.getID()),
		SID_MINOR(sensorE3.getID()),
		sensorE3.isHigh() ? 'H' : 'L',sensorE3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorE4.getID()),
		SID_MINOR(sensorE4.getID()),
		sensorE4.isHigh() ? 'H' : 'L',sensorE4.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorF1.getID()),
		SID_MINOR(sensorF1.getID()),
		sensorF1.isHigh() ? 'H' : 'L',sensorF1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorF2.getID()),
		SID_MINOR(sensorF2.getID()),
		sensorF2.isHigh() ? 'H' : 'L',sensorF2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorF3.getID()),
		SID_MINOR(sensorF3.getID()),
		sensorF3.isHigh() ? 'H' : 'L',sensorF3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorF4.getID()),
		SID_MINOR(sensorF4.getID()),
		sensorF4.isHigh() ? 'H' : 'L',sensorF4.getValue());
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL MajorDevice::begin(void)
{
	//Begin.
	SimpleDevice::begin();
#ifdef _DEBUG
	_PRINT0(">MajorDevice::begin : begin to execute !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_ECS:
		//Print result.
		_PRINT0("Major");
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
	case CMD_SSECW:
		//Start motor.
		motorE.startCCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SSECCW:
		//Start motor.
		motorE.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SSE:
		//Stop motor.
		motorE.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SSFCW:
		//Start motor.
		motorF.startCCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SSFCCW:
		//Start motor.
		motorF.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_SSF:
		//Stop motor.
		motorF.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_UPT:
		//Get value.
		if(sensorD1.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorD.stop();
			//Start motor.
			motorD.startCCW();
		}
		break;
	case CMD_LPB:
		//Get value.
		if(sensorD2.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorD.stop();
			//Start motor.
			motorD.startCW();
		}
		break;
	case CMD_WPP:
		//Get value.
		if(sensorE1.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_TES1SP:
		//Set status.
		status = 0;
		//Stop motor.
		motorE.stop();
		//Start motor.
		motorE.startCCW();
		break;
	case CMD_TESCP:
		//Set status.
		status = 0;
		//Stop motor.
		motorE.stop();
		//Start motor.
		motorE.startCCW();
		//Stop motor.
		motorF.stop();
		//Start motor.
		motorF.startCCW();
		break;
	case CMD_WPC:
		//Set status
		status = 0;
		//Get value.
		if(sensorF1.isHigh())
		{
			//Add status.
			status = status + 1;
		}
		break;
	case CMD_TWSCP:
		//Get value.
		if(sensorE3.isLow()
			&& sensorF3.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorE.stop();
			//Start motor.
			motorE.startCW();
			//Stop motor.
			motorF.stop();
			//Start motor.
			motorF.startCW();
		}
		break;
	case CMD_TSPPE:
		//Get value.
		if(sensorE4.isLow()
			&& sensorF4.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Get value.
			if(sensorE4.isHigh())
			{
				//Stop motor.
				motorE.stop();
				//Start motor.
				motorE.startCW();
			}
			//Get value.
			if(sensorF4.isHigh())
			{
				//Stop motor.
				motorF.stop();
				//Start motor.
				motorF.startCCW();
			}
		}
		break;
	case CMD_PUSHBR:
		//Start motor.
		motorT.startCCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_PULLBR:
		//Start motor.
		motorT.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">MajorDevice::begin : unsupported command(\"%s\") !",getDescription());
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
void MajorDevice::cancel(void)
{
	//Cancel.
	SimpleDevice::cancel();
#ifdef _DEBUG
	_PRINT0(">MajorDevice::cancel : cancel command !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_TES1SP:
		//Stop motor.
		motorE.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_TESCP:
		//Stop motor.
		motorE.stop();
		motorF.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_UPT:
		//Stop motor.
		motorD.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_LPB:
		//Stop motor.
		motorD.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_WPP:
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_WPC:
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_TWSCP:
		//Stop motor.
		motorE.stop();
		motorF.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_TSPPE:
		//Stop motor.
		motorE.stop();
		motorF.stop();
		//Print result.
		_PRINT0("OK");
		break;
	default:
		//Print result.
		_PRINT0("Error");
#ifdef _DEBUG
		_PRINT1(">MajorDevice::cancel : unsupported command(\"%s\") !",getDescription());
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
_BOOL MajorDevice::doLoop(void)
{
	//Do loop.
	SimpleDevice::doLoop();
/*
#ifdef _DEBUG
	_PRINT0(">MajorDevice::doLoop : do device loop !");
#endif
*/
	//Check command.
	switch(getCommand())
	{
	case CMD_TES1SP:
		//Check status.
		switch(status)
		{
		case 0:
			//Get value.
			if(sensorE2.isLow())
			{
				//Add status.
				status = status + 1;
			}
			break;
		case 1:
			//Get value.
			if(sensorE2.isHigh())
			{
				//Stop motor.
				motorE.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MajorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_TESCP:
		//Check status.
		switch(status)
		{
		case 0:
			//Get value.
			if(sensorF4.isLow())
			{
				//Add status.
				status = status + 1;
			}
			break;
		case 1:
			//Get value.
			if(sensorF4.isHigh())
			{
				//Stop motor.
				motorE.stop();
				motorF.stop();
				//Print result.
				//_PRINT0("OK");
				//Switch command.
				//Set command.
				setCommand(CMD_UPT);
				//Start motor.
				motorD.startCCW();
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MajorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_UPT:
		//Get value.
		if(sensorD1.isLow())
		{
			//Stop motor.
			motorD.stop();
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_LPB:
		//Get value.
		if(sensorD2.isLow())
		{
			//Stop motor.
			motorD.stop();
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_WPP:
		//Get value.
		if(sensorE1.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_WPC:
		//Check status.
		switch(status)
		{
		case 0:
			//Get value.
			if(sensorF1.isHigh())
			{
				//Add status.
				status = status + 1;
			}
			break;
		case 1:
			//Get value.
			if(sensorF1.isLow())
			{
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MajorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_TWSCP:
		//Get value.
		if(sensorE3.isLow()
			&& sensorF3.isLow())
		{
			//Stop motor.
			motorE.stop();
			motorF.stop();
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_TSPPE:
		//Get value.
		if(sensorE4.isLow())
		{
			//Stop motor.
			motorE.stop();
		}
		//Get value.
		if(sensorF4.isLow())
		{
			//Stop motor.
			motorF.stop();
		}
		//Get value.
		if(sensorE4.isLow()
			&& sensorF4.isLow())
		{
			//Stop motor.
			motorE.stop();
			//Stop motor.
			motorF.stop();
			//Print.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">MajorDevice::doLoop : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
