#include <Global.h>
#include <SimpleString.h>

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define MAX_STRING_LENGTH									256

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleString::SimpleString()
{
	//Set length.
	length = 0;
	//Clear memory.
	memset(buffer,0,MAX_STRING_LENGTH * sizeof(_CHAR));
}
	
/**
 * Default construction.
 *
 * @param string String terminated with '\0'.
 * @return
 *     <p>No results returned.</p>
 */
SimpleString::SimpleString(const _CHAR* string)
{
#ifdef _DEBUG
	_ASSERT(string != _NULL);
	_ASSERT(strlen(string) <= MAX_STRING_LENGTH);
#endif
	//Set length.
	length = strlen(string);
	//Copy string.
	memcpy(buffer,(_OBJECT)string,length * sizeof(_CHAR));
	//Clear buffer.
	memset(buffer,0,(MAX_STRING_LENGTH - length) * sizeof(_CHAR));
}

/**
 * Copy construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleString::SimpleString(const SimpleString& string)
{
	//Set length.
	this->length = string.length;
	//Copy buffer.
	memcpy(this->buffer,string.buffer,MAX_STRING_LENGTH * sizeof(_CHAR));
};

/**
 * Get length of string.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Length of string.</p>
 */
_INTEGER SimpleString::getLength() const
{
	//Return result.
	return length;
}

/**
 * Get buffer of string.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Buffer of string.</p>
 */
const _CHAR* SimpleString::getBuffer() const
{
	//Return result.
	return buffer;
}

/**
 * Whether is full.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if string is full.</p>
 */
_BOOL SimpleString::isFull() const
{
	//Return result.
	return length >= MAX_STRING_LENGTH;
}

/**
 * Whether is empty.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if string is empty.</p>
 */
_BOOL SimpleString::isEmpty() const
{
	//Return result.
	return length <= 0;
}

/**
 * Clear string.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
void SimpleString::clear()
{
	//Set length.
	length = 0;
	//Clear memory.
	memset(buffer,0,MAX_STRING_LENGTH * sizeof(_CHAR));
}

/**
 * Get char at specified index.
 *
 * @param index Index of char.
 * @return
 *     <p>Char at specified index.</p>
 */
_CHAR SimpleString::charAt(_INTEGER index) const
{
#ifdef _DEBUG
	_ASSERT(index >= 0 && index < length);
#endif
	//Return result.
	return buffer[index];
}

/**
 * Append.
 *
 * @param value Char value.
 * @return
 *     <p>Reference of this class.</p>
 */
SimpleString& SimpleString::append(_CHAR value)
{
#ifdef _DEBUG
	_ASSERT(length < MAX_STRING_LENGTH);
#endif
	//Set char.
	buffer[length ++] = value;
	//Return result.
	return *this;
}

/**
 * Get length.
 *
 * @param string String.
 * @return
 *     <p>Length of string.</p>
 */
_SHORT SimpleString::getLength(const _STRING string)
{
	//Length
	_SHORT length = 0;
#ifdef _DEBUG
	_ASSERT(string != _NULL);
#endif
	//Do while.
	for(_SHORT i = 0;string[i] != '\0';i ++) length ++;
	//Return result.
	return length;
}