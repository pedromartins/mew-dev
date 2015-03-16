[Arduino website](http://www.arduino.cc)

Datasheets
  * Sharp IR (GP2D12 F 88): http://www.robotshop.ca/PDF/rbsha03_manual.pdf
  * Compass (HMC6352) http://www.ssec.honeywell.com/magnetic/datasheets/HMC6352.pdf
  * MaxBotix EZ2 ultrasound: http://www.maxbotix.com/MaxSonar-EZ1__FAQ.html
  * Motorcontroller MD22: http://www.robot-electronics.co.uk/htm/md22tech.htm
  * I2C to USB chip: http://www.technobots.co.uk/Data%20Sheets/3810-005.pdf
    * wiring ([source](http://www.arduino.cc/playground/Learning/I2C)):
    * Arduino analog input 4 = I2C SDA ->pin closer to +5V on USB->I2C adapter
    * Arduino analog input 5 = I2C SCL ->middle pin on USB->I2C adapter

The I2C adapter image:

![http://mew-dev.googlecode.com/svn/wiki/images/i2c.jpg](http://mew-dev.googlecode.com/svn/wiki/images/i2c.jpg)


---

Hardware setup

---


Sensors:
  * Compass: connect VCC to +3V, GND as appropriate, SDA to ANALOG-IN 4, SCL to ANALOG-IN 5 on the Arduino.
  * IR's: red wire goes to +5V, black to GND and white to ANALOG-IN 0-3 (positions currently undefined)

Ultrasound (see backside of the sensors for pin names):
  * Connect GND and +5 appropriately.
  * Connect AN to ANALOG-IN 0 and 1 on the ultrasound-Arduino (positions currently undefined)

Servos:
  * Attach shield to Arduino
  * Lintel Servo: bottom left (0)

Motors:
  * Connect the I2C adapter to the motor controller (black wire: GND, red: +5V, blue with flag: SCL, blue without flag: SDA)


---

older stuff

---


~~A cheap way to interface I2C: http://www.paintyourdragon.com/uc/i2c/index.html -- Pedro~~

Been there already pedro! it only works with certain graphics chipsets that do ddc, and the intel integrated one in the eeepc doesn't.. nor does whatever ancient nvidea chip I had on an ancient PC in my room! I soldered up a converter a month or so ago to try!

the i2c bridge isn't the hard part, but if people want one for testing then i have a few spare vga plugs for soldering!


---


A few initial ideas to get the ball rolling -- Harry

**Main working areas:**
||
|:|


---


# i have decreed that it is arduino, no one contributed early enough! #

~~= MCU platform =~~


~~For choice of microcontroller platform we have PIC, Arduino (atmega), ARM or parallax stamp (probably others).~~
~~Things to consider when deciding which to use -~~
  * ~~Do the chips suit the application in terms of pin count, hardware peripherals (i2c, PWM, counters, timers, A/D...), processing power, package?~~
  * ~~What are the available resources? - Online communities, programming equipment(we might be able to use university programmers), libraries, documentation, etc~~
  * ~~What experience does the group have with this platform?~~
  * ~~What costs are associated with it in terms of money, time, space on the bot, etc.~~

~~Also we need to think about our approach towards the low level processing that is required. Are going to go for a modular approach? - separate MCUs for the servo controller, stepper/DC motors and sensors might make sense since we can easily fit plenty of slaves on the i2c bus.~~

# Sensors #

The bot is going to need to measure distance so rangefinders will be useful. The most common output method for these sensors is an analogue voltage, but some use PWM or even i2c. If we use analogue voltages, we will have to consider low-pass filters to clean the signal if they aren't already implemented in the sensors.
An electronic compass could be useful for orientation purposes (maybe even gyros and accelerometers...)
Our wiki page on sensors is [here](http://code.google.com/p/mew-dev/wiki/Sensors).

# Actuators #

Until the mechanical team have come to a decision, we should think about which actuators we would like them to use. For driving the wheels of the bot, DC motors, stepper motors, modified servos and AC motors are possibilities. What electronic requirements would each of these need?
For the grippers and other effectors on the bot, we will be using servos and possibly a linear actuator.

## drive motors ##
The motor controllers are these:
http://www.technobots.co.uk/Data%20Sheets/1502-001.pdf

They will be powerful enough to power the motors provided we don't stall them - we need software protection to power them off if the optical encoders detect stalling.


I suggest 1 arduino to read the encoders and output to the motors - then you get a good feedback loop.  Here's some quick sudocode:
```
define ACCEL_CONST 20       // aprox 200ms to get to speed or to stop.
while (1) {
  ds=read_desired_speed();  // from PC, probably into an I2C memory location
  as=actual_speed;          // set by encoder in a timed interrupt routine
  deltaSum+=ds-as;          // speed delta.  Additive so that average speed=desired speed.
  if ((delatSum>STALL_THRESHOLD) || (delatSum< -STALL_THRESHOLD)) {
    // motor is stalled
    output_i2c(MOTOR_BASE_ADDRESS,0);
    sleep(5000);            // wait 5 secs, then retry.
    deltaSum=0;
  }
  // set motor speed
  output_i2c(MOTOR_BASE_ADDRESS,deltaSum / ACCEL_CONST);
  // sleep to allow motor speed to change, prevents too much
  // negative feedback causing oscillations.
  sleep(10);
}

void ISR() {  //called on a fast timer, although could be integrated into above loop
  int a = read_encoder_state();  // returns 0, 1, 2, or 3.
  static int last_state = 0;
  
  // decay speed, this acts as a simple filter.
  actual_speed=actual_speed - actual_speed>>2;
  actual_speed+=difference(a, last_state);  // where difference retuns +1, 0, or -1;
  last_state=a;

}
```
(note in the above code, yes, there is a race, but it won't matter since 1 error in actual\_speed won't cause a noticeable problem)

There are more efficient hardware ways of handling an encoder than using timer interrupts. We should probably look at using an external clock source for incrementing a timer. Then speed calculation requires no interrupt. speed = k`*`(current\_pulses\_counted - previous pulses\_counted)/delta\_time. There is more information in the Counter chapters of the atmega 168 datasheet - [here](http://www.atmel.com/dyn/resources/prod_documents/doc2545.pdf). -- Harry

I'm not sure the hardware counters will be that much use, since remember the input from the encoder will be gray code, and we have to differentiate between forward and reverse motion. (and in gray code, "bounces" are entirely acceptable, and likely)  If this arduino has to deal with other sensors as well as the motors/encoders, then yes we certainly need a more efficient way to do it, but if we're only dealing with two motors/encoders, we only need to poll the encoders ~8 times per rev, and the motors will run at a maximum of ~ 20k rpm, thats only 2700 polls per sec, which is well within the limits of a 16Mhz micro.  -- Oliver

Interesting article on creating a PIC based DC motor controller with PID control - [here](http://www.seattlerobotics.org/encoder/200205/pidmc.html).