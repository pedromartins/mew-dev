 int IR_pin = 0;//IR Analog pin 0
 unsigned long distance = 0;

 void setup()
 {
 Serial.begin(9600);
 pinMode(IR_pin,INPUT);
}

 void loop()
 {
  distance = analogRead(IR_pin);
  Serial.println(distance, DEC);
  delay(250); //delay 1/4 seconds.
 }
