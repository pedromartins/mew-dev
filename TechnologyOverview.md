# Well, things have moved on a bit since this, maybe use the more specific pages for discussing tech stuff now! {ian} #

# Introduction #

We are looking to build a modular system, that is, one in which the functionality of the separate entities is cleanly and clearly defined and separated. We will implement a communications protocol across this system enabling various parts to 'talk' to each other.

This lets us abstract out various functionality into the places it is necessary. The part of our system dealing with (potentially) image acquisition has no idea about how to control a servo!

An over-riding principle is speed and ease of development.

# Control System Overview #

_As a first, preliminary, draft Hok and I propose the following architecture:_

~~===[Gumstix](http://www.gumstix.com) embedded linux computer running both the AI and image acquisition/processing===~~

These things are amazing, a complete ARM based linux 2.6 system, with 256Mb RAM and 256Mb flash (and a micro sd card socket), full USB host capability and the size of an AA battery. For ~£100!

## alas, the gumstix is no more for us, x86 now! ##

### [Arduino](http://www.arduino.cc) based sensor control systems ###

Arduino is ATMEL Atmega based microcontroller platform. There are a whole host of incredible libraries available (including ones for servo control, distance sensing with ultrasonic sensors, i2c communication protocol and so on) and various pre-build boards as well as a great IDE. At it's heart however the Arduino is just a nice bootloader on at atmega, so we would be free if size/weight become an issue to embed these devices directly into the robot on our own custom boards (anyone done PCB etching before?)

The idea here is that the arduinos deal with all the nitty-gritty servo and sensor related stuff that we don't want bothering the AI CPU. The AI sends a command to the servo to move to such and such a orientation and it just does it. This could obviously be extended (since the arduino is actually quite an agile platform, and _fairly_ powerful) to something like a robotic-clamp controller, such that the AI would signal to the controller, 'I have positioned you over an item, please grab it'. The arduino would then control the related servos and force-resistance sensors necessary to make the grab before the AI made visual confirmation.

### [I²C](http://en.wikipedia.org/wiki/I²C) based communications protocol ###

Ask the eee guys about this! A simple bus protocol that allows us to address up to 112 nodes (please say we don't need more servos than that?) and send and request simple data.
We would writing our own _simple_ protocol over this to control the servos and sensors. The gumstix has an I²C bus, and the arduino has a library (The Wire) that does it.

### [OpenCV](http://opencv.willowgarage.com/wiki/) computer vision library ###

As we saw on the noisy macbook (with the facial recognition thing), OpenCV is awesome. It's a computer vision library (which has an embedded version, if we need it) with Python bindings. It can do object recognition with haar-classifiers (a type of cool machine learning) and about a million other things which will no doubt soon be discussed at length elsewhere!