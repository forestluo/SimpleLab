#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <avr/pgmspace.h>
#include "SimplePrint.h"
#include "SimpleFormat.h"
#include <SoftwareSerial.h>

//Debug
#define _DEBUG

//Position
int position = 0;
//CM05 status.
bool alreadyReset;
unsigned long lastActive;
//Buffer
unsigned char buffer[128];
//Timestamp.
unsigned long timestamps[2];

//Power Pin
int powerPin = 3;
int resetPin = 2;
//Switch Pin
int switchPins[3] = {7,6,5};
//Voltage Pin
int voltagePins[3] = {A1,A2,A3};
//LED Pin
int redPin = 10;
int yellowPin = 12;
int greenPin = 11;
//Software Serial
//RX -> Pin8, TX -> Pin9
SoftwareSerial hc05Module(9,8);

void CM05_PowerOn()
{
    digitalWrite(powerPin,1);//Power on CM05
    delay(3000);
    digitalWrite(powerPin,0);
}

void CM05_Reset()
{
    digitalWrite(resetPin,1);//Reset on CM05
    delay(3000);
    digitalWrite(resetPin,0);
}

void doVoltageSamples()
{
    //Voltage values.
    int voltageValues[100];
    
    //Read voltage.
    for(int i = 0;i < 100;i ++)
    {
        delayMicroseconds(300);
        voltageValues[i] = analogRead(voltagePins[0]);
    }
    hc05Module.print("Va|");
    //Do output.
    for(int i = 0;i < 100;i ++)
    {
        hc05Module.
          print(voltageValues[i]);
        if(i < 99) hc05Module.print(',');
    }
    hc05Module.println();

    delay(5);

    //Read voltage.
    for(int i = 0;i < 100;i ++)
    {
        delayMicroseconds(300);
        voltageValues[i] = analogRead(voltagePins[1]);
    }
    hc05Module.print("Vb|");
    //Do output.
    for(int i = 0;i < 100;i ++)
    {
        hc05Module.
          print(voltageValues[i]);
        if(i < 99) hc05Module.print(',');
    }
    hc05Module.println();

    delay(5);

    //Read voltage.
    for(int i = 0;i < 100;i ++)
    {
        delayMicroseconds(300);
        voltageValues[i] = analogRead(voltagePins[2]);
    }
    hc05Module.print("Vc|");
    //Do output.
    for(int i = 0;i < 100;i ++)
    {
        hc05Module.
          print(voltageValues[i]);
        if(i < 99) hc05Module.print(',');
    }
    hc05Module.println();

    delay(5);
}

bool waitCommand()
{  
    //Listen.
    hc05Module.listen();
    //Wait for a while.
    if(hc05Module.available() <= 0) return false;
    //Read.
    while(1)
    {
        //Check position.
        if(position > 128)
            position = 0;
        //Read.
        buffer[position] =
            hc05Module.read();
        //Check result.
        if(buffer[position ++] == '\n') break;
        //Wait for a while.
        if(hc05Module.available() <= 0) return false;
    }

#ifdef _DEBUG
    //Print.
    _PRINT0(">ACSample3::waitCommand : command recevied !");
    //Set end char.
    buffer[position] = '\0';
    //Print.
    Serial.print(">\t");Serial.println((char *)buffer);
#endif

    //Clear position.
    position = 0;
    //Reset last active.
    lastActive = millis();
    //Compare.
    if(strncmp(buffer,"Red",3) == 0)
    {
        digitalWrite(redPin,1);
        digitalWrite(greenPin,0);
        digitalWrite(yellowPin,0);      
#ifdef _DEBUG        
        //Power on again.
        _PRINT1(">ACSample3::waitCommand : set RED pin at %u(ms)",lastActive);
#endif        
    }
    else if(strncmp(buffer,"Green",5) == 0)
    {
        digitalWrite(redPin,0);
        digitalWrite(greenPin,1);
        digitalWrite(yellowPin,0);      
#ifdef _DEBUG        
        //Power on again.
        _PRINT1(">ACSample3::waitCommand : set GREEN pin at %u(ms)",lastActive);
#endif        
    }
    else if(strncmp(buffer,"Yellow",6) == 0)
    {
        digitalWrite(redPin,0);
        digitalWrite(greenPin,0);
        digitalWrite(yellowPin,1);      
#ifdef _DEBUG        
        //Power on again.
        _PRINT1(">ACSample3::waitCommand : set YELLOW pin at %u(ms)",lastActive);
#endif        
    }
    else if(strncmp(buffer,"Reset",5) == 0)
    {
        //Reset CM05.
        CM05_Reset();
        //Reset last active.
        lastActive = millis();
#ifdef _DEBUG        
        //Reset again.
        _PRINT1(">ACSample3::waitCommand : reset at %u(ms)",lastActive);
#endif        
    }
    else
    {
#ifdef _DEBUG
        //Reset again.
        _PRINT1(">ACSample3::waitCommand : invalid command at %u(ms)",lastActive);
#endif
    }
    return true;
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
    _PRINT0(">ACSample3::setup : begin to work !");
#endif

    //Declare the reset pin as an OUTPUT.
    pinMode(resetPin,OUTPUT);
    digitalWrite(resetPin,0);
    //Declare the power pin as an OUTPUT.
    pinMode(powerPin,OUTPUT);
    digitalWrite(powerPin,1);//Power on CM05
    
    //Declare the led pin as an OUTPUT.
    pinMode(redPin,OUTPUT);
    pinMode(yellowPin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    digitalWrite(redPin,1);
    digitalWrite(greenPin,1);
    digitalWrite(yellowPin,1);
    //Wait for 1 second.
    delay(1000);
    digitalWrite(greenPin,0);
    //Wait for 1 second.
    delay(1000);
    digitalWrite(yellowPin,0);
    //Wait for 1 second.
    delay(1000);
    digitalWrite(powerPin,0);//Power on CM05

    //Declare the switch pin as an INPUT.
    for(int i = 0;i < 3;i ++)
        pinMode(switchPins[i],INPUT);
#ifdef _DEBUG
    //Print.
    _PRINT0(">ACSample3::setup : switch pin connected !");
#endif
    
    //Declare the voltage pin as an INPUT.
    for(int i = 0;i < 3;i ++)
        pinMode(voltagePins[i],INPUT);
#ifdef _DEBUG
    //Print.
    _PRINT0(">ACSample3::setup : voltage pin connected !");
#endif

    //Setup baudrate for serial port.
    hc05Module.begin(57600);
#ifdef _DEBUG
    //Print.
    _PRINT0(">ACSample3::setup : bluetooth module connected !");
#endif

    //Clear status.
    alreadyReset = false;
    lastActive = millis();
    
    //Set timestamp.
    timestamps[0] = timestamps[1] = millis();
#ifdef _DEBUG　
    //Print.
    _PRINT0(">ACSample3::setup : device was setup !");
#endif
}

void loop()
{    
    //Get current time.
    unsigned long currentTime = millis();
    //Check last active.
    if(currentTime < lastActive)
    {
        lastActive = millis();
    }
    else
    {
        //Check flag.
        if(alreadyReset &&
            currentTime - lastActive > 300000)
        {
            //Clear flag.
            alreadyReset = false;
#ifdef _DEBUG        
            //Failed on active test.
            _PRINT1(">ACSample3::loop : reset failed at %u(ms)",currentTime);
#endif
            //Power on CM05.
            CM05_PowerOn();
            //Reset last active.
            lastActive = millis();
#ifdef _DEBUG        
            //Power on again.
            _PRINT1(">ACSample3::loop : power on again at %u(ms)",lastActive);
#endif        
        }
        else if(!alreadyReset &&
            currentTime - lastActive > 600000)
        {
            //Clear flag.
            alreadyReset = true;
#ifdef _DEBUG        
            //Failed on active test.
            _PRINT1(">ACSample3::loop : active failed at %u(ms)",currentTime);
#endif        
            //Reset CM05.
            CM05_Reset();
            //Reset last active.
            lastActive = millis();
#ifdef _DEBUG        
            //Reset again.
            _PRINT1(">ACSample3::loop : reset at %u(ms)",lastActive);
   
#endif
        }
    }

    //Wait for command.
    while(waitCommand());

   //Check current time.
    if(currentTime - timestamps[1] > 1000)
    {
        //Set timestamp.
        timestamps[1] = millis();

        int switchValues[3];
        //Try to read value from switch pin.
        for(int i = 0;i < 3;i ++)
        {
            switchValues[i] = digitalRead(switchPins[i]);
        }    
/*
#ifdef _DEBUG
        //Print result.
        _PRINT0(">ACSample3::loop : show status !");
        _PRINT1(">\ttimestamp = %u",currentTime);
        _PRINT3(">\tswitch values = %d,%d,%d",
            switchValues[0],switchValues[1],switchValues[2]);
#endif
*/
        hc05Module.print("Sa|");hc05Module.println(switchValues[2]);
        hc05Module.print("Sb|");hc05Module.println(switchValues[1]);
        hc05Module.print("Sc|");hc05Module.println(switchValues[0]);
    }

    //Check result.
    if(currentTime - timestamps[0] > 1000)
    {
        //Set timestamp.
        timestamps[0] = millis();
        //Do voltage values.
        doVoltageSamples(); delay(20);
    }
}
