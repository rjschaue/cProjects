/**
   @file geometry.c
   @author Joey Schauer (rjschaue)
   
   This program checks to see if given coordinates fall inside the given
   coordinates for a triangle using the left of formula.
*/

#include "geometry.h"

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
