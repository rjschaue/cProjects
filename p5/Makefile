CC = gcc
CFLAGS = -Wall -std=c99 -g

all: encode decode

encode: encode.o codes.o bits.o codes.h bits.h
decode: decode.o codes.o bits.o codes.h bits.h

encode.o: encode.c codes.h bits.h
decode.o: decode.c codes.h bits.h
codes.o: codes.h
bits.o: bits.h

clean:
	rm -f encode.o decode.o codes.o bits.o
	rm -f encode decode
	rm -f output.txt encoded.bin
