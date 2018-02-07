/** 
    @file geometry.h
    @author Joey Schauer (rjschaue)

    This is the header file for the geometry program
 */

#include <stdbool.h>

/** For the extra credit, the number of horizontal and vertical super-samples
    per pixel.  This is a preprocessor macro with conditional compilation
    code around it.  That lets us replace this value on the gcc line, if
    we want to.  This constant definition should probably be in triangle.c
    rather than in this header, but putting it here lets me give it to you
    with the starter. */
#ifndef SSAMP
#define SSAMP 1
#endif

/**
    Checks to see if the given x, y coordinate falls to the left of the
    vector using the xa, ya and xb, yb coordinates

    @param xa the x coordinate value for the first triangle coordinate
    @param ya the y coordinate value for the first triangle coordinate
    @param xb the x coordinate value for the second triangle coordinate
    @param yb the y coordinate value for the second triangle coordinate
    @param x the x coordinate value to see if it is left of the vector
    @param y the y coordinate value to see if it is left of the vector

    @return true if the coordinate is left of the triangle edge
*/
bool leftOf( double xa, double ya, double xb, double yb,
             double x, double y );

/**
    Checks to see if a given coordinate is inside of the given triangle

    @param x1 is the first x coordinate of the triangle
    @param y1 is the first y coordinate of the triangle
    @param x2 is the second x coordinate of the triangle
    @param y2 is the second y coordinate of the triangle
    @param x3 is the third x coordinate of the triangle
    @param y3 is the third y coordinate of the triangle
    @param x is the x coordinate of the point to be checked
    @param y is the y coordinate of the point to be checked
    @return true if the point is inside the triangle
*/
bool inside( double x1, double y1, double x2, double y2,
             double x3, double y3, double x, double y );
