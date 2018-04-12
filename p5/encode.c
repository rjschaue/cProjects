/**
    @file encode.c
    @author Joey Schauer (rjschaue)

    This program is used to encode a given file using the given code list,
    storing the resulting binary file with a given name
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
        fprintf(stderr, "usage: encode <codes-file> <infile> <outfile>\n");
        return EXIT_FAILURE;
    }

    populateList(argv[1]);
    
    FILE *input = fopen( argv[2], "r" );

    if (!input) {
        freeList();
        perror(argv[2]);
        return EXIT_FAILURE;
    }

    FILE *encoded = fopen( argv[3], "wb" );

    if (!encoded) {
        freeList();
        perror(argv[3]);
        return EXIT_FAILURE;
    }

    char c[1] = {};

    BitBuffer buffer = { 0x00, 0 };

    while (fread(c, 1, 1, input) != 0) {

        if (c[0] < 'a' || c[0] > 'z') {
            if (c[0] != ' ' && c[0] != '\n') {
                freeList();
                fprintf(stderr, "Invalid input file\n");
                return EXIT_FAILURE;
            }
        }
        
        char const *code = symToCode(c[0]);
        
        if (code != NULL) {
            writeBits(code, &buffer, encoded);
        }
    }

    freeList();
    flushBits(&buffer, encoded);

    return EXIT_SUCCESS;
}
