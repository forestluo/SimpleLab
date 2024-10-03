#ifndef _HZK16_FILE_H
#define _HZK16_FILE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <FileModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// HZK16 File
//
////////////////////////////////////////////////////////////////////////////////

class HZK16File
{
public:
	/**
     * Load HZK bitmap.
	 *
	 * @param fileModule File module.
	 * @param hzCode GB2312 code.
	 * @param bitmap HZK bitmap.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void loadHZKBitmap(FileModule& fileModule,_UINT16 hzCode,_HZKBITMAP bitmap);

	/**
     * Load HZK bitmaps.
	 *
	 * <p>Load not more than 8 HZKs.</p>
	 *
	 * @param fileModule File module.
	 * @param hzCode GB2312 code.
	 * @param bitmaps HZK bitmaps.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void loadHZKBitmaps(FileModule& fileModule,const _CHAR* hzks,_HZKBITMAP* bitmaps);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !