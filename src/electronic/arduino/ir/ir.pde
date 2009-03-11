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


void setup()
  {
  Serial.begin(9600);
  
  //initialise IR pins to INPUT
  for(int i = 0; i < 4; i++)
  {
    pinMode(IR_pins[i],INPUT);
  }
}

void loop()
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
  Serial.println();
  delay(250); //delay 1/4 seconds.
}
