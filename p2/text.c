/**
    
*/

#include <stdio.h>
#include <stdlib.h>
#include "encoding.h"
#define MAX_LINE_LENGTH 70
#define INT_LENGTH_CHECK 10

void printHeader( int width, int height ) {
    printf("P3\n");
    printf("%d %d\n", width, height);
    printf("%d\n", CMAX);
}


void printValue( unsigned char c ) {
    static int lineLength = 0;
    
    int color = (int) c;
    int intLength = 1;
    
    while (color >= INT_LENGTH_CHECK) {
        color /= INT_LENGTH_CHECK;
        intLength++;
    }

    if (lineLength + intLength > MAX_LINE_LENGTH) {
        printf("\n%d", color);
        lineLength = intLength;
    } else if (lineLength == 0) {
        printf("%d", color);
        lineLength += intLength;
    } else {
        printf(" %d", color);
        lineLength += intLength + 1;
    }
}
