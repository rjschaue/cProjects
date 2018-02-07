/**
    @file triangle.c
    @author Joey Schauer (rjschaue)

    This program will take integer and floating point values from standard
    input that represent a triangle. The first two are integers for width and
    height of image. The next six are floating point values for each vertex of
    the triangle. The last 3 integers are RGB color values for the triangle.
*/

#include <stdio.h>
#include <stdlib.h>
#include "geometry.h"
#include "encoding.h"

/** Constant for the color black. */
#define BLACK 0

/**
    Program starting point. Reads inital values from standard input.

    @return program exit status
*/
int main()
{
    // Gets width of draw box.
    int width;
    // Gets height of draw box.
    int height;

    // Checks given value for width, exits program if invalid.
    if ( !scanf("%d", &width) || width < 0) {
        return EXIT_FAILURE;
    }

    // Checks given value for height, exits program if invalid.
    if ( !scanf("%d", &height) || height < 0) {
        return EXIT_FAILURE;
    }

    // Gets x1 triangle coordinate value.
    double x1;
    // Gets y1 triangle coordinate value.
    double y1;

    // Checks given value for x1, exits program if invalid.
    if ( !scanf("%lf", &x1)) {
        return EXIT_FAILURE;
    }

    // Checks given value for y1, exits program if invalid.
    if ( !scanf("%lf", &y1)) {
        return EXIT_FAILURE;
    }

    // Gets x2 triangle coordinate value.
    double x2;
    // Gets y2 triangle coordinate value.
    double y2;

    // Checks given value for x2, exits program if invalid.
    if ( !scanf("%lf", &x2)){
        return EXIT_FAILURE;
    }

    // Checks given value for y2, exits program if invalid.
    if ( !scanf("%lf", &y2)) {
        return EXIT_FAILURE;
    }

    // Gets x3 triangle coordinate value.
    double x3;
    // Gets y3 triangle coordinate value.
    double y3;

    // Checks given value for x3, exits program if invalid.
    if ( !scanf("%lf", &x3)) {
        return EXIT_FAILURE;
    }

    // Checks given value for y3, exits program if invalid.
    if ( !scanf("%lf", &y3)) {
        return EXIT_FAILURE;
    }

    // Gets red RGB value for the triangle.
    int red;
    // Gets green RGB value for the triangle.
    int green;
    // Gets blue RGB value for the triangle.
    int blue;

    // Checks given value for red, exits program if invalid.
    if ( !scanf("%d", &red) || red < 0 || red > CMAX) {
        return EXIT_FAILURE;
    }

    // Checks given value for green, exits program if invalid.
    if ( !scanf("%d", &green) || green < 0 || green > CMAX) {
        return EXIT_FAILURE;
    }
    
    // Checks given value for blue, exits program if invalid.
    if ( !scanf("%d", &blue) || blue < 0 || blue > CMAX) {
        return EXIT_FAILURE;
    }
    
    // Prints the header for the triangle in ppm format.
    printHeader(width, height);
    
    // Traverses each pixel in the draw box and checks to see if it is inside
    // the triangle or not, colors with given RGB values if inside the
    // triangle, otherwise colors the pixel black.
    for (double y = 0.5; y < width; y++) {
        for (double x = 0.5; x < height; x++) {
            if (inside(x1, y1, x2, y2, x3, y3, x, y)) {
                printValue(red);
                printValue(green);
                printValue(blue);
            } else {
                printValue(BLACK);
                printValue(BLACK);
                printValue(BLACK);
            }
        }
    }
    
    // Ends the file with a newline character.
    printf("\n");

    return EXIT_SUCCESS;
}
