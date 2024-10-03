#ifndef _CONSOLE_FILE_H
#define _CONSOLE_FILE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <FileModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// Console File
//
////////////////////////////////////////////////////////////////////////////////

class ConsoleFile
{
private:
	/**
	 * Write index.
	 */
	static _UINT8 writeIndex;

public:
	/**
     * Initialize.
	 *
	 * @param fileModule File module.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initialize(FileModule& fileModule);

	/**
     * Write into console buffer.
	 *
	 * @param fileModule File module.
	 * @param string String.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void writeConsole(FileModule& fileModule,_CHAR* string);

	/**
     * Read console.
	 *
	 * <p>The maximum length is 32.</p>
	 *
	 * @param fileModule File module.
	 * @param index Index of string.
	 * @param string String.
	 * @return
	 *     <p>Return true, if there is a string.</p>
	 */
	static void readConsole(FileModule& fileModule,_UINT8 index,_CHAR* string);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !