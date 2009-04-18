#define BAUDRATE 57600
//compass part
#include <Wire.h>

int HMC6352Address = 0x42;
// This is calculated in the setup() function
int slaveAddress;
byte headingData[2];
byte OMCbyte;
int i,j, headingValue;
int smoothHeading;
byte distance[4]= {0, 0, 0, 0};

void sendCompassReading()
{
  
  /*Wire.beginTransmission(slaveAddress);
  Wire.send('A');              // The "Get Data" command
  Wire.endTransmission();
  delay(10);*/

  Wire.requestFrom(slaveAddress, 2);        // Request the 2 byte heading (MSB comes first)

  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.receive();
    i++;
  }

  headingValue = headingData[0]*256 + headingData[1];  // Put the MSB and LSB together
  
  Serial.println(headingValue, DEC);
}

//end compass
/*
  outputs the IR range in cm.
  code adapted from http://www.arduino.cc/playground/Main/ReadGp2d12Range
  
  This GP2D12 sensor should be used with a refresh rate of 36ms or greater.
  
  The function returns the IR range in cm, -1 on analog read error, -2 on out of range and -3 if the object is too close.
*/
int IR_pins[4] = {0,1,2,3};//IR Analog pin 0
 
byte read_gp2d12_range(byte pin)
{
  int tmp;   //temporary, for conversion
  byte ret;  //return value
  tmp = analogRead(pin);
  
  /*if (tmp < 3)
    return -1; // invalid value*/

  ret = (byte)( (6787.0 /((float)tmp - 3.0)) - 4.0 );

  /*if(ret > 70)
    return -2;
  else if(ret < 4)
    return -3;
  else
    return ret;*/
	
  return ret;
} 

void sendIrReadings()
{  
  for(int i = 0; i < 4; i++)
  {
    Serial.println(distance[i], DEC);
  }
}

//end IR bit. simply call  sendIRreadings(); as required.

void setup()
{
  
  
  Serial.begin(BAUDRATE);
  
  //initialise IR pins to INPUT
  for(int i = 0; i < 4; i++)
  {
    pinMode(IR_pins[i],INPUT);
  }
  Serial.flush();

  //Compass Initialisation -   Check Operational mode control byte
  //                           Make sure measurement rate is 20Hz and operational mode is continuous
  //---------------------------------------------------------------------------------
  slaveAddress = HMC6352Address >> 1;   // This results in 0x21 as the address to pass to TWI
  Wire.begin();

  
  // Send a "r" command to the HMC6352

  // This reads from the EEPROM
  /*Wire.beginTransmission(slaveAddress);
  Wire.send('r');              // The "Get Data from EEPROM command
  Wire.send(0x08);    //Operational mode control byte address
  Wire.endTransmission();
  delay(10);                   // The HMC6352 needs at least a 70us (microsecond) delay

  // after this command.  Using 10ms just makes it safe

  Wire.requestFrom(slaveAddress, 1);        // Request the operational mode control byte
  OMCbyte = Wire.receive();
  
  Serial.println(OMCbyte, HEX);
  Serial.println(OMCbyte, BIN);
  
  if(OMCbyte != 0x72) { //If not correct, write the correct one
    Wire.beginTransmission(slaveAddress);
    Wire.send('w');              // The "Write Data to EEPROM" command
    Wire.send(8);    //Operational mode control byte address
    Wire.send(0x72); //Desired OMCbyte
    Wire.endTransmission();
    delay(10);        
  }*/
  /*Wire.beginTransmission(slaveAddress);
  Wire.send('A');              // The "Get Data" commandc
  Wire.endTransmission();
  delay(10);*/
  
  
//-------------------------------------------------------------------------------------------

}

byte incomingByte = 0;

void loop()
{ 
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    switch(incomingByte)
    {
      case 'i':
        sendIrReadings();
        delay(36);    //mi delay
        break;
      case 'c':
        sendCompassReading();
        break;
      case '?':
        Serial.print("s");//identify as sensor arduino
        break;
      default:
        break;
    }
  }
  j++;
  j = j%4;
  distance[j] = read_gp2d12_range(IR_pins[j]); //Update an IR reading
 }

