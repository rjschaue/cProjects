/**
    @file point.c
    @author Joey Schauer (rjschaue)

    This component defines the functions for working with Coords and Points
*/

#include "point.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NAME_MAX_LEN 20
#define STRING_BUFFER 30
#define DESC_BUFFER 1025
#define DEG_TO_RAD ( M_PI / 180 )
#define EARTH_RADIUS 3959.0

Point *parsePoint() 
{
  Point *p = (Point *)malloc(sizeof(Point));
  
  char string[STRING_BUFFER];
  
  if (scanf("%s", string) == 1) {
    if (strlen(string) > NAME_MAX_LEN) {
      return NULL;
    }
    strcpy(p->name, string);
  } else {
    return NULL;
  }

  if (scanf("%lf%lf", p->location->lat, p->location->lon) != 2) {
    return NULL;
  }
  
  char description[DESC_BUFFER];
  if (scanf("%1024[^\n\t]", description) != 1) {
    return NULL;
  }

  p->desc = (char *)malloc( strlen(description) + 1 );
  strcpy(p->desc, description);

  getchar();

  return p;
}

void freePoint( Point *pt ) 
{
  free(pt->desc);
  free(pt);
}

void reportPoint( Point const *pt, Coords const *ref ) 
{
  printf("%s%.1lf\n", pt->name, globalDistance(ref, pt->location));
  printf("  %s\n", pt->desc);
}

double globalDistance( Coords const *c1, Coords const *c2 ) 
{
  double v1[] = { cos( c1->lon * DEG_TO_RAD ) * cos( c1->lat * DEG_TO_RAD ),
                  sin( c1->lon * DEG_TO_RAD ) * cos( c1->lat * DEG_TO_RAD ),
                  sin( c1->lon * DEG_TO_RAD ) };

  double v2[] = { cos( c2->lon * DEG_TO_RAD ) * cos( c2->lat * DEG_TO_RAD ),
                  sin( c2->lon * DEG_TO_RAD ) * cos( c2->lat * DEG_TO_RAD ),
                  sin( c2->lon * DEG_TO_RAD ) };

  double dp = 0.0;
  for (int i = 0; i < sizeof( v1 ) / sizeof( v1[0] ); i++ ) {
    dp += v1[ i ] * v2[ i ];
  }

  double angle = acos( dp );

  return EARTH_RADIUS * angle;
}
