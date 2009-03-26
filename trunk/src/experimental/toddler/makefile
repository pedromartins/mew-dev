INCLUDES = -I.# -I/usr/include/opencv/ -I.
LIBS = -lpthread# -lcv -lhighgui
LIB_PATH = -L/usr/lib/

all: toddler

toddler : toddler.cpp serial.cpp mew_i2c.c arduino.cpp
	g++  toddler.cpp serial.cpp mew_i2c.c arduino.cpp ${LIBS} -o toddler

#toddler.o:	mew_i2c.o
#	g++ -c ${INCLUDES} ${LIBS} ${LIB_PATH} -o toddler.o



clean:
	rm *.o
	rm toddler
