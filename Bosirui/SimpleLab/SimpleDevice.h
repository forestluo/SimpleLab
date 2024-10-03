#ifndef _SIMPLE_DEVICE_H
#define _SIMPLE_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

//Supported by all
#define CMD_ECS												0
#define CMD_CEC												1
#define CMD_LAM												2
#define CMD_LAS												3
//Supported by major board
#define CMD_SSECW											4
#define CMD_SSECCW											5
#define CMD_SSE												6
#define CMD_SSFCW											7
#define CMD_SSFCCW											8
#define CMD_SSF												9
#define CMD_UPT												10
#define CMD_LPB												11
#define CMD_WPP												12
#define CMD_TES1SP											13
#define CMD_TES2SP											14
#define CMD_TESCP											15
#define CMD_WPC												16
#define CMD_TWSCP											17
#define CMD_TSPPE											18
#define CMD_PUSHBR											19
#define CMD_PULLBR											20
//Supported by minor board
#define CMD_STARTGCW										21
#define CMD_STARTGCCW										22
#define CMD_STOPG											23
#define CMD_STARTH											24
#define CMD_STOPH											25
#define CMD_PUSHPR											26
#define CMD_PULLPR											27
#define CMD_OPENM											28
#define CMD_OPENMS											29
#define CMD_CLOSEM											30
#define CMD_STARTX											31
#define CMD_STOPX											32
#define CMD_STARTMNCW										33
#define CMD_STARTMNCCW										34
#define CMD_STOPMN											35
#define CMD_PPF												36
#define CMD_TPFM											37
#define CMD_SVP												38
#define CMD_SAP												39
#define CMD_TPE												40
//Supported by card, cover and film board
#define CMD_AUTO											41
#define CMD_SINGLE											42

////////////////////////////////////////////////////////////////////////////////
//
// Simple Device
//
////////////////////////////////////////////////////////////////////////////////

class SimpleDevice
{
private:
	/**
	 * Idle.
	 *
	 * <p>Whether is idle.</p>
	 */
	_BOOL idle;
	/**
	 * Command.
	 */
	_INT8 command;
	/**
	 * Timestamp.
	 *
	 * <p>Timestamp of execute.</p>
	 */
	_UINT32 timestamp;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~SimpleDevice(void);

	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleDevice();

public:
	/**
     * Whether is idle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Whether is idle.</p>
	 */
	_BOOL isIdle(void);

protected:
	/**
	 * Whether is timeout.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if is timeout.</p>
	 */
	_BOOL isTimeout(void);

	/**
	 * Set idle.
	 *
	 * @param idle Idle status.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setIdle(_BOOL idle);

public:
	/**
	 * Get command.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Current command.</p>
	 */
	_INT8 getCommand(void);

	/**
	 * Get command description.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Description of command.</p>
	 */
	_STRING getDescription(void);

	/**
	 * Set command.
	 *
	 * @param command Command.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setCommand(_INT8 command);

public:
	/**
     * Parse string.
	 *
	 * @param string Command string.
	 * @return
	 *     <p>Return true, if successfully parsed.</p>
	 */
	_BOOL parse(const _STRING string);

public:
	/**
     * Begin to execute.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL begin(void);

	/**
	 * Cancel.
	 *
	 * @param None No results returned.</p>
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void cancel(void);

	/**
	 * Do loop.
	 *
	 * @param None No results returned.</p>
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	virtual _BOOL doLoop(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !