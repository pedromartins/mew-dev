//sends ultrasound readings. Connect ultarsound sensor's analogue outputs to pins 0 and 1

#define BAUDRATE 9600

void sendUltrasoundReadings()
{
  int readings[2] = {-1, -1};
  readings[0] = analogRead(0); // Append signal value to val
  readings[1] = analogRead(1);//make this use arrays
  
  readings[0] *= 1.24;
  readings[1] *= 1.24;
  
  Serial.println(readings[0], DEC);
  Serial.println(readings[1], DEC);
}


void setup() {
 pinMode(0, INPUT); // Switch signalpin ANALOG-0 to input
 pinMode(1, INPUT); // Switch signalpin ANALOG-1 to input
 Serial.begin(BAUDRATE);        
 Serial.flush();          
}

byte incomingByte = 0;

void loop() {
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    switch(incomingByte)
    {
      case 'u':
        sendUltrasoundReadings();
        break;
      case '?':
        Serial.print("u;");//identify as ultrasound arduino
        break;
      default:
        break;
    }
  }
} 
