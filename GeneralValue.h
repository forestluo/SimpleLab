#ifndef _GENERAL_VALUE_H
#define _GENERAL_VALUE_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

/**
 *Max sample count.
 *
 * <p>Max count of sample in a packet.</p>
 */
#define MAX_SAMPLE_COUNT									16

/**
 * General value type.
 */
#define GENERAL_NULL_TYPE									0x00
#define GENERAL_BOOLEAN_TYPE								0x01
#define GENERAL_BYTE_TYPE									0x02
#define GENERAL_CHAR_TYPE									0x03
#define GENERAL_SHORT_TYPE									0x04
#define GENERAL_INTEGER_TYPE								0x05
#define GENERAL_FLOAT_TYPE									0x06
#define GENERAL_LONG_TYPE									0x07
#define GENERAL_DOUBLE_TYPE									0x08
#define GENERAL_LENGTH_TYPE									0x09

/**
 * General value.
 */
typedef struct tagGeneralValue
{
	/**
	 * Type of value.
	 */
	_UINT8 valueType;
	/**
	 * General value.
	 *
	 * <p>It is no more than 8 bytes.
	 * And transmiited in network byte order.</p>
	 */
	union
	{
		//Length.
		_INTEGER length;

		//Boolean value.
		_BOOL boolValue;
		//Byte value.
		_BYTE byteValue;
		//Char value.
		_CHAR charValue;
		//Short value.
		_SHORT shortValue;
		//Integer value.
		_INTEGER integerValue;
		//Float value.
		_FLOAT floatValue;

	} dataValue;

} GeneralValue;

/**
 * Sample value.
 */
typedef struct tagSampleValue
{
	/**
	 * Timestamp.
	 *
	 * <p>The sample timestamp.<p>
	 */
	_UINT32 timestamp;
	/**
	 * Sequence id.
	 *
	 * <p>It is used in cycle(1 ~ 65535).</p>
	 */
	_UINT16 sequenceID; 
	/**
	 * Pin value.
	 *
	 * <p>It is kept for 32bit.</p>
	 */
	_UINT32 pinValue;
	/**
	 * General value.
	 *
	 * <p>It is kept for any kind of value.</p>
	 */
	GeneralValue generalValue;

} SampleValue;

/**
 * Device value.
 *
 * <p>A device can collect sample in a group and send it in one packet.
 * The max count of sample is not more than 16.
 * Thus the whole packet is not more than 256 bytes.</p>
 */
typedef struct tagDeviceValue
{
	/**
	 * Count of sample.
	 */
	_BYTE sampleCount;
	/**
	 * Sample of pin.
	 */
	SampleValue sampleValues[MAX_SAMPLE_COUNT];

} DeviceValue;

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
