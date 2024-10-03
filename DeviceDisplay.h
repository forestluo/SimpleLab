#ifndef _DEVICE_DISPLAY_H
#define _DEVICE_DISPLAY_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Display string.
 *
 * <p>Display string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _DISPLAY0(string)									\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[64];										\
	memset(buffer,0,64);									\
	strcpy_P(buffer,(char *)(_str));						\
															\
	displayModule.println(buffer);							\
	displayModule.displayBuffer();							\
}															\

/**
 * Display string.
 *
 * <p>Display string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _DISPLAY1(string,v1)								\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[64];										\
	char format[64];										\
	memset(buffer,0,64);									\
	memset(format,0,64);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1);								\
															\
	displayModule.println(buffer);							\
	displayModule.displayBuffer();							\
}															\

/**
 * Display string.
 *
 * <p>Display string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _DISPLAY2(string,v1,v2)								\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[64];										\
	char format[64];										\
	memset(buffer,0,64);									\
	memset(format,0,64);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2);							\
															\
	displayModule.println(buffer);							\
	displayModule.displayBuffer();							\
}															\

/**
 * Display string.
 *
 * <p>Display string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _DISPLAY4(string,v1,v2,v3,v4)						\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[64];										\
	char format[64];										\
	memset(buffer,0,64);									\
	memset(format,0,64);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4);						\
															\
	displayModule.println(buffer);							\
	displayModule.displayBuffer();							\
}															\

/**
 * Display string.
 *
 * <p>Display string in PROGMEM.</p>
 *
 * @param string String in PROGMEM.
 * @return
 *     <p>No results returned.</p>
 */
#define _DISPLAY6(string,v1,v2,v3,v4,v5,v6)					\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[64];										\
	char format[64];										\
	memset(buffer,0,64);									\
	memset(format,0,64);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4,v5,v6);				\
															\
	displayModule.println(buffer);							\
	displayModule.displayBuffer();							\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !