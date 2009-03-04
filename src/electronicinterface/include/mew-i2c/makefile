demo:	./build/mew_i2c.o ./build/mew_i2c_demo.o
	gcc -g -o ./demo ./build/mew_i2c.o ./build/mew_i2c_demo.o

./build/mew_i2c.o:	mew_i2c.c mew_i2c.h
	gcc -g -c mew_i2c.c -o ./build/mew_i2c.o

./build/mew_i2c_demo.o:	mew_i2c_demo.c
	gcc -g -c mew_i2c_demo.c -o ./build/mew_i2c_demo.o

clean:
	rm ./build/*
	rm ./demo
