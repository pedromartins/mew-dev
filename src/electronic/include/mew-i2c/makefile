INCLUDES = -I/usr/include/opencv/ -I.
LIBS = -lcv -lhighgui
LIB_PATH = -L/usr/lib/


toddles : toddles.cpp serial.cpp sensors.cpp mew_i2c.c
	g++ serial.cpp sensors.cpp mew_i2c.c toddles.cpp ${LIBS} -o toddles

#toddles.o:	mew_i2c.o
#	g++ -c ${INCLUDES} ${LIBS} ${LIB_PATH} -o toddles.o


#mew_i2c.o:	mew_i2c.c mew_i2c.h
#	gcc -g -c mew_i2c.c -o mew_i2c.o

#mew_i2c_demo.o:	mew_i2c_demo.c
#	gcc -g -c mew_i2c_demo.c -o mew_i2c_demo.o

clean:
	rm *.o
	rm toddles
