.PHONY: all clean example test test_nist_arcfour

OS = $(shell uname -s)
CC = gcc
CFLAGS = -std=c11 -Wall -O3 -march=native -mtune=native

all: arcfour example

example: example.o
	$(CC) $(CFLAGS) example.o -o example -L./ -larcfour -Wl,-rpath,'$$ORIGIN'

example.o: example.c
	$(CC) $(CFLAGS) -c example.c -o example.o

#test suite
test: test_nist_arcfour
	@./test_nist_arcfour || exit 2

test_nist_arcfour: test_nist_arcfour.o arcfour
	$(CC) $(CFLAGS) test_nist_arcfour.o -o test_nist_arcfour -L./ -larcfour -Wl,-rpath,'$$ORIGIN'

test_nist_arcfour.o: test_nist_arcfour.c
	$(CC) $(CFLAGS) -c test_nist_arcfour.c

#main library build
arcfour:  arcfour.o
ifeq ($(OS),Linux)
    # Commands and variables specific to Linux
	$(CC) -D_GNU_SOURCE arcfour.o -o libsha3.so -shared -fPIC -ldl
else ifeq ($(OS),Darwin)
    # Commands and variables specific to macOS
	$(CC) -dynamiclib -exported_symbols_list symbols/libarcfour.exp arcfour.o -o libarcfour.dylib 
endif

arcfour.o: arcfour.c
ifeq ($(OS),Linux)
# Commands and variables specific to Linux
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c arcfour.c -o arcfour.o -fPIC -ldl  
else ifeq ($(OS),Darwin) 
# Commands and variables specific to macOS
	$(CC) $(CFLAGS) -c arcfour.c -o arcfour.o
endif

clean:
	rm -f *.o *.so example *.dylib test_nist_arcfour