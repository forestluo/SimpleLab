#ifndef _SIMPLE_STRING_H
#define _SIMPLE_STRING_H

////////////////////////////////////////////////////////////////////////////////
//
// Simple String
//
////////////////////////////////////////////////////////////////////////////////

class SimpleString
{
private:
	/**
     * Length of string.
	 */
	_INTEGER length;
	/**
	 * Buffer of string.
	 */
	_CHAR buffer[256];

public:
	/**
     * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleString();
	
	/**
	 * Default construction.
	 *
	 * @param string String terminated with '\0'.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleString(const _CHAR* string);

	/**
     * Copy construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleString(const SimpleString& string);

public:
	/**
     * Get length of string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Length of string.</p>
	 */
	_INTEGER getLength() const;
	
	/**
     * Get buffer of string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Buffer of string.</p>
	 */
	const _CHAR* getBuffer() const;

public:
	/**
     * Whether is full.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if string is full.</p>
	 */
	_BOOL isFull() const;

	/**
     * Whether is empty.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if string is empty.</p>
	 */
	_BOOL isEmpty() const;

public:
	/**
     * Clear string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clear();

	/**
	 * Get char at specified index.
	 *
	 * @param index Index of char.
	 * @return
	 *     <p>Char at specified index.</p>
	 */
	_CHAR charAt(_INTEGER index) const;

public:
	
	/**
	 * Append.
	 *
	 * @param value Char value.
	 * @return
	 *     <p>Reference of this class.</p>
	 */
	SimpleString& append(_CHAR value);

public:
	
	/**
	 * Get length.
	 *
	 * @param string String.
	 * @return
	 *     <p>Length of string.</p>
	 */
	static _SHORT getLength(const _STRING string);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
