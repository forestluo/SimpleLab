#ifndef _SIMPLE_FORMAT_H
#define _SIMPLE_FORMAT_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT0(buffer,string)								\
{															\
	const char _str[] PROGMEM = (string);					\
	strcpy(buffer,_str);									\
}															\

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT1(buffer,string,v1)							\
{															\
	const char _str[] PROGMEM = (string);					\
	sprintf(buffer,_str,v1);								\
}															\

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT2(buffer,string,v1,v2)						\
{															\
	const char _str[] PROGMEM = (string);					\
	sprintf(buffer,_str,v1,v2);								\
}															\

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT3(buffer,string,v1,v2,v3)					\
{															\
	const char _str[] PROGMEM = (string);					\
	sprintf(buffer,_str,v1,v2,v3);							\
}															\

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT4(buffer,string,v1,v2,v3,v4)					\
{															\
	const char _str[] PROGMEM = (string);					\
	sprintf(buffer,_str,v1,v2,v3,v4);						\
}															\

/**
 * Format string.
 *
 * @param buffer Result buffer.
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _FORMAT6(buffer,string,v1,v2,v3,v4,v5,v6)			\
{															\
	const char _str[] PROGMEM = (string);					\
	sprintf(buffer,_str,v1,v2,v3,v4,v5,v6);					\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
