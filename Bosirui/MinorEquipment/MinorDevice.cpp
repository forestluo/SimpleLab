////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include "MinorDevice.h"

////////////////////////////////////////////////////////////////////////////////
//
// Application
//
////////////////////////////////////////////////////////////////////////////////

//Major Device
static MinorDevice* pMinorDevice = _NULL;

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
MinorDevice::~MinorDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
MinorDevice::MinorDevice()
	: motorG('G',DigitalPin16,DigitalPin17),
	  motorH('H',DigitalPin14,DigitalPin15),
	  motorK('K',DigitalPin20,DigitalPin21),
	  motorL('L',DigitalPin18,DigitalPin19),
	  motorMN('W',DigitalPin24,DigitalPin25),
	  motorX('X',DigitalPin22,DigitalPin23),
		sensorV1(SID('V','1'),AnalogPin0),
		sensorV2(SID('V','2'),AnalogPin1),
		sensorG1(SID('G','1'),DigitalPin26),
		sensorG2(SID('G','2'),DigitalPin27),
		sensorG3(SID('G','3'),DigitalPin28),
		sensorG4(SID('G','4'),DigitalPin29),
		sensorH1(SID('H','1'),DigitalPin30),
		sensorH2(SID('H','2'),DigitalPin31),
		sensorH3(SID('H','3'),DigitalPin32),
		sensorK1(SID('K','1'),DigitalPin38),
		sensorK2(SID('K','2'),DigitalPin39),
		sensorK3(SID('K','3'),DigitalPin40),
		sensorL1(SID('L','1'),DigitalPin42),
		sensorL2(SID('L','2'),DigitalPin43),
		sensorL3(SID('L','3'),DigitalPin44),
		sensorM1(SID('M','1'),DigitalPin46),
		sensorN1(SID('N','1'),DigitalPin47),
		sensorX1(SID('X','1'),DigitalPin48)
{
#ifdef _DEBUG
	_PRINT0(">MinorDevice::MinorDevice : device was initialized !");
#endif
}

/**
 * List motors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void MinorDevice::listMotors(void)
{
	//Print motors.
	_PRINT3("%c\tDC\t%d\t%u",motorG.getID(),motorG.getSpeed(),motorG.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorH.getID(),motorH.getSpeed(),motorH.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorK.getID(),motorK.getSpeed(),motorK.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorL.getID(),motorL.getSpeed(),motorL.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorMN.getID(),motorMN.getSpeed(),motorMN.getElapsedTime());
	_PRINT3("%c\tDC\t%d\t%u",motorX.getID(),motorX.getSpeed(),motorX.getElapsedTime());
}

/**
 * List sensors.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void MinorDevice::listSensors(void)
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
		SID_MAJOR(sensorG1.getID()),
		SID_MINOR(sensorG1.getID()),
		sensorG1.isHigh() ? 'H' : 'L',sensorG1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorG2.getID()),
		SID_MINOR(sensorG2.getID()),
		sensorG2.isHigh() ? 'H' : 'L',sensorG2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorG3.getID()),
		SID_MINOR(sensorG3.getID()),
		sensorG3.isHigh() ? 'H' : 'L',sensorG3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorG4.getID()),
		SID_MINOR(sensorG4.getID()),
		sensorG4.isHigh() ? 'H' : 'L',sensorG4.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorH1.getID()),
		SID_MINOR(sensorH1.getID()),
		sensorH1.isHigh() ? 'H' : 'L',sensorH1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorH2.getID()),
		SID_MINOR(sensorH2.getID()),
		sensorH2.isHigh() ? 'H' : 'L',sensorH2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorH3.getID()),
		SID_MINOR(sensorH3.getID()),
		sensorH3.isHigh() ? 'H' : 'L',sensorH3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorK1.getID()),
		SID_MINOR(sensorK1.getID()),
		sensorK1.isHigh() ? 'H' : 'L',sensorK1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorK2.getID()),
		SID_MINOR(sensorK2.getID()),
		sensorK2.isHigh() ? 'H' : 'L',sensorK2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorK3.getID()),
		SID_MINOR(sensorK3.getID()),
		sensorK3.isHigh() ? 'H' : 'L',sensorK3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorL1.getID()),
		SID_MINOR(sensorL1.getID()),
		sensorL1.isHigh() ? 'H' : 'L',sensorL1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorL2.getID()),
		SID_MINOR(sensorL2.getID()),
		sensorL2.isHigh() ? 'H' : 'L',sensorL2.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorL3.getID()),
		SID_MINOR(sensorL3.getID()),
		sensorL3.isHigh() ? 'H' : 'L',sensorL3.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorM1.getID()),
		SID_MINOR(sensorM1.getID()),
		sensorM1.isHigh() ? 'H' : 'L',sensorM1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorN1.getID()),
		SID_MINOR(sensorN1.getID()),
		sensorN1.isHigh() ? 'H' : 'L',sensorN1.getValue());
	_PRINT4("%c%c\tD\t%c\t%d",
		SID_MAJOR(sensorX1.getID()),
		SID_MINOR(sensorX1.getID()),
		sensorX1.isHigh() ? 'H' : 'L',sensorX1.getValue());
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL MinorDevice::begin(void)
{
	//Begin.
	SimpleDevice::begin();
#ifdef _DEBUG
	_PRINT0(">MinorDevice::begin : begin to execute !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_ECS:
		//Print result.
		_PRINT0("Minor");
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
	case CMD_STARTGCW:
		//Start motor.
		motorG.startCCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STARTGCCW:
		//Start motor.
		motorG.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STOPG:
		//Start motor.
		motorG.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STARTH:
		//Start motor.
		motorH.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STOPH:
		//Start motor.
		motorH.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_PUSHPR:
		//Check L1.
		if(sensorL1.isLow())
		{
			//Print result.
			_PRINT0("Error");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Check K2.
			if(sensorK2.isLow())
			{
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			else
			{
				//Stop motor.
				motorK.stop();
				//Start motor.
				motorK.startCCW();
			}
		}
		break;
	case CMD_PULLPR:
		//Get value.
		if(sensorK1.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorK.stop();
			//Start motor.
			motorK.startCW();
		}
		break;
	case CMD_OPENM:
		//Check L2.
		if(sensorL2.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorL.stop();
			//Start motor.
			motorL.startCW();
		}
		break;
	case CMD_CLOSEM:
		//Check L1.
		if(sensorL1.isLow())
		{
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Stop motor.
			motorL.stop();
			//Start motor.
			motorL.startCCW();
		}
		break;
	case CMD_STARTX:
		//Start motor.
		motorX.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STOPX:
		//Stop motor.
		motorX.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STARTMNCW:
		//Start motor.
		motorMN.startCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STARTMNCCW:
		//Start motor.
		motorMN.startCCW();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_STOPMN:
		//Stop motor.
		motorMN.stop();
		//Print result.
		_PRINT0("OK");
		//Set idle.
		setIdle(_TRUE);
		break;
	case CMD_PPF:
		//Set status.
		status = 0;
		//Start motor.
		motorMN.startCW();
		break;
	case CMD_TPFM:
		//Set status.
		status = 0;
		//Start motor.
		motorMN.startCW();
		break;
	case CMD_SVP:
		//Set status.
		status = 0;
		//Start motor.
		motorG.startCCW();
		break;
	case CMD_SAP:
		//Set status.
		status = 0;
		//Start motor.
		motorH.startCW();
		motorG.startCCW();
		break;
	case CMD_TPE:
		//Set status.
		status = 0;
		//Start motor.
		motorX.startCW();
		motorH.startCW();
		break;
	default:
		//Print result.
		_PRINT0("Error");
		//Set idle.
		setIdle(_TRUE);
#ifdef _DEBUG
		_PRINT1(">MinorDevice::begin : unsupported command(\"%s\") !",getDescription());
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
void MinorDevice::cancel(void)
{
	//Cancel.
	SimpleDevice::cancel();
#ifdef _DEBUG
	_PRINT0(">MinorDevice::cancel : cancel command !");
#endif
	//Check command.
	switch(getCommand())
	{
	case CMD_PUSHPR:
	case CMD_PULLPR:
		//Stop motor.
		motorK.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_OPENM:
	case CMD_CLOSEM:
		//Stop motor.
		motorL.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_PPF:
	case CMD_TPFM:
		//Stop motor.
		motorMN.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_SVP:
		//Stop motor.
		motorG.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_SAP:
		//Stop motor.
		motorH.stop();
		motorG.stop();
		//Print result.
		_PRINT0("OK");
		break;
	case CMD_TPE:
		//Set status.
		status = 0;
		//Stop motor.
		motorX.stop();
		motorH.stop();
		//Print result.
		_PRINT0("OK");
		break;
	default:
		//Print result.
		_PRINT0("Error");
#ifdef _DEBUG
		_PRINT1(">MinorDevice::cancel : unsupported command(\"%s\") !",getDescription());
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
_BOOL MinorDevice::doLoop(void)
{
	//Do loop.
	SimpleDevice::doLoop();
/*
#ifdef _DEBUG
	_PRINT0(">MinorDevice::doLoop : do device loop !");
#endif
*/
	//Check command.
	switch(getCommand())
	{
	case CMD_PUSHPR:
		//Check L1.
		if(sensorL1.isLow())
		{
			//Stop motor.
			motorK.stop();
			//Print result.
			_PRINT0("Error");
			//Set idle.
			setIdle(_TRUE);
		}
		else
		{
			//Get value.
			if(sensorK2.isLow())
			{
				//Stop motor.
				motorK.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
		}
		break;
	case CMD_PULLPR:
		//Get value.
		if(sensorK1.isLow())
		{
			//Stop motor.
			motorK.stop();
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_OPENM:
		//Check L2.
		if(sensorL2.isLow())
		{
			//Stop motor.
			motorL.stop();
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_CLOSEM:
		//Check L1.
		if(sensorL1.isLow())
		{
			//Stop motor.
			motorL.stop();
			//Print result.
			_PRINT0("OK");
			//Set idle.
			setIdle(_TRUE);
		}
		break;
	case CMD_PPF:
		//Check status.
		switch(status)
		{
		case 0:
			//Check M1.
			if(sensorM1.isLow()) status ++;
			break;
		case 1:
			//Check N1.
			if(sensorN1.isHigh())
			{
				//Change status.
				status ++;
				//Stop motor.
				motorMN.stop();
				//Start motor.
				motorMN.startCCW();
			}
			break;
		case 2:
			//Check L3.
			if(sensorL3.isLow()) status ++;
			break;
		case 3:
			//Check L3.
			if(sensorL3.isHigh())
			{
				//Change status.
				status ++;
				//Stop motor.
				motorMN.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_TPFM:
		//Check status.
		switch(status)
		{
		case 0:
			//Check M1.
			if(sensorM1.isLow()) status ++;
			break;
		case 1:
			//Check M1.
			if(sensorM1.isHigh())
			{
				//Change status.
				status ++;
				//Stop motor.
				motorMN.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_SVP:
		//Check status.
		switch(status)
		{
		case 0:
			//Check G1 and G3.
			if(sensorG1.isLow() &&
				sensorG3.isLow()) status ++;
			break;
		case 1:
			//Check G1 and G3.
			if(sensorG1.isHigh() &&
				sensorG3.isHigh())
			{
				//Change status.
				status ++;
				//Stop motor.
				motorG.stop();
				//Start motor.
				motorG.startCW();
			}
			break;
		case 2:
			//Check G1 and G3.
			if(sensorG1.isLow() &&
				sensorG3.isLow()) status ++;
			break;
		case 3:
			//Check G1 and G3.
			if(sensorG1.isHigh() &&
				sensorG3.isHigh())
			{
				//Change status.
				status ++;
				//Set timestamp.
				timestamp = millis();
			}
			break;
		case 4:
			//Check timestamp.
			if(millis() > timestamp + 2000)
			{
				//Change status.
				status ++;
				//Stop motor.
				motorG.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_SAP:
		//Check status.
		switch(status)
		{
		case 0:
			//Check H1.
			if(sensorH1.isLow()) status ++;
			break;
		case 1:
			//Check H1.
			if(sensorH1.isHigh())
			{
				//Change status.
				status ++;
				//Stop motor.
				motorH.stop();
				motorG.stop();
				//Print result.
				_PRINT0("OK");
				//Set idle.
				setIdle(_TRUE);
			}
			break;			
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		break;
	case CMD_TPE:
		//Check status.
		switch(status & 0x0F)
		{
		case 0x00:
			//Check H3.
			if(sensorH3.isLow())
			{
				//Change status.
				status |= 0x01;
			}
			break;
		case 0x01:
			//Check H3.
			if(sensorH3.isHigh())
			{
				//Change status.
				status |= 0x02;
				//Stop motor.
				motorH.stop();
			}
			break;
		case 0x03:
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		//Check status.
		switch((status >> 4) & 0x0F)
		{
		case 0x00:
			//Check X1.
			if(sensorX1.isLow())
			{
				//Change status.
				status |= 0x10;
			}
			break;
		case 0x01:
			//Check X1.
			if(sensorX1.isHigh())
			{
				//Change status.
				status |= 0x20;
				//Stop motor.
				motorX.stop();
			}
			break;
		case 0x03:
			break;
		default:
#ifdef _DEBUG
			_PRINT2(">MinorDevice::doLoop(\"%s\") : invalid status(%d) !",getDescription(),status);
#endif
			return _FALSE;
		}
		//Check status.
		if(status == 0x33)
		{
			//Stop motor.
			motorH.stop();
			motorX.stop();
			//Print result.
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
		_PRINT1(">MinorDevice::doLoop : unsupported command(\"%s\") !",getDescription());
#endif
		return _FALSE;
	}
	//Return true.
	return _TRUE;
}
