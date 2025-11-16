all: arcfour example

example: example.o
	gcc example.o -o example -Wall -O2

example.o: example.c
	gcc -c -O2 -Wall example.c -o example.o

arcfour: arcfour.o
	gcc -D_GNU_SOURCE arcfour.o -o arcfour.so -fPIC -shared -ldl

arcfour.o: arcfour.c
	gcc -c -O2 -Wall arcfour.c

clean:
	rm -f *.o *.so example