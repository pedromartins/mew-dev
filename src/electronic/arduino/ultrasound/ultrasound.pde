void setup() {
 Serial.begin(9600);                  
}

void loop() {
  int reading;
pinMode(0, INPUT); // Switch signalpin ANALOG-0 to input
reading = analogRead(0); // Append signal value to val

reading *= 1.24;

Serial.println(reading);

delay(100);
} 
