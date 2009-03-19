CFLAGS =# -g

test: main.o serial.o arduino.o
	g++ $(CFLAGS) -o test *.o

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

arduino.o: arduino.cpp arduino.h
	g++ $(CFLAGS) -c arduino.cpp

serial.o: serial.cpp serial.h
	g++ $(CFLAGS) -c serial.cpp

clean:
	rm *.o
	rm test
