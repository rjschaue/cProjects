/**
    @file encoding.h
    @author Joey Schauer (rjschaue)
    
    This program prints out the relevant header and color values
    for a ppm file.
*/

/** Maximum color component value. */
#define CMAX 255

/**
    Prints the header for the ppm file using a given width and height.

    @param width the width of the draw box
    @param height the height of the draw box
*/
void printHeader( int width, int height );

/**
    Prints out the given RGB character

    @param c is the character to be printed out
*/
void printValue( unsigned char c );
