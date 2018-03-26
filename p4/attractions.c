/**
    @file attractions.c
    @author Joey Schauer (rjschaue)
    
    This component defines the main function and any other functions
    not provided by pointlist or point. This is responsible for reading user
    commands and performing them.  
*/

#include "point.h"
#include "pointlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Coords *user;

/**
    Static function used to implement the list command

    @param pt is the Point to compare data against
    @param data is data used in the function implementation
    @return true if the Point should be output or false if not
*/
static bool list(Point const *pt, void *data) {
  return true;
}

/**
    Static function used to implement the nearby command

    @param pt is the Point to compare data against
    @param data is data used in the function implementation
    @return true if the Point should be output or false if not
*/ 
static bool nearby(Point const *pt, void *data) {
  double *distance = (double *) data;

  if (globalDistance(user, &(pt->location)) <= *distance) {
    return true;
  } else {
    return false;
  }
}
/**
    Static function used to implement the match command

    @param pt is the Point to compare data against
    @param data is data used in the function implementation
    @return true if the Point should be output or false if not
*/ 
static bool match(Point const *pt, void *data) {
  char matchstr[NAME_LENGTH +1] = "";
  strcpy(matchstr, (char *) data);

  if (strcmp(matchstr, pt->name) == 0) {
    return true;
  } else {
    return false;
  }
}

/**
    Starts the program

    @param argc number of command-line arguments
    @param argv list of command-line arguments

    @return program exit status
*/
int main(int argc, char *argv[])
{
  int promptNum = 1;
  user->lat = 35.772325;
  user->lon = -78.673581;

  Pointlist *ptlist = createPointlist();

  while(true) {
    char choice[STRING_BUFFER] = "";
    bool valid = true;

    printf("%d> ", promptNum);
    scanf("%99s", choice);

    if(choice[0] == EOF || strcmp(choice, "quit")) {
      break;
    }

    if(strcmp(choice, "add")) {
      
      Point *pt = parsePoint();
      
      if (pt == NULL) {
        valid = false;
      } else {
        if (addPoint(ptlist, pt) == false) {
          printf("Invalid command\n");
        }
      }  

    } else if(strcmp(choice, "remove")) {
      
      char name[STRING_BUFFER] = "";
      
      if (scanf("%99s", name) == 1) {
        if(removePoint(ptlist, name) == false) {
          valid = false;
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "move")) {
      double lat = 0.0;
      double lon = 0.0;

      if (scanf("%lf%lf", &lat, &lon) == 2) {
        if (lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) {
          valid = false;
        } else {
          user->lat = lat;
          user->lon = lon;
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "list")) {
      
      listPoints(ptlist, user, list, NULL);
    
    } else if(strcmp(choice, "nearby")) {
      
      double dist = 0.0;
      double *distp;

      if (scanf("%lf", &dist) == 1) {
        if (dist < 0) {
          valid = false;
        } else {
          distp = &dist;
          listPoints(ptlist, user, nearby, distp);
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "match")) {
      
      char matchstr[STRING_BUFFER] = "";

      if (scanf("%99s", matchstr) == 1) {
        if (strlen(matchstr) > 20) {
          valid = false;
        } else {
          
          bool validstr = true;
          
          for (int i = 0; i < strlen(matchstr) && validstr; i++) {
            if (matchstr[i] < 'a' || matchstr[i] > 'z') {
              validstr = false;
            }
          }

          if (validstr) {
            listPoints(ptlist, user, match, matchstr);
          } else {
            valid = false;
          }
        }
      } else {
        valid = false;
      }
    } else if(strcmp(choice, "help")) {
      printf("add <name> <latitude> <longitude> <description>\n");
      printf("remove <name>\n");
      printf("move <latitude> <longitude>\n");
      printf("list\n");
      printf("nearby <distance>\n");
      printf("match <word>\n");
      printf("help\n");
      printf("quit\n");
    } else {
      valid = false;
    }
    
    if (!valid) {
      printf("Invalid command\n");
      scanf("%*[^\n]");
      getchar();
    }
    
    promptNum++;

    printf("\n");
  }

  freePointlist(ptlist);
}


