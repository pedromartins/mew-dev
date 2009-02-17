
OBJS = simulator.o map.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

sim : $(OBJS)
	ar sr libsim.a $(OBJS)
	cp libsim.a ../release/lib

simulator.o : simulator.h simulator.c map.h
	$(CC) $(CFLAGS) simulator.c

map.o : map.h map.c
	$(CC) $(CFLAGS) map.c

clean:
	rm -f *.o *.a *~
