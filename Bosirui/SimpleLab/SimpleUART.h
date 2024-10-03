#ifndef _SIMPLE_UART_H
#define _SIMPLE_UART_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple UART
//
////////////////////////////////////////////////////////////////////////////////

class SimpleUART
{
private:
	/**
	 * Position.
	 */
	_UINT8 position;
	/**
	 * Buffer.
	 */
	_CHAR buffer[32];

public:
	/**
	 * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleUART(void);

public:
	/**
	 * Whether line is ready.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if line is ready.</p>
	 */
	_BOOL lineReady(void);

	/**
	 * Get string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Pointer of string.</p>
	 */
	const _STRING getString(void) const;
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
