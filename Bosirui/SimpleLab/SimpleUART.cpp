////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleUART.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default construction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleUART::SimpleUART(void)
{
	//Set position.
	position = 0;
	//Clear buffer.
	memset(buffer,0,32 * sizeof(_CHAR));
}

/**
 * Whether line is ready.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Return true, if line is ready !.</p>
 */
_BOOL SimpleUART::lineReady(void)
{
	//Check available.
	while(Serial && Serial.available() > 0)
	{
		//Read value.
		_CHAR value = Serial.read();
		//Check result.
		if(value == '\r') continue;
		//Check result.
		if(value != '\n')
		{
			//Set value.
			buffer[position ++] = value;
		}
		//Check result.
		if(value == '\n' ||
			position >= 31)
		{
			//Set buffer.
			buffer[position] = '\0';
			//Reset position.
			position = 0; return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}

/**
 * Get string.
 *
 * @param None No parameters needed.
 * @return
 *     <p>Pointer of string.</p>
 */
const _STRING SimpleUART::getString(void) const {return (_STRING)buffer;}
