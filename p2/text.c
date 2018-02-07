/**
    @file text.c
    @author Joey Schauer (rjschaue)
    
    This program prints out the header and RGB values for a text ppm file.
*/

#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"

/** The max length for a line of text */
#define MAX_LINE_LENGTH 70
/** The value to divide by to check the length of an integer */
#define INT_LENGTH_CHECK 10

void printHeader( int width, int height ) {
    printf("P3\n");
    printf("%d %d\n", width, height);
    printf("%d\n", CMAX);
}

void printValue( unsigned char c ) {
    // The static variable to determine the current length of the line.
    static int lineLength = 0;
    
    // Converts the character to an integer.
    int color = c;
    // Gets the length of the integer.
    int intLength = 1;
    
    // Determines the length of the color by division.
    while (color >= INT_LENGTH_CHECK) {
        color /= INT_LENGTH_CHECK;
        intLength++;
    }

    // Prints out the character, ensuring the lines do not exceed a maximum
    // length value and are separated by spaces.
    if (lineLength + intLength + 1 > MAX_LINE_LENGTH) {
        printf("\n%d", c);
        lineLength = intLength;
    } else if (lineLength == 0) {
        printf("%d", c);
        lineLength += intLength;
    } else {
        printf(" %d", c);
        lineLength += intLength + 1;
    }
}
