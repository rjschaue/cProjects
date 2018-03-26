/**
    @file pointlist.c
    @author Joey Schauer (rjschaue)

    This component contains functions for working with a Pointlist
*/

#include "pointlist.h"

Coords *user;

Pointlist *createPointlist() 
{
  Pointlist *pl = (Pointlist *)malloc(sizeof(Pointlist));

  pl->count = 0;
  pl->cap = 10;

  pl->list = (Point **)malloc(pl->cap * sizeof(Point *));

  return pl;
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

int compare (const void *p1, const void *p2) {
  Point *point1 = (Point *) p1;
  Point *point2 = (Point *) p2;
  if (globalDistance(&(point1->location), user) < 
      globalDistance(&(point2->location), user)) {
    return -1;
  } else if (globalDistance(&(point1->location), user) == 
      globalDistance(&(point2->location), user)) {
    return 0;
  } else {
    return 1;
  }
}

void listPoints( Pointlist *ptlist, Coords const *ref,
                 bool (*test)( Point const *pt, void *data ), void *data ) 
{
  user->lat = ref->lat;
  user->lon = ref->lon;
  
  qsort(ptlist, ptlist->count, sizeof(Point *), compare);

  for (int i = 0; i < ptlist->count; i++) {
    bool print = test(ptlist->list[i], data);
    if (print) {
      reportPoint(ptlist->list[i], ref);
    }
  }
}


