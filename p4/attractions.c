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
#include <ctype.h>

Coords user = {35.772325, -78.673581};

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
  if (globalDistance(&user, &(pt->location)) <= *((double *) data)) {
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
  char matchStr[NAME_LENGTH +1] = "";
  strcpy(matchStr, (char *) data);
  
  char testStr[STRING_BUFFER] = "";
  int testNum = 0;

  for (int i = 0; pt->desc[i]; i++) {
    if (pt->desc[i] != ' ' && pt->desc[i] != '-' && pt->desc[i] != ',') {
      testStr[testNum++] = tolower(pt->desc[i]);
    } else {
      testStr[testNum] = '\0';

      if (strcmp(matchStr, testStr) == 0) {
        return true;
      }
      
      if (strcasestr(testStr, matchStr) != NULL) {
        return true;
      }

      strcpy(testStr, "");
      testNum = 0;
    }
  }
  
  return false;
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

  Pointlist *ptlist = createPointlist();

  while(true) {
    char choice[STRING_BUFFER] = "";
    bool valid = true;

    printf("%d> ", promptNum);
    int state = scanf("%s", choice);

    printf("\n");

    if(state == EOF || strcmp(choice, "quit") == 0) {
      break;
    }

    if(strcmp(choice, "add") == 0) {
      
      Point *pt = parsePoint();
      
      if (pt == NULL) {
        valid = false;
      } else {
        if (addPoint(ptlist, pt) == false) {
          printf("Invalid command\n");
        }
      }  

    } else if(strcmp(choice, "remove") == 0) {
      
      char name[STRING_BUFFER] = "";
      
      if (scanf("%s", name) == 1) {
        if(removePoint(ptlist, name) == false) {
          valid = false;
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "move") == 0) {
      double lat = 0.0;
      double lon = 0.0;

      if (scanf("%lf%lf", &lat, &lon) == 2) {
        if (lat < -90.0 || lat > 90.0 || lon < -180.0 || lon > 180.0) {
          valid = false;
        } else {
          user.lat = lat;
          user.lon = lon;
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "list") == 0) {
      
      listPoints(ptlist, &user, list, NULL);
    
    } else if(strcmp(choice, "nearby") == 0) {
      
      double dist = 0.0;
      double *distp;

      if (scanf("%lf", &dist) == 1) {
        if (dist < 0) {
          valid = false;
        } else {
          distp = &dist;
          listPoints(ptlist, &user, nearby, distp);
        }
      } else {
        valid = false;
      }

    } else if(strcmp(choice, "match") == 0) {
      
      char matchstr[STRING_BUFFER] = "";

      if (scanf("%s", matchstr) == 1) {
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
            listPoints(ptlist, &user, match, matchstr);
          } else {
            valid = false;
          }
        }
      } else {
        valid = false;
      }
    } else if(strcmp(choice, "help") == 0) {
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
  }

  freePointlist(ptlist);
  return EXIT_SUCCESS;
}


