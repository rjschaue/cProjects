/**
    @file pointlist.c
    @author Joey Schauer (rjschaue)

    This component contains functions for working with a Pointlist
*/

#include "pointlist.h"

Pointlist *createPointlist()
{
  // Dynamically allocates memory for the pointlist
  Pointlist *pl = (Pointlist *)malloc(sizeof(Pointlist));
  
  // Sets the initial count of the list
  pl->count = 0;
  // Sets the initial capacity for the list
  pl->cap = START_LIST_CAP;
  
  //Dynamically allocates memory for the list and initializes Points
  pl->list = (Point **)malloc(pl->cap * sizeof(Point *));
  
  for (int i = 0; i < pl->cap; i++) {
    pl->list[i] = (Point *)malloc( sizeof(Point) );
  }

  return pl;
}

void freePointlist( Pointlist *ptlist )
{
  for (int i = 0; i < ptlist->count; i++) {
    free(ptlist->list[i]);
  }
  free(ptlist);
}

bool addPoint( Pointlist *ptlist, Point *pt )
{
  //Checks to see if the point is already in the list
  for (int i = 0; i < ptlist->count; i++) {
    if (strcmp(ptlist->list[i]->name, pt->name) == 0) {
      return false;
    }
  }
  
  //Reallocs the pointlist if at capacity
  if (ptlist->count == ptlist->cap) {
    ptlist->cap *= 2;
    ptlist->list = (Point **)realloc(ptlist->list, ptlist->cap * sizeof(Point *));
  }

  //Adds the point to the list and increases the count
  ptlist->list[ptlist->count] = pt;

  ptlist->count++;

  return true;
}

bool removePoint( Pointlist *ptlist, char const *name )
{
  //Checks to see if the point is in the list and removes if so
  for (int i = 0; i < ptlist->count; i++) {
    if (strcmp(ptlist->list[i]->name, name) == 0) {
      for (int k = i; k < ptlist->count - 1; k++) {
        ptlist->list[k] = ptlist->list[k+1];
      }
      ptlist->count--;
      return true;
    }
  }
  return false;
}

/**
    Swaps the two given Points

    @param a is the first point
    @param b is the second point
*/
void swap(Point *a, Point *b) {
  Point temp = *a;
  *a = *b;
  *b = temp;
}

/**
    Sorts the given pointlist using the quicksort method

    @param ptlist is the pointlist to sort
    @param low is the start of the pointlist
    @param high is the end of the pointlist
    @param ref are the coordinates of the user
*/
void quickSort(Pointlist *ptlist, int low, int high, Coords const *ref) {
  if (low < high) {
    Coords *pivot = &(ptlist->list[high]->location);
    int i = (low - 1);

    for (int k = low; k <= high - 1; k++) {
      if (globalDistance(&(ptlist->list[k]->location), ref)
          < globalDistance(pivot, ref)) {
        i++;
        swap(ptlist->list[i], ptlist->list[k]);
      }
    }
    swap(ptlist->list[i+1], ptlist->list[high]);
    i++;

    quickSort(ptlist, low, i - 1, ref);
    quickSort(ptlist, i + 1, high, ref);
  }
}

void listPoints( Pointlist *ptlist, Coords const *ref,
                 bool (*test)( Point const *pt, void *data ), void *data )
{
  quickSort(ptlist, 0, ptlist->count - 1, ref);

  for (int i = 0; i < ptlist->count; i++) {
    bool print = test(ptlist->list[i], data);
    if (print) {
      reportPoint(ptlist->list[i], ref);
    }
  }
}


