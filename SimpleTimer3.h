#ifndef _SIMPLE_TIMER3_H
#define _SIMPLE_TIMER3_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple Timer3
//
////////////////////////////////////////////////////////////////////////////////

class SimpleTimer3
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
     * Reset timers.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void reset(void);

	/**
     * Get milliseconds.
	 *
	 * <p>Milliseconds according to the crystal ocilliator.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Milliseconds.</p>
	 */
	static unsigned long millis(void);

	/**
     * Get microseconds.
	 *
	 * <p>Microseconds according to the crystal ocilliator.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Microseconds.</p>
	 */
	static unsigned long micros(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !