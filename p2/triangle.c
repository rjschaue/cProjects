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
#define BLACK 0

int main()
{
    int width;
    int height;

    if ( !scanf("%d", &width) || width < 0) {
        return EXIT_FAILURE;
    }

    if ( !scanf("%d", &height) || height < 0) {
        return EXIT_FAILURE;
    }

    double x1;
    double y1;

    if ( !scanf("%lf", &x1)) { 
        return EXIT_FAILURE;
    }

    if ( !scanf("%lf", &y1)) {
        return EXIT_FAILURE;
    }

    double x2;
    double y2;

    if ( !scanf("%lf", &x2)){
        return EXIT_FAILURE;
    }

    if ( !scanf("%lf", &y2)) {
        return EXIT_FAILURE;
    }

    double x3;
    double y3;

    if ( !scanf("%lf", &x3)) {
        return EXIT_FAILURE;
    }

    if ( !scanf("%lf", &y3)) {
        return EXIT_FAILURE;
    }

    int red;
    int green;
    int blue;

    if ( !scanf("%d", &red) || red < 0 || red > CMAX) {
        return EXIT_FAILURE;
    }

    if ( !scanf("%d", &green) || green < 0 || green > CMAX) {
        return EXIT_FAILURE;
    }
    
    if ( !scanf("%d", &blue) || blue < 0 || blue > CMAX) { 
        return EXIT_FAILURE;
    }
    
    printHeader(width, height);
    
    for (int x = 0; i < width; i++) {
        for (int y = 0; k < height; k++) {
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

    printf("\n");

    return EXIT_SUCCESS;
}
