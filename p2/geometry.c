/**
   @file geometry.c
   @author Joey Schauer (rjschaue)
   
   This program checks to see if given coordinates fall inside the given
   coordinates for a triangle using the left of formula. 
*/

#include "geometry.h"

/**
    Checks to see if the given x and y coordinate falls to the left of the
    vector using the xa, ya and xb, yb coordinates

    @param xa the x coordinate value for the first triangle coordinate
    @param ya the y coordinate value for the first triangle coordinate
    @param xb the x coordinate value for the second triangle coordinate
    @param yb the y coordinate value for the second triangle coordinate
    @param x the x coordinate value to see if it is left of the vector
    @param y the y coordinate value to see if it is left of the vector

    @return true if the coordinate is left of the triangle edge
*/
bool leftOf(double xa, double ya, double xb, double yb, double x, double y) {
    // Gets the x vector of the triangle edge
    double xVectorE = xb - xa;
    // Gets the y vector of the triangle edge
    double yVectorE = yb - ya;
    // Gets the x vector of the coordinate to be checked
    double xVectorP = x - xa;
    // Gets the y vector of the coordinate to be checked
    double yVectorP = y - ya;

    // Checks to see if the cross product of the vectors is less than 0,
    // if so, the given coordinate is left of the triangle edge
    if ((xVectorE * yVectorP - yVectorE * xVectorP) <= 0) {
        return true;
    } else {
        return false;
    }
}

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
bool inside(double x1, double y1, double x2, double y2, double x3, double y3,
            double x, double y) {
    // Checks to see if the given point is to the left of every edge of
    // the triangle
    if ( leftOf(x1, y1, x2, y2, x, y) && leftOf( x2, y2, x3, y3, x, y) &&
         leftOf(x3, y3, x1, y1, x, y)) {
        return true;
    } else {
        return false;
    }    
}
