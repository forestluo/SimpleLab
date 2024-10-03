////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include "CardDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Card Device
static CardDevice* pCardDevice = _NULL;

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
CardDevice::~CardDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
CardDevice::CardDevice()
	: motorA('A',DigitalPin11,DigitalPin12),
		sensorA1(SID('A','1'),DigitalPin10),
		sensorA2(SID('A','2'),DigitalPin8)
{
	//Set status.
	status = 0;
	//Set timestamp.
	timestamp = millis();

	//Set idle.
	setIdle(_FALSE);
	//Set command.
	setCommand(CMD_AUTO);
#ifdef _DEBUG
	_PRINT0(">CardDevice::CardDevice : device was initialized !");
#endif
}

/**
 * List motors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void CardDevice::listMotors(void)
{
	//Print motor A.
	_PRINT3("%c\tDC\t%d\t%u",motorA.getID(),motorA.getSpeed(),motorA.getElapsedTime());
}

/**
 * List sensors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void CardDevice::listSensors(void)
{
	//Print sensor A1.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorA1.getID()),
		SID_MINOR(sensorA1.getID()),
		sensorA1.isHigh() ? 'H' : 'L',sensorA1.getValue());
	//Print sensor A2.
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorA2.getID()),
		SID_MINOR(sensorA2.getID()),
		sensorA2.isHigh() ? 'H' : 'L',sensorA2.getValue());
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL CardDevice::begin(void)
{
	//Begin.
	SimpleDevice::begin();
#ifdef _DEBUG
	_PRINT0(">CardDevice::begin : begin to execute !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_ECS:
		//Print result.
		_PRINT0("Card");
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
	case CMD_AUTO:
	case CMD_SINGLE:
		//Check sensor A2.
		if(sensorA2.isHigh())
		{
			//Check sensor A1.
			if(sensorA1.isHigh())
			{
				//Set status.
				status = 0;
				//Reset timestamp.
				timestamp = millis();
			}
/*
			else
			{
#ifdef _DEBUG
				//There is a card in it.
				_PRINT0(">CardDevice::begin : there is a card !");
#endif
			}
*/
		}
/*
		else
		{
#ifdef _DEBUG
			//There is no more cards.
			_PRINT0(">CardDevice::begin : there is no more cards !");
#endif
		}
*/
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">CardDevice::begin : unsupported command(\"%s\") !",getDescription());
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
void CardDevice::cancel(void)
{
	//Cancel.
	SimpleDevice::cancel();
#ifdef _DEBUG
	_PRINT0(">CardDevice::cancel : cancel command !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_AUTO:
	case CMD_SINGLE:
		//Clear status.
		status = 0;
		//Stop motor.
		motorA.stop();
		//Print result.
		_PRINT0("OK");
		break;
	default:
		//Print result.
		_PRINT0("Error");
#ifdef _DEBUG
		_PRINT1(">CardDevice::cancel : unsupported command(\"%s\") !",getDescription());
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
_BOOL CardDevice::doLoop(void)
{
	//Do loop.
	SimpleDevice::doLoop();
/*
#ifdef _DEBUG
	_PRINT0(">CardDevice::doLoop : do device loop !");
#endif
*/
	//Check command.
	switch(getCommand())
	{
	case CMD_SINGLE:
		//Check status.
		switch(status)
		{
		case 0:
			//Check counter.
			if(millis() >
				timestamp + 5000)
			{
				//Set status.
				status ++;
				//Start motor A.
				motorA.startCW();
			}
			break;
		case 1:
			//Check counter.
			if(sensorA1.isLow()
				|| sensorA2.isLow())
			{
				//Clear status.
				status ++;
				//Stop motor.
				motorA.stop();
			}
			break;
		case 2:
			//Set idle.
			setIdle(_TRUE); _PRINT0("OK");
			break;
		}
		break;
	case CMD_AUTO:
		//Check status.
		switch(status)
		{
		case 0:
			//Check counter.
			if(millis() >
				timestamp + 5000)
			{
				//Set status.
				status ++;
				//Start motor A.
				motorA.startCW();
			}
			break;
		case 1:
			//Check counter.
			if(sensorA1.isLow()
				|| sensorA2.isLow())
			{
				//Clear status.
				status ++;
				//Stop motor.
				motorA.stop();
			}
			break;
		case 2:
			//Check sensor A2.
			if(sensorA2.isHigh())
			{
				//Check sensor A1.
				if(sensorA1.isHigh())
				{
					//Set status.
					status = 0;
					//Reset timestamp.
					timestamp = millis();
				}
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
		_PRINT1(">CardDevice::doLoop : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
