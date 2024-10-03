#ifndef _SIMPLE_PRINT_H
#define _SIMPLE_PRINT_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT0(string)										\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	memset(buffer,0,128);									\
	strcpy_P(buffer,(char *)(_str));						\
	if(Serial) Serial.println(buffer);						\
}															\

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT1(string,v1)									\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	char format[128];										\
	memset(buffer,0,128);									\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1);								\
	if(Serial) Serial.println(buffer);						\
}															\

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT2(string,v1,v2)								\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	char format[128];										\
	memset(buffer,0,128);									\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2);							\
	if(Serial) Serial.println(buffer);						\
}															\

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT3(string,v1,v2,v3)							\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	char format[128];										\
	memset(buffer,0,128);									\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3);						\
	if(Serial) Serial.println(buffer);						\
}															\

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT4(string,v1,v2,v3,v4)							\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	char format[128];										\
	memset(buffer,0,128);									\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4);						\
	if(Serial) Serial.println(buffer);						\
}															\

/**
 * Print string.
 *
 * <p>Print string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _PRINT6(string,v1,v2,v3,v4,v5,v6)					\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[128];										\
	char format[128];										\
	memset(buffer,0,128);									\
	memset(format,0,128);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4,v5,v6);				\
	if(Serial) Serial.println(buffer);						\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
