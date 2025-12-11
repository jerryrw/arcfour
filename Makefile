.PHONY: all clean example test test_nist_arcfour

OS = $(shell uname -s)
CC = gcc
CFLAGS = -std=c11 -Wall -O3 -march=native -mtune=native

all: test

#example: example.o
#	gcc example.o -o example -Wall -O2 -L./ -larcfour

#example.o: example.c
#	gcc -c -O2 -Wall example.c -o example.o

test: test_nist_arcfour
	@./test_nist_arcfour || exit 2

test_nist_arcfour: test_nist_arcfour.o arcfour
#$(CC) $(CFLAGS) test_nist_arcfour.o arcfour.o -o test_nist_arcfour
	$(CC) $(CFLAGS) test_nist_arcfour.o -o test_nist_arcfour -L./ -larcfour -Wl,-rpath,'$$ORIGIN'

test_nist_arcfour.o: test_nist_arcfour.c
	$(CC) $(CFLAGS) -c test_nist_arcfour.c

arcfour:  arcfour.o
ifeq ($(OS),Linux)
    # Commands and variables specific to Linux
	$(CC) -D_GNU_SOURCE arcfour.o -o libsha3.so -shared -fPIC -ldl
else ifeq ($(OS),Darwin) # macOS
    # Commands and variables specific to macOS
	$(CC) -dynamiclib -exported_symbols_list libarcfour.exp arcfour.o -o libarcfour.dylib 
endif

arcfour.o: arcfour.c
ifeq ($(OS),Linux)
# Commands and variables specific to Linux
	$(CC) $(CFLAGS) -D_GNU_SOURCE -c arcfour.c -o arcfour.o -fPIC -ldl  

else ifeq ($(OS),Darwin) # macOS
# Commands and variables specific to macOS
	$(CC) $(CFLAGS) -c arcfour.c -o arcfour.o
endif

clean:
	rm -f *.o *.so example *.dylib test_nist_arcfour