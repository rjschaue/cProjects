/**
    @file pointlist.h
    @author Joey Schauer (rjschaue)

    This header contains the Pointlist struct and declarations of functions for
    working with a Pointlist
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "point.h"

/** This struct contains a resizeable array of pointers to Point instances */
typedef struct {
  /** Counts the number of Points currently on the list */
  int count;
  /** The current capacity of the list */
  int cap;
  /** A pointer to a dynamically allocated array of pointers to Point */
  Point **list;
} Pointlist;

/**
    This function dynamically allocates an instance of Pointlist
    and initalizes it's fields
*/
Pointlist *createPointlist();

/**
    This function frees all dynamically allocated memory used by Pointlist

    @param ptlist the Pointlist to free memory for
*/
void freePointlist( Pointlist *ptlist );

/**
    This function adds the given Point to the given Pointlist, resizing if
    necessary. Returns true if successful, false if otherwise

    @param ptlist the Pointlist to add to
    @param pt the Point to add to the Pointlist
    @return true if successful, false if otherwise
*/
bool addPoint( Pointlist *ptlist, Point *pt );

/**
    This function removes the Point with the given name from the given
    Pointlist, returning true if successful, false if there is no Point
    with the given name
    
    @param ptlist is the Pointlist to remove from
    @param name is the name of the Point to remove
    @return true if successful, false if there is no Point with the given name
*/ 
bool removePoint( Pointlist *ptlist, char const *name );

/**
    This function goes through the Points on the given Pointlist, printing
    the selected ones

    @param ptlist is the Pointlist to print
    @param ref are the Coords of the user
    @param test is a pointer to a function used to decide which Points to print
    @param data is a pointer to additional data
*/
void listPoints( Pointlist *ptlist, Coords const *ref,
                 bool (*test)( Point const *pt, void *data ), void *data );
