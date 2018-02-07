/**
    @file binary.c
    @author Joey Schauer (rjschaue)
    
    This program has functions to print out the header and any RGB values in
    binary format as a ppm image file.    
*/

#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

/**
    Prints out the header for a binary ppm file using a given width an height.
    
    @param width the width of the draw box
    @param height the height of the draw box    
*/
void printHeader( int width, int height ) {
    printf("P6\n");
    printf("%d %d\n", width, height);
    printf("%d\n", CMAX);
}

/**
    Prints out a given character as a binary value.

    @param c is the RGB character value to print out
*/
void printValue( unsigned char c ) {
    putchar(c);
}
