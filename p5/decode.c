/**
    @file decode.c
    @author Joey Schauer (rjschaue)

    This program decodes a given file using a given code list, storing the
    text file with the given name
*/

#include "codes.h"
#include "bits.h"

/**
    Starts the program

    @param argc number of command-line arguments
    @param argv list of command-line arguments

    @return program exit status
*/
int main(int argc, char *argv[]) 
{
    if (argc < 4) {
        fprintf(stderr, "usage: decode <codes-file> <infile> <outfile>\n");
        return EXIT_FAILURE;
    }

    populateList(argv[1]);
    
    FILE *encoded = fopen(argv[2], "rb");

    if (!encoded) {
        freeList();
        perror(argv[2]);
        return EXIT_FAILURE;
    }

    FILE *output = fopen(argv[3], "w");

    if (!output) {
        freeList();
        perror(argv[3]);
        return EXIT_FAILURE;
    }

    char c[STRING_BUFFER] = "";
    int cLen = 0;

    BitBuffer *buffer;
    buffer->bits = 0x0;
    buffer->bcount = 0;
    
    char symbol = '0';
    int bit = 0;

    while ((bit = readBit(buffer, encoded)) != -1) {
        if (bit == 0) {
            c[cLen] = '0';
            cLen++;
            c[cLen] = '\0';
        } else if (bit == 1) {
            c[cLen] = '1';
            cLen++;
            c[cLen] = '\0';
        }

        if (codeToSym(c) != -2) {
            symbol = (char) codeToSym(c);
            fprintf(output, &symbol);
            cLen = 0;
            c[cLen] = '\0';
        }
    }

    return EXIT_SUCCESS;
}
