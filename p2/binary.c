/**
    @file binary.c
    @author Joey Schauer (rjschaue)
    
    This program has functions to print out the header and any RGB values in
    binary format as a ppm image file.    
*/

#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

void printHeader( int width, int height ) {
    printf("P6\n");
    printf("%d %d\n", width, height);
    printf("%d\n", CMAX);
}

void printValue( unsigned char c ) {
    putchar(c);
}
