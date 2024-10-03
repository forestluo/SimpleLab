#include <avr/pgmspace.h>
#include "SimplePrint.h"
#include "SimpleFormat.h"

#define _DEBUG

#include <SPI.h>
//Set pin 10 as the slave select for the digital pot.
const int mosiPin = 11;
const int misoPin = 12;
const int clockPin = 10;
const int selectPin = 9;

int readATT7022E(int command)
{
    //Enable SPI
    digitalWrite(selectPin,HIGH);
    digitalWrite(clockPin,LOW);
    digitalWrite(selectPin,LOW);
    //Send 8 bits command to SPI.
    for(int i = 0;i < 8;i ++)
    {
        digitalWrite(clockPin,HIGH);
        digitalWrite(mosiPin,
            (command & 0x80) ? HIGH : LOW);
        delayMicroseconds(1);
        digitalWrite(clockPin,LOW);
        delayMicroseconds(1);
        //Shift left.
        command <<= 1;
    }
    //Wait for 3us
    delayMicroseconds(3);
    //Value.
    int value = 0;
    //Read 24 bits data from SPI.
    for(int i = 0;i < 24;i ++);
    {
        //Shift left.
        value <<= 1;
        digitalWrite(clockPin,HIGH);
        //delayMicroseconds(2);
        if(digitalRead(misoPin)) value |= 0x01;
        digitalWrite(clockPin,LOW);
        delayMicroseconds(1);
    }
    //Disable SPI.
    digitalWrite(selectPin,HIGH);
    delayMicroseconds(2);
    //Return result.
    return value;
}

void writeATT7022E(int command,int value)
{
    //Take the SS pin low to select the chip.
    digitalWrite(selectPin,LOW);
    //Send in the command.
    SPI.transfer(command | 0x80);

    //Wait for the response.
    for(int i = 2;i >= 0;i --)
    {
        value >>= 8;
        //Write value.
        SPI.transfer((value >> i) & 0xFF);
    }
    
    //Take the SS pin high to de-select the chip.
    digitalWrite(selectPin,HIGH);
    //Return result.
    return value;
}

void initializeATT7022E(void)
{
    //Software reset.
    //writeATT7022E(0xD3,0x000000);
}

void dumpRegisters(void)
{
    //Value.
    int value;
#ifdef _DEBUG
    _PRINT0("ATT7022E::dumpRegisters : dump registers !");
#endif    

    //Read value.
    value = readATT7022E(0x00);
#ifdef _DEBUG
    _PRINT1("\tdeviceID = 0x%08x",value);
#endif

/*
    //Read value.
    value = readATT7022E(0x01);
#ifdef _DEBUG
    _PRINT1("\tPa = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x02);
#ifdef _DEBUG
    _PRINT1("\tPb = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x03);
#ifdef _DEBUG
    _PRINT1("\tPc = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x04);
#ifdef _DEBUG
    _PRINT1("\tPt = 0x%08x",value);
#endif

    //Read value.
    value = readATT7022E(0x05);
#ifdef _DEBUG
    _PRINT1("\tQa = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x06);
#ifdef _DEBUG
    _PRINT1("\tQb = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x07);
#ifdef _DEBUG
    _PRINT1("\tQc = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x08);
#ifdef _DEBUG
    _PRINT1("\tQt = 0x%08x",value);
#endif

    //Read value.
    value = readATT7022E(0x09);
#ifdef _DEBUG
    _PRINT1("\tSa = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x0a);
#ifdef _DEBUG
    _PRINT1("\tSb = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x0b);
#ifdef _DEBUG
    _PRINT1("\tSc = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x0c);
#ifdef _DEBUG
    _PRINT1("\tSt = 0x%08x",value);
#endif

    //Read value.
    value = readATT7022E(0x0d);
#ifdef _DEBUG
    _PRINT1("\tUaRms = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x0e);
#ifdef _DEBUG
    _PRINT1("\tUbRms = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x0f);
#ifdef _DEBUG
    _PRINT1("\tUcRms = 0x%08x",value);
#endif

    //Read value.
    value = readATT7022E(0x10);
#ifdef _DEBUG
    _PRINT1("\tIaRms = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x11);
#ifdef _DEBUG
    _PRINT1("\tIbRms = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x12);
#ifdef _DEBUG
    _PRINT1("\tIcRms = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x13);
#ifdef _DEBUG
    _PRINT1("\tItRms = 0x%08x",value);
#endif

    //Read value.
    value = readATT7022E(0x14);
#ifdef _DEBUG
    _PRINT1("\tPfa = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x15);
#ifdef _DEBUG
    _PRINT1("\tPfb = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x16);
#ifdef _DEBUG
    _PRINT1("\tPfc = 0x%08x",value);
#endif
    //Read value.
    value = readATT7022E(0x17);
#ifdef _DEBUG
    _PRINT1("\tPft = 0x%08x",value);
#endif
*/

    //Read value.
    value = readATT7022E(0x3E);
#ifdef _DEBUG
    _PRINT1("\tChkSum = 0x%08x",value);
#endif
}

void setup()
{
    //Open serial communication and wait for port to open.
    Serial.begin(115200);
    //Do while.
    while(!Serial) 
    {
        //Wait for serial port to connect.
        //Need for leonardo.
    }
#ifdef _DEBUG
    // Print.
    _PRINT0(">ATT7022E::setup : begin to work !");
#endif
  
    //Set the select pin as an output.
    pinMode(misoPin,INPUT);
    pinMode(mosiPin,OUTPUT);
    pinMode(clockPin,OUTPUT);
    pinMode(selectPin,OUTPUT);
    //Set output.
    digitalWrite(selectPin,HIGH);
    
    //Initialize ATT7022E
    initializeATT7022E();
#ifdef _DEBUG
    // Print.
    _PRINT0(">ATT7022E::setup : ATT7022E was initialized !");
#endif
}

void loop()
{
    //Delay one second.
    delay(2000);
    //Dump registers.
    dumpRegisters();
}
