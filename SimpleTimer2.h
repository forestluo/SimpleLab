#ifndef _SIMPLE_TIMER2_H
#define _SIMPLE_TIMER2_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Timer2
//
////////////////////////////////////////////////////////////////////////////////

class SimpleTimer2
{
public:
	/**
     * Initialize timer.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void initializeTimer(void);

public:
	/**
     * Get milliseconds.
	 *
	 * <p>Milliseconds according to the crystal ocilliator.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Milliseconds.</p>
	 */
	static _UINT32 millis(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !