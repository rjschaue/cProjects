/**
    
*/

#include "geometry.h"

bool leftOf(double xa, double ya, double xb, double yb, double x, double y) {
    double xVectorE = xb - xa;
    double yVectorE = yb - ya;
    double xVectorP = x - xa;
    double yVectorP = y - ya;

    if ((xVectorE * yVectorP - yVectorE * xVectorP) <= 0) {
        return true;
    } else {
        return false;
    }
}

bool inside(double x1, double y1, double x2, double y2, double x3, double y3,
            double x, double y) {
    if ( leftOf(x1, y1, x2, y2, x, y) && leftOf( x2, y2, x3, y3, x, y) &&
         leftOf(x3, y3, x1, y1, x, y)) {
        return true;
    } else {
        return false;
    }    
}
