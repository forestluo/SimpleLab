#ifndef _SIMPLE_CONSOLE_H
#define _SIMPLE_CONSOLE_H

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
#define _CONSOLE0(string)									\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	memset(buffer,0,32);									\
	strcpy_P(buffer,(char *)(_str));						\
	ConsoleFile::writeConsole(fileModule,buffer);			\
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
#define _CONSOLE1(string,v1)								\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	char format[32];										\
	memset(buffer,0,32);									\
	memset(format,0,32);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1);								\
	ConsoleFile::writeConsole(fileModule,buffer);			\
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
#define _CONSOLE2(string,v1,v2)								\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	char format[32];										\
	memset(buffer,0,32);									\
	memset(format,0,32);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2);							\
	ConsoleFile::writeConsole(fileModule,buffer);			\
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
#define _CONSOLE3(string,v1,v2,v3)							\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	char format[32];										\
	memset(buffer,0,32);									\
	memset(format,0,32);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3);						\
	ConsoleFile::writeConsole(fileModule,buffer);			\
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
#define _CONSOLE4(string,v1,v2,v3,v4)						\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	char format[32];										\
	memset(buffer,0,32);									\
	memset(format,0,32);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4);						\
	ConsoleFile::writeConsole(fileModule,buffer);			\
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
#define _CONSOLE6(string,v1,v2,v3,v4,v5,v6)					\
{															\
	static const prog_char _str[] PROGMEM = (string);		\
	char buffer[32];										\
	char format[32];										\
	memset(buffer,0,32);									\
	memset(format,0,32);									\
	strcpy_P(format,(char *)(_str));						\
	sprintf(buffer,format,v1,v2,v3,v4,v5,v6);				\
	ConsoleFile::writeConsole(fileModule,buffer);			\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
