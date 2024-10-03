////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>

#include <SPI.h>
#include <DataFlash.h>

#include <SPIChip.h>
#include <ChipAT45DB161D.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define DATA_FLASH(o)										((DataFlash *)(o))

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
ChipAT45DB161D::~ChipAT45DB161D(void)
{
	//Check result.
	if(chipCore != _NULL)
	{
		//Delete object.
		delete DATA_FLASH(chipCore);
		//Clear object.
		chipCore = (DataFlash *)_NULL;
	}
}

/**
 * Default construction.
 *
 * @param selectedPin Pin for selection.
 * @return
 *     <p>No results returned.</p>
 */
ChipAT45DB161D::ChipAT45DB161D(DigitalPin selectedPin)
	: SPIChip(selectedPin)
{
	//Set default index.
	index = 0;
	//Create data flash.
	chipCore = new DataFlash();
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif
	//Initialize data flash.
	DATA_FLASH(chipCore)->setup(selectedPin,
								DigitalPin26,/*It has no use*/
								DigitalPin27/*It has no use*/);
}

/**
 * Initialize.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipAT45DB161D::initialize(void)
{
	//ID of data flash.
	DataFlash::ID id;
	//Flag.
	_BOOL flag = _TRUE;
#ifdef _DEBUG
	_ASSERT(chipCore != _NULL);
#endif

	//Select chip.
	selectChip();
	//Read status register.
	_UINT8 status = DATA_FLASH(chipCore)->status();
#ifdef _DEBUG
	//Print.
	_PRINT1("ChipAT45DB161D::initialize : status(0x%02x) !",status);
#endif
	//Read manufacturer and device ID.
	DATA_FLASH(chipCore)->readID(id);
	/*
	//Check manufacture.
	if(id.manufacturer != 0x1F)
	{
		//Set flag.
		flag = _FALSE;
#ifdef _DEBUG
		//Print.
		//Should be 0x1F.
		_PRINT1("ChipAT45DB161D::initialize : invalid manufacturer(0x%02x) !",id.manufacturer);
#endif
	}
	//Check device id.
	else if(id.device[0] != 0x1F || id.device[1] != 0x00)
	{
		//Set flag.
		//flag = _FALSE;
#ifdef _DEBUG
		//Print.
		//Should be 0x1F00.
		_PRINT2("ChipAT45DB161D::initialize : invalid device_id(0x%02x%02x) !",id.device[0],id.device[1]);
#endif
	}
	//Check extended information length.
	else if(id.extendedInfoLength != 0x00)
	{
		//Set flag.
		//flag = _FALSE;
#ifdef _DEBUG
		//Print.
		//Should be 0x00.
		_PRINT1("ChipAT45DB161D::initialize : invalid extended_string_length(0x%02x) !",id.extendedInfoLength);
#endif
	}
	*/
	//Unselect chip.
	unselectChip();
#ifdef _DEBUG
	//Print.
	_PRINT0("ChipAT45DB161D::initialize : flash was initialized !");
#endif
	//Return flag.
	return flag;
}

/**
 * Seek.
 *
 * @param dataAddress Address of data.
 * @param page Page number.
 * @param offset Offset of page.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::seek(_UINT32 dataAddress,_UINT32& page,_UINT32& offset)
{
	//Adjust address.
	//Only 16M bytes supported.
	dataAddress &= 0x0FFFFFFF;
	//Calculate page number.
	//	page = dataAddress / 512
	page = dataAddress >> 9;
#ifdef _DEBUG
	//Check page.
	if(page >= 4096)
	{
		//Print.
		_PRINT2("ChipAT45DB161D::seek : invalid page(%d) of address(0x%08lx) !",page,dataAddress);
	}
	_ASSERT(page <= 4096);
#endif
	//Calculate page offset.
	//	offset = dataAddress % 512
	offset = dataAddress & 0x1FF;
}

/**
 * Read uint8.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT8 ChipAT45DB161D::readUint8(_UINT32 dataAddress)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

	//Value.
	_UINT8 value;
#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferRead(index & 0x01,offset);	
	//Set result.
	value = SPI.transfer(0xFF);
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
	//Return result.
	return value;
}

/**
 * Read uint16.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT16 ChipAT45DB161D::readUint16(_UINT32 dataAddress)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

	//Value.
	_UINT16 value;
#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferRead(index & 0x01,offset);	
	//Set result.
	value  = ((_UINT16)SPI.transfer(0xFF) << 8) & 0xFF00;
	value |=  (_UINT16)SPI.transfer(0xFF)       & 0x00FF;
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
	//Return result.
	return value;
}

/**
 * Read uint32.
 *
 * @param dataAddress Address of data.
 * @return
 *     <p>Value of data.</p>
 */
_UINT32 ChipAT45DB161D::readUint32(_UINT32 dataAddress)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

	//Value.
	_UINT32 value;
#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferRead(index & 0x01,offset);	
	//Set result.
	value  = ((_UINT32)SPI.transfer(0xFF) << 24) & 0xFF000000;
	value |= ((_UINT32)SPI.transfer(0xFF) << 16) & 0x00FF0000;
	value |= ((_UINT32)SPI.transfer(0xFF) <<  8) & 0x0000FF00;
	value |=  (_UINT32)SPI.transfer(0xFF)        & 0x000000FF;
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
	//Return result.
	return value;
}

/**
 * Read buffer.
 *
 * @param dataAddress Address of data.
 * @param buffer Buffer.
 * @param length Length of buffer.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::readBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG
	_ASSERT(buffer != _NULL && length > 0);
#endif

	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferRead(index & 0x01,offset);
	//Position.
	_UINT16 position = 0;
	//Do while.
	while(length > 0 && offset < 512)
	{
		//Sub length.
		length --;
		//Add offset.
		offset ++;
		//Read byte.
		buffer[position ++] = SPI.transfer(0xFF);
	}
	//Check length.
	while(length > 512)
	{
		//Add page.
		page ++;
		//Map page to buffer.
		DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
		//Set offset of page.
		DATA_FLASH(chipCore)->bufferRead(index & 0x01,0);
		//Do while.
		for(offset = 0;offset < 512;offset ++)
		{
			//Read page.
			buffer[position ++] = SPI.transfer(0xFF);
		}
		//Sub length.
		length -= 512;
	}
	//Check length.
	if(length > 0)
	{
		//Add page.
		page ++;
		//Map page to buffer.
		DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
		//Set offset of page.
		DATA_FLASH(chipCore)->bufferRead(index & 0x01,0);
		//Do while.
		while(length > 0)
		{
			//Sub length.
			length --;
			//Read byte.
			buffer[position ++] = SPI.transfer(0xFF);
		}
	}
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}

/**
 * Write uint8.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::writeUint8(_UINT32 dataAddress,_UINT8 value)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferWrite(index & 0x01,offset);	
	//Set result.
	SPI.transfer(value);
	//Map buffer to page.
	DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}

/**
 * Write uint16.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::writeUint16(_UINT32 dataAddress,_UINT16 value)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferWrite(index & 0x01,offset);	
	//Set result.
	SPI.transfer((_UINT8)(value >> 8));
	//Set result.
	SPI.transfer((_UINT8)value);
	//Map buffer to page.
	DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}

/**
 * Write uint32.
 *
 * @param dataAddress Address of data.
 * @param value Value of data.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::writeUint32(_UINT32 dataAddress,_UINT32 value)
{
	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferWrite(index & 0x01,offset);
	//Set result.
	SPI.transfer((_UINT8)(value >> 24));
	//Set result.
	SPI.transfer((_UINT8)(value >> 16));
	//Set result.
	SPI.transfer((_UINT8)(value >> 8));
	//Set result.
	SPI.transfer((_UINT8)value);
	//Map buffer to page.
	DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}

/**
 * Write buffer.
 *
 * @param dataAddress Address of data.
 * @param buffer Buffer.
 * @param length Length of buffer.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::writeBuffer(_UINT32 dataAddress,_BUFFER buffer,_UINT16 length)
{
#ifdef _DEBUG
	_ASSERT(buffer != _NULL && length > 0);
#endif

	//Page and offset.
	_UINT32 page,offset;
	//Seek address.
	seek(dataAddress,page,offset);

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferWrite(index & 0x01,offset);
	//Position.
	_UINT16 position = 0;
	//Do while.
	while(length > 0 && offset < 512)
	{
		//Sub length.
		length --;
		//Add offset.
		offset ++;
		//Write byte.
		SPI.transfer(buffer[position ++]);
	}
	//Map buffer to page.
	DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	//Check length.
	while(length > 512)
	{
		//Add page.
		page ++;
		//Map page to buffer.
		DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
		//Set offset of page.
		DATA_FLASH(chipCore)->bufferWrite(index & 0x01,0);
		//Do while.
		for(offset = 0;offset < 512;offset ++)
		{
			//Write page.
			SPI.transfer(buffer[position ++]);
		}
		//Sub length.
		length -= 512;
		//Map buffer to page.
		DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	}
	//Check length.
	if(length > 0)
	{
		//Add page.
		page ++;
		//Map page to buffer.
		DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
		//Set offset of page.
		DATA_FLASH(chipCore)->bufferWrite(index & 0x01,0);
		//Do while.
		while(length > 0)
		{
			//Sub length.
			length --;
			//Write byte.
			SPI.transfer(buffer[position ++]);
		}
		//Map buffer to page.
		DATA_FLASH(chipCore)->bufferToPage(index & 0x01,page);
	}
	//End with wait.
	//DATA_FLASH(chipCore)->endAndWait();
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}

/**
 * Load HZK bitmap.
 *
 * @param hzCode GB2312 code.
 * @param bitmap HZK bitmap.
 * @return
 *     <p>No results returned.</p>
 */
void ChipAT45DB161D::loadHZKBitmap(_UINT16 hzCode,_HZKBITMAP bitmap)
{
	//WCode.
	_UINT32 wCode = (_UINT8)hzCode - 0xA0;
	//QCode.
	_UINT32 qCode = (_UINT8)(hzCode >> 8) - 0xA0;
	//Calculate position.
	_UINT32 position = ((qCode - 1) * 94 + wCode - 1) << 5;
#ifdef _DEBUG
	//Check position.
	if(position >= 267616)
	{
		//Print.
		_PRINT2("ChipAT45DB161D::loadHZKBitmap : invalid position(0x%08lx) of hzCode(0x%04x) !",position,hzCode);
	}
	_ASSERT(position < 267616);
#endif
	//Page and offset.
	_UINT32 page, offset;
	//Seek position.
	seek(position,page,offset);
#ifdef _DEBUG
	//Check offset.
	if(offset > 480)
	{
		//Print.
		_PRINT2("ChipAT45DB161D::loadHZKBitmap : invalid offset(%d) of position(0x%08lx) !",offset,position);
	}
	_ASSERT(offset <= 480);
#endif

#ifdef _DEBUG
	//Assert condition.
	_ASSERT(chipCore != _NULL);
#endif
	//Select chip.
	selectChip();
	//Map page to buffer.
    DATA_FLASH(chipCore)->pageToBuffer(page,index & 0x01);
	//Set offset of page.
	DATA_FLASH(chipCore)->bufferRead(index & 0x01,offset);
	//Do while.
	for(int i = 0;i < sizeof(_HZKBITMAP);i ++)
	{
		//Set result.
		bitmap[i] = SPI.transfer(0xFF);
	}
	//Unselect chip.
	unselectChip();
	//Add index.
	index ++;
}