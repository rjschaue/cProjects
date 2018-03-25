/**
    @file pointlist.c
    @author Joey Schauer (rjschaue)

    This component contains functions for working with a Pointlist
*/

#include "pointlist.h"

Pointlist *createPointlist() 
{

}

void freePointlist( Pointlist *ptlist ) 
{

}

bool addPoint( Pointlist *ptlist, Point *pt ) 
{

}

bool removePoint( Pointlist *ptlist, char const *name ) 
{

}

void listPoints( Pointlist *ptlist, Coords const *ref,
                 bool (*test)( Point const *pt, void *data ), void *data ) 
{

}
