////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <ChipDHT.h>

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Read byte.
 *
 * @param pin Data pin.
 * @return
 *     <p>Byte value.</p>
 */
_BYTE ChipDHT::readByte(DigitalPin pin)
{
	//Result.
	_BYTE result = 0;
	//Collect 8 bits from datastream, return them interpreted
	//as a byte. I.e. if 0000.0101 is sent, return decimal 5.
	//Code expects the system to have recently entered the
	//dataline low condition at the start of every data bit's
	//transmission BEFORE this function is called.
	for(int i = 0;i < 8;i ++)
	{
		//We enter this during the first start bit (low for 50uS) of the byte
		//Next: wait until pin goes high
		while(digitalRead(pin)==LOW);
        //signalling end of start of bit's transmission.
		//Dataline will now stay high for 27 or 70 uS, depending on
		//whether a 0 or a 1 is being sent, respectively.
		delayMicroseconds(30);
		//AFTER pin is high, wait further period, to be
        //into the part of the timing diagram where a 0 or a 1 denotes
        //the datum being send. The "further period" was 30uS in the software
        //that this has been created from. I believe that a higher number
        //(45?) might be more appropriate.
		//Next: Wait while pin still high.
		if(digitalRead(pin) == HIGH)
		{
			// "add" (not just addition) the 1 to the growing byte.
			result |= (1 << (7-i));
		}
		//Next wait until pin goes low again, which signals the START
	    //of the NEXT bit's transmission.
		while(digitalRead(pin) == HIGH);
    }//end of "for.."
	//Return rsult.
	return result;
}

/**
 * Initialize.
 *
 * @param pin Data pin.
 * @return
 *     <p>No results returned.</p>
 */
void ChipDHT::initialize(DigitalPin pin)
{
	//Set pin mode.
	pinMode(pin,OUTPUT);
	//Set high.
	digitalWrite(pin,HIGH);
}

/**
 * Read.
 *
 * @param pin Data pin.
 * @param temperature Temperature.
 * @param humidity Humidity.
 * @return
 *     <p>Return true, if successfully done.</p>
 */
_BOOL ChipDHT::read(DigitalPin pin,_FLOAT& temperature,_FLOAT& humidity)
{
	/*
		Uses global variables dht_dat[0-4], and bGlobalErr to pass
		"answer" back. bGlobalErr=0 if read went okay.
		Depends on global dht_dpin for where to look for sensor.
	*/
	//Send "start read and report" command to sensor....
	//First: pull-down I/O pin for 23000us.
	digitalWrite(pin,LOW);
	delay(23);
	/*
		aosong.com datasheet for DHT22 says pin should be low at least
		500us. I infer it can be low longer without any]
		penalty apart from making "read sensor" process take
		longer.
	*/
	//Next line: Brings line high again,
	//second step in giving "start read..." command.
	digitalWrite(pin,HIGH);
	delayMicroseconds(30);
	//DHT22 datasheet says host should
	//keep line high 20-40us, then watch for sensor taking line
	//low. That low should last 80us. Acknowledges "start read
	//and report" command.
	//Getting the delay exacly right is critical...
	//put 40 in for the delay, in one of the later
	//editions of this code, and the program
	//will work SOMETIMES, but not ALWAYS.
	//You have to allow for processing overheads,
	//etc, too. Using, say, 30 won't "magically"
	//make the TOTAL delay (with overheads, etc)
	//exactly 30.0000 milliseconds. (This version may
	//also have been unreliable with delay=40.. now
	//deprecated.)
	//Next: Change Arduino pin to an input, to
	//watch for the 80us low explained a moment ago.
	pinMode(pin,INPUT);
	delayMicroseconds(40);
	//Read value.
	_BYTE value = digitalRead(pin);
	//Check result.
	if(value)
	{
#ifdef _DEBUG
		//Print.
		_PRINT0("ChipDHT::read : DHT start condition 1 not met.");
#endif
		return _FALSE;
	}//end "if..."
	delayMicroseconds(80);
	//Read value.
	value = digitalRead(pin);
	if(!value)
	{
#ifdef _DEBUG
		//Print.
		_PRINT0("ChipDHT::read : DHT start condition 2 not met.");
#endif
		return _FALSE;
	}//end "if..."
	/*
		After 80us low, the line should be taken high for 80us by the
		sensor. The low following that high is the start of the first
		bit of the forty to come. The routine "read_dht_dat()"
		expects to be called with the system already into this low.
	*/
	delayMicroseconds(80);

	//Values.
	_BYTE values[5];
	//now ready for data reception... pick up the 5 bytes coming from the sensor.
	for(int i = 0;i < 5;i ++)
	{
		//Read value.
		values[i] = readByte(pin);
	}
	//Next: restore pin to output duties
	pinMode(pin,OUTPUT);
	//Next: Make data line high again, as output from Arduino
	digitalWrite(pin,HIGH);
	//Next see if data received consistent with checksum received
	_BYTE checksum = values[0] + values[1] + values[2] + values[3];
	/*
		Condition in following "if" says "if fifth byte from sensor
		not the same as the sum of the first four..."
	*/
	if(values[4] != checksum)
	{
#ifdef _DEBUG
		//Print.
		_PRINT0("ChipDHT::read : DHT checksum error.");
#endif
		return _FALSE;
	}
	//Set humidity.
	humidity = values[0] + values[1] / 256.0f;
	//Set temperature.
	temperature = values[2] + values[3] / 256.0f;
	//Return true.
	return _TRUE;
}
