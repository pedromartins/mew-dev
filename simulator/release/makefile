
OBJS = 
CC = gcc
DEBUG = -g
CFLAGS = -Iinclude -Llib -lsim -Wall $(DEBUG)

samples: sample sample2

sample: samples/sample.c include/sim.h lib/libsim.a
	$(CC) samples/sample.c $(CFLAGS) -o bin/sample
	 
sample2: samples/sample2.c include/sim.h lib/libsim.a
	$(CC) samples/sample.c $(CFLAGS) -o bin/sample2

clean:
	rm -f bin/* *~
