////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <HZK16File.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Definitions
//
////////////////////////////////////////////////////////////////////////////////

//HZK16 Address
#define HZK16_ADDRESS										0
//HZK16 File Size
#define HZK16_FILE_SIZE										267616
//HZK16 File Page Count
#define HZK16_FILE_PAGE_COUNT								523

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Load HZK bitmap.
 *
 * @param fileModule File module.
 * @param hzCode GB2312 code.
 * @param bitmap HZK bitmap.
 * @return
 *     <p>No results returned.</p>
 */
void HZK16File::loadHZKBitmap(FileModule& fileModule,_UINT16 hzCode,_HZKBITMAP bitmap)
{
	//WCode.
	_UINT32 wCode = (_UINT8)hzCode - 0xA0;
	//QCode.
	_UINT32 qCode = (_UINT8)(hzCode >> 8) - 0xA0;
	//Calculate position.
	_UINT32 position = ((qCode - 1) * 94 + wCode - 1) << 5;
#ifdef _DEBUG
	//Check position.
	if(position >= HZK16_FILE_SIZE)
	{
		//Print.
		_PRINT2("HZK16File::loadHZKBitmap : invalid position(0x%08lx) of hzCode(0x%04x) !",position,hzCode);
	}
	_ASSERT(position < HZK16_FILE_SIZE);
#endif
	//Read buffer.
	fileModule.readBuffer(position,(_BUFFER)bitmap,sizeof(_HZKBITMAP));
}

/**
 * Load HZK bitmaps.
 *
 * @param fileModule File module.
 * @param hzks GB2312 codes.
 * @param bitmaps HZK bitmaps.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
void HZK16File::loadHZKBitmaps(FileModule& fileModule,const _CHAR* hzks,_HZKBITMAP* bitmaps)
{
	//Check result.
	if(hzks != NULL && hzks[0] != 0x00)
	{
		//Do while.
		for(int i = 0;i < 8;i ++,hzks += 2)
		{
			//Check hzks.
			if(hzks[0] == 0x00 || hzks[1] == 0x00) break;
			//Load hzk bitmap.
			loadHZKBitmap(fileModule,(((_UINT16)hzks[0] << 8) & 0xFF00) | ((_UINT16)hzks[1] & 0x00FF),bitmaps[i]);
		}
	}
}
