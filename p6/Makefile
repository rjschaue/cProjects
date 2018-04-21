CC = gcc
CFLAGS = -Wall -std=c99 -g

regular: regular.o pattern.o parse.o pattern.h parse.h

regular.o: pattern.h parse.h
pattern.o: pattern.h
parse.o: parse.h

clean:
	rm -f parse.o pattern.o regular.o
	rm -f regular
	rm -f output.txt stderr.txt
