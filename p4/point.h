/**
    @file point.h
    @author Joey Schauer (rjschaue)

    This header contains the Coords and Point structs along with any
    relevant functions for working with these structs
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifndef POINT_H
#define POINT_H
/** Maximum length of a name in Point */
#define NAME_LENGTH 20
/** Buffer for holding a name string */
#define STRING_BUFFER 100
/** Max length of a description */
#define DESC_LENGTH 1024
/** Buffer for holding a description string */
#define MAX_BUFFER 4095
/** Degrees to radians calculation */
#define DEG_TO_RAD ( M_PI / 180 )
/** Radius of the earth */
#define EARTH_RADIUS 3959.0
/** Minimum latitude value */
#define LAT_MIN -90
/** Maximum latitude value */
#define LAT_MAX 90
/** Minimum longitude value */
#define LON_MIN -180
/** Maximum longitude value */
#define LON_MAX 180

/** Representation for a location, in latitude and longitude. */
typedef struct {
  /** Latitude value for a global location. */
  double lat;
  
  /** Longitude value for a global location. */
  double lon;
} Coords;

/** Representation for a point with a name, coordinates and description */
typedef struct {
  /** The name of the point */
  char name[NAME_LENGTH + 1];

  /** The latitude and longitude of the point */
  Coords location;

  /** A description of the point */
  char *desc;
} Point;

/**
    Creates a new Point based on text read from standard input

    @return a pointer to the new dynamically allocated Point
*/
Point *parsePoint();

/**
    Frees the memory for the given Point

    @param pt is the point to free memory for
*/
void freePoint( Point *pt );

/**
    Prints out a description of the given point in the format required by
    the list, nearby and match commands. Given coordinates of user location
    allows for reporting of how far away the given Point is

    @param pt is the point to report on
    @param ref are the coordinates of the user's location
*/
void reportPoint( Point const *pt, Coords const *ref );

/**
    Returns the distance between two given Coords in miles

    @param c1 is the first set of coordinates
    @param c2 is the second set of coordinates
    @return the distance between the two coordinates in miles
*/
double globalDistance( Coords const *c1, Coords const *c2 );

#endif
