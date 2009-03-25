mouse: mouse.o
	gcc -o $@ $< -lpthread

mouse.o: mouse.c
	gcc -c -o $@ $<

clean:
	rm -f mouse mouse.o

