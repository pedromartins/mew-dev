#define BAUDRATE 38400
//compass part
#include <Wire.h>

int HMC6352Address = 0x42;
// This is calculated in the setup() function
int slaveAddress;
byte headingData[2];
int i, headingValue;
int smoothHeading;

void sendCompassReading()
{
  // Send a "A" command to the HMC6352

  // This requests the current heading data
  Wire.beginTransmission(slaveAddress);
  Wire.send("A");              // The "Get Data" command
  Wire.endTransmission();
  delay(10);                   // The HMC6352 needs at least a 70us (microsecond) delay

  // after this command.  Using 10ms just makes it safe
  // Read the 2 heading bytes, MSB first
  // The resulting 16bit word is the compass heading in 10th's of a degree
  // For example: a heading of 1345 would be 134.5 degrees

  Wire.requestFrom(slaveAddress, 2);        // Request the 2 byte heading (MSB comes first)

  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.receive();
    i++;
  }

  headingValue = headingData[0]*256 + headingData[1];  // Put the MSB and LSB together
  
  Serial.print(headingValue);
  Serial.print(";");
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
  
  if (tmp < 3)
    return -1; // invalid value

  ret = (byte)( (6787.0 /((float)tmp - 3.0)) - 4.0 );

  if(ret > 70)
    return -2;
  else if(ret < 4)
    return -3;
  else
    return ret;
} 

void sendIrReadings()
{
  byte distance[4] = {-1, -1, -1, -1};
  distance[0] = read_gp2d12_range(IR_pins[0]);
  distance[1] = read_gp2d12_range(IR_pins[1]);
  distance[2] = read_gp2d12_range(IR_pins[2]);
  distance[3] = read_gp2d12_range(IR_pins[3]);
  
  for(int i = 0; i < 4; i++)
  {
    Serial.print(distance[i], DEC);
    Serial.print(" ");
  }
  Serial.print(";");
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

  //init compass stuff
  slaveAddress = HMC6352Address >> 1;   // This results in 0x21 as the address to pass to TWI
  Wire.begin();
  
   pinMode(13, OUTPUT);      // sets the digital pin as output

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
      case ';':
        //stop command.. not really necessary
        break;
      case '?':
        Serial.print("s;");//identiy as sensor arduino
        break;
      default:
        break;
    }
  }
  
  //sendUltraSoundReadings();
 }
