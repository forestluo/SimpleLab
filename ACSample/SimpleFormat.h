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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	strcpy(buffer,format);									\
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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1);								\
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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2);							\
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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3);						\
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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4);						\
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
	static const char _str[] PROGMEM = (string);		\
	char format[128];										\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4,v5,v6);				\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
