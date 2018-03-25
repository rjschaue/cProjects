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
}

void freePointlist( Pointlist *ptlist ) 
{
  for(int i = 0; i < ptlist->cap; i++) {
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

void listPoints( Pointlist *ptlist, Coords const *ref,
                 bool (*test)( Point const *pt, void *data ), void *data ) 
{
  
}
