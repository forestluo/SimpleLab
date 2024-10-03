#ifndef _SIMPLE_ASSERT_H
#define _SIMPLE_ASSERT_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Assert.
 *
 * <p>Use buzz to alert.</p>
 *
 * @param c Condition.
 * @return
 *     <p>No results returned.</p>
 */
#define _ASSERT(c)											\
{															\
	if(!(c))												\
	{														\
		static const prog_char _str[] PROGMEM =				\
			"Assert failed in %s() at line%d in file(%s) !";\
		char buffer[128];									\
		char format[128];									\
		memset(buffer,0,128);								\
		memset(format,0,128);								\
		strcpy_P(format,(char *)(_str));					\
		sprintf(buffer,format,								\
			__FUNCTION__,__LINE__,__FILE__);				\
		while(1)											\
		{													\
			if(Serial) Serial.println(buffer);				\
			digitalWrite(5,LOW);delay(1000);				\
			digitalWrite(5,HIGH);delay(1000);				\
		}													\
	}														\
}															\

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
