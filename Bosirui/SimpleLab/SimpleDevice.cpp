////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <Memory.h>

#include <SimpleDevice.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Supported by all
const char _cmd_0[]											= "ecs";
const char _cmd_1[]											= "cec";
const char _cmd_2[]											= "lam";
const char _cmd_3[]											= "las";
//Supported by marjor board
const char _cmd_4[]											= "ssecw";
const char _cmd_5[]											= "sseccw";
const char _cmd_6[]											= "sse";
const char _cmd_7[]											= "ssfcw";
const char _cmd_8[]											= "ssfccw";
const char _cmd_9[]											= "ssf";
const char _cmd_10[]										= "upt";
const char _cmd_11[]										= "lpb";
const char _cmd_12[]										= "wpp";
const char _cmd_13[]										= "tes1sp";
const char _cmd_14[]										= "tes2sp";
const char _cmd_15[]										= "tescp";
const char _cmd_16[]										= "wpc";
const char _cmd_17[]										= "twscp";
const char _cmd_18[]										= "tsppe";
const char _cmd_19[]										= "pushbr";
const char _cmd_20[]										= "pullbr";
//Supported by minor board
const char _cmd_21[]										= "startgcw";
const char _cmd_22[]										= "startgccw";
const char _cmd_23[]										= "stopg";
const char _cmd_24[]										= "starth";
const char _cmd_25[]										= "stoph";
const char _cmd_26[]										= "pushpr";
const char _cmd_27[]										= "pullpr";
const char _cmd_28[]										= "openm";
const char _cmd_29[]										= "openms";
const char _cmd_30[]										= "closem";
const char _cmd_31[]										= "startx";
const char _cmd_32[]										= "stopx";
const char _cmd_33[]										= "startmncw";
const char _cmd_34[]										= "startmnccw";
const char _cmd_35[]										= "stopmn";
const char _cmd_36[]										= "ppf";
const char _cmd_37[]										= "tpfm";
const char _cmd_38[]										= "svp";
const char _cmd_39[]										= "sap";
const char _cmd_40[]										= "tpe";
//Supported by card, cover and film board
const char _cmd_41[]										= "auto";
const char _cmd_42[]										= "single";

const char* COMMAND_TABLE[] =
{
	_cmd_0,_cmd_1,_cmd_2,_cmd_3,_cmd_4,_cmd_5,_cmd_6,_cmd_7,_cmd_8,_cmd_9,
	_cmd_10,_cmd_11,_cmd_12,_cmd_13,_cmd_14,_cmd_15,_cmd_16,_cmd_17,_cmd_18,_cmd_19,
	_cmd_20,_cmd_21,_cmd_22,_cmd_23,_cmd_24,_cmd_25,_cmd_26,_cmd_27,_cmd_28,_cmd_29,
	_cmd_30,_cmd_31,_cmd_32,_cmd_33,_cmd_34,_cmd_35,_cmd_36,_cmd_37,_cmd_38,_cmd_39,
	_cmd_40,_cmd_41,_cmd_42
};

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
SimpleDevice::~SimpleDevice(void)
{

}

/**
 * Default construction.
 *
 * @param None No parameter needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleDevice::SimpleDevice()
{
	//Set idle.
	idle = _TRUE;
	//Clear command.
	command = -1;
	//Clear timestamp.
	timestamp = 0;
}

/**
 * Whether is idle.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Whether is idle.</p>
 */
_BOOL SimpleDevice::isIdle(void)
{
	//Return result.
	return idle;
}

/**
 * Set idle.
 *
 * @param idle Idle status.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::setIdle(_BOOL idle)
{
	//Set idle.
	this->idle = idle;
}

/**
 * Whether sample is timeout.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if sample is timeout.</p>
 */
_BOOL SimpleDevice::isTimeout(void)
{
	//Return result.
	return millis() <= timestamp + 1000 ? _FALSE : _TRUE;
}

/**
 * Get command.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Current command.</p>
 */
_INT8 SimpleDevice::getCommand(void)
{
	//Return result.
	return command;
}

/**
 * Get command description.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Description of command.</p>
 */
_STRING SimpleDevice::getDescription(void)
{
#ifdef _DEBUG
	_ASSERT(command >= 0 && command <= 42);
#endif
	//Return result.
	return COMMAND_TABLE[command];
}

/**
 * Set command.
 *
 * @param command Command.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::setCommand(_INT8 command)
{
#ifdef _DEBUG
	_ASSERT(command >= 0 && command <= 42);
#endif
	this->command = command;
}

/**
 * Parse string.
 *
 * @param string Command string.
 * @return
 *     <p>Return true, if successfully parsed.</p>
 */
_BOOL SimpleDevice::parse(const _STRING string)
{
#ifdef _DEBUG
	_ASSERT(string != _NULL);
#endif
	//Clear command.
	command = -1;
	//Do while.
	for(int i = 0;i <= 42;i ++)
	{
/*
#ifdef _DEBUG
		_PRINT1(">SimpleDevice::parse : try command(\"%s\") !",COMMAND_TABLE[i]);
#endif
*/
		//Check comamnd.
		if(strcmp(COMMAND_TABLE[i],string) == 0)
		{
			//Set command.
			command = i;
#ifdef _DEBUG
			_PRINT1(">SimpleDevice::parse : command(\"%s\") received !",string);
#endif
			return _TRUE;
		}
	}
#ifdef _DEBUG
	_PRINT1(">SimpleDevice::parse : invalid command(\"%s\") !",string);
#endif
	return _FALSE;
}

/**
 * Begin to execute.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL SimpleDevice::begin(void)
{
	//Clear idle.
	idle = _FALSE;
	//Set timestamp.
	timestamp = millis();
#ifdef _DEBUG
	_ASSERT(command >= 0 && command <= 42);
#endif
	//Print back.
	_PRINT1("+%s",COMMAND_TABLE[command]);
#ifdef _DEBUG
	_PRINT0(">SimpleDevice::begin : begin to execute !");
#endif
	return _TRUE;
}

/**
 * Cancel.
 *
 * @param None No results returned.</p>
 * @return
 *     <p>No results returned.</p>
 */
void SimpleDevice::cancel(void)
{
	//Set idle.
	idle = _TRUE;
	//Clear timestamp.
	timestamp = 0;
#ifdef _DEBUG
	_ASSERT(command >= 0 && command <= 42;
	_PRINT1(">SimpleDevice::cancel : command(\"%s\") canceled !",COMMAND_TABLE[command]);
#endif
}

/**
 * Do loop.
 *
 * @param None No results returned.</p>
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL SimpleDevice::doLoop(void)
{
	//Check timeout.
	if(isTimeout())
	{
		//Reset timer.
		timestamp = millis();
#ifdef _DEBUG
		_ASSERT(command >= 0 && command <= 42);
#endif
		//Print back.
		_PRINT1("+%s",COMMAND_TABLE[command]);
#ifdef _DEBUG
		_PRINT1(">SimpleDevice::doLoop : command(\"%s\") timeout !",COMMAND_TABLE[command]);
#endif
	}
	//Return true.
	return _TRUE;
}
