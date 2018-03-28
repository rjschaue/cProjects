/**
    @file point.c
    @author Joey Schauer (rjschaue)

    This component defines the functions for working with Coords and Points
*/

#include "point.h"

Point *parsePoint()
{
  // Dynamically allocates memory for the point
  Point *p = (Point *)malloc(sizeof(Point));

  //Gets a string from stdin for a name and checks validity
  strcpy(p->name, "");

  char string[STRING_BUFFER] = "";
  
  if (scanf("%s", string) == 1) {
    if (strlen(string) > NAME_LENGTH) {
      return NULL;
    }
    strcpy(p->name, string);
  } else {
    return NULL;
  }

  //Gets a latitude and longitude value from stdin and checks validity
  if (scanf("%lf%lf", &(p->location.lat), &(p->location.lon)) != 2) {
    return NULL;
  }
  
  if (p->location.lat < LAT_MIN || p->location.lat > LAT_MAX) {
    return NULL;
  }

  if (p->location.lon < LON_MIN || p->location.lon > LON_MAX) {
    return NULL;
  }

  //Gets a description from stdin and checks validity
  char description[MAX_BUFFER] = "";
  if (scanf("%[^\n\t]", description) == 1) {
    if (strlen(description) > DESC_LENGTH + 1) {
      return NULL;
    }
  } else {
    return NULL;
  }

  p->desc = (char *)malloc( strlen(description) + 1 );

  strcpy(p->desc, description);

  return p;
}

void freePoint( Point *pt )
{
  free(pt->desc);
  free(pt);
}

void reportPoint( Point const *pt, Coords const *ref )
{
  printf("%s (%.1lf miles)\n", pt->name, globalDistance(ref, &(pt->location)));
  printf(" %s\n", pt->desc);
}

double globalDistance( Coords const *c1, Coords const *c2 )
{

  double v1[] = { cos( c1->lon * DEG_TO_RAD ) * cos( c1->lat * DEG_TO_RAD ),
                  sin( c1->lon * DEG_TO_RAD ) * cos( c1->lat * DEG_TO_RAD ),
                  sin( c1->lat * DEG_TO_RAD ) };

  double v2[] = { cos( c2->lon * DEG_TO_RAD ) * cos( c2->lat * DEG_TO_RAD ),
                  sin( c2->lon * DEG_TO_RAD ) * cos( c2->lat * DEG_TO_RAD ),
                  sin( c2->lat * DEG_TO_RAD ) };

  double dp = 0.0;
  for (int i = 0; i < sizeof( v1 ) / sizeof( v1[0] ); i++ ) {
    dp += v1[ i ] * v2[ i ];
  }

  double angle = acos( dp );

  return (EARTH_RADIUS * angle);
}
