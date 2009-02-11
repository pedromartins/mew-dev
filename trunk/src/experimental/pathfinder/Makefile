test: test.o
	g++ -o test ../../simulator/src/*.o test.o 

test.o: test.cpp
	g++ -I ../../simulator/src/ -c test.cpp

make clean:
	rm *.o test
