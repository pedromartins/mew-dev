CFLAGS = -g

sensortest: main.o serial.o sensors.o
	g++ $(CFLAGS) -o sensortest *.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

serial.o: serial.cpp serial.h
	g++ $(CFLAGS) -c serial.cpp

sensors.o: sensors.cpp sensors.h
	g++ $(CFLAGS) -c sensors.cpp

clean:
	rm *.o
	rm sensortest
