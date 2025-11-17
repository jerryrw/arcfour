all: arcfour example

example: example.o
	gcc example.o -o example -Wall -O2 -L./ -larcfour

example.o: example.c
	gcc -c -O2 -Wall example.c -o example.o

arcfour: arcfour.o
# Linux shared library
#	gcc -D_GNU_SOURCE arcfour.o -o arcfour.so -fPIC -shared -ldl
# macOS dynamic library
	gcc -dynamiclib arcfour.o -o libarcfour.dylib 

arcfour.o: arcfour.c
	gcc -c -O2 -Wall arcfour.c

clean:
	rm -f *.o *.so example