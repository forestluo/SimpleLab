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
	const char _str[] PROGMEM = (string);					\
	if(Serial) Serial.println(_str);						\
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
	const char _str[] PROGMEM = (string);					\
	char buffer[128];										\
	memset(buffer,0,128);									\
	sprintf(buffer,_str,v1);								\
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
	const char _str[] PROGMEM = (string);					\
	char buffer[128];										\
	memset(buffer,0,128);									\
	sprintf(buffer,_str,v1,v2);								\
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
	const char _str[] PROGMEM = (string);					\
	char buffer[128];										\
	memset(buffer,0,128);									\
	sprintf(buffer,_str,v1,v2,v3);							\
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
	const char _str[] PROGMEM = (string);					\
	char buffer[128];										\
	memset(buffer,0,128);									\
	sprintf(buffer,_str,v1,v2,v3,v4);						\
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
	const char _str[] PROGMEM = (string);					\
	char buffer[128];										\
	memset(buffer,0,128);									\
	sprintf(buffer,_str,v1,v2,v3,v4,v5,v6);					\
	if(Serial) Serial.println(buffer);						\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
