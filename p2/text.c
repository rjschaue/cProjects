/**
    
*/

#include "encoding.h"

void printHeader( int width, int height ) {
    printf("P3\n");
    printf("%d %d\n", width, height);
    printf("%d\n", CMAX);
}


void printValue( unsigned char c ) {

}
