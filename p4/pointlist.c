/**
    @file pointlist.c
    @author Joey Schauer (rjschaue)

    This component contains functions for working with a Pointlist
*/

#include "pointlist.h"

Pointlist *createPointlist() 
{
  Pointlist *pl = (Pointlist *)malloc(sizeof(Pointlist));

  pl->count = 0;
  pl->cap = 10;

  pl->list = (Point **)malloc(pl->cap * sizeof(Point *));
  
  for (int i = 0; i < pl->cap; i++) {
    pl->list[i] = (Point *)malloc( sizeof(Point) );
  }

  return pl;
}

void freePointlist( Pointlist *ptlist ) 
{
  for(int i = 0; i < ptlist->count; i++) {
    free(ptlist->list[i]);
  }
  free(ptlist);
}

bool addPoint( Pointlist *ptlist, Point *pt ) 
{
  for(int i = 0; i < ptlist->count; i++) {
    if (strcmp(ptlist->list[i]->name, pt->name) == 0) {
      return false;
    }
  } 
  
  if(ptlist->count == ptlist->cap) {
    ptlist->cap *= 2;
    ptlist->list = (Point **)realloc(ptlist->list, ptlist->cap * sizeof(Point *));
  }
  
  ptlist->list[ptlist->count] = pt;

  ptlist->count++;

  return true;
}

bool removePoint( Pointlist *ptlist, char const *name ) 
{
  for(int i = 0; i < ptlist->count; i++) {
    if (strcmp(ptlist->list[i]->name, name) == 0) {
      for(int k = i; k < ptlist->count - 1; k++) {
        ptlist->list[k] = ptlist->list[k+1];
      }
      ptlist->count--;
      return true;
    }
  }
  return false;
}

void swap(Point *a, Point *b) {
  Point temp = *a;
  *a = *b;
  *b = temp;
}

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


