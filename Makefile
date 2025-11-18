all: arcfour example

example: example.o
	gcc example.o -o example -Wall -O2 -L./ -larcfour

example.o: example.c
	gcc -c -O2 -Wall example.c -o example.o

arcfour: arcfour.o
# Linux shared library - uncomment this next line for Linux leave comented for macOS
#	gcc -D_GNU_SOURCE arcfour.o -o arcfour.so -fPIC -shared -ldl

# macOS dynamic library- uncoment this next line for macOS leave commented for Linux
	gcc -dynamiclib -exported_symbols_list libapp.exp arcfour.o -o libarcfour.dylib 

arcfour.o: arcfour.c
	gcc -c -O2 -Wall arcfour.c

clean:
	rm -f *.o *.so example *.dylib