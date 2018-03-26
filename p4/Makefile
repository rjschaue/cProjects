CC = gcc
CFLAGS = -Wall -std=c99 -g -D_GNU_SOURCE
LDLIBS = -lm 

attractions: attractions.o point.o point.h pointlist.o pointlist.h

attractions.o: point.h pointlist.h
point.o: point.h
pointlist.o: pointlist.h

clean:
	rm -f attractions.o point.o pointlist.o
	rm -f attractions
	rm -f output.txt
