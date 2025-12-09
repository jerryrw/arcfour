all: test_nist_arcfour

#example: example.o
#	gcc example.o -o example -Wall -O2 -L./ -larcfour

#example.o: example.c
#	gcc -c -O2 -Waxll example.c -o example.o

test_nist_arcfour: test_nist_arcfour.o arcfour.o
	gcc test_nist_arcfour.o arcfour.o -o test_nist_arcfour -Wall -O2

test_nist_arcfour.o: test_nist_arcfour.c
	gcc -c -O2 -Wall test_nist_arcfour.c

arcfour.o: arcfour.c
	gcc -c -O2 -Wall arcfour.c -o arcfour.o

clean:
	rm -f *.o *.so example *.dylib