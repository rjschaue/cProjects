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

/** The coordinates of the user */
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

  //Checks the description for any matching strings
  for (int i = 0; pt->desc[i]; i++) {
    if ((pt->desc[i] != ' ' && pt->desc[i] != '-' && pt->desc[i] != ',')
        || pt->desc[i+1] == '\0') {
      testStr[testNum++] = tolower(pt->desc[i]);
      if (pt->desc[i+1] == '\0') {
        testStr[testNum] = '\0';

        if (strcmp(matchStr, testStr) == 0) {
          return true;
        }
      }
    } else {
      testStr[testNum] = '\0';

      if (strcmp(matchStr, testStr) == 0) {
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
  //Variable to keep track of prompt numbers
  int promptNum = 1;
  
  //Initializes the pointlist to store Points in
  Pointlist *ptlist = createPointlist();

  //While loop to run the program
  while (true) {
    //Gets the string with the user's choice
    char choice[STRING_BUFFER] = "";
    //Gets whether the input is valid or not
    bool valid = true;

    //Prompts the user for a choice
    printf("%d> ", promptNum);
    int state = scanf("%s", choice);

    printf("\n");

    //Ends the program if EOF or user enters quit
    if (state == EOF || strcmp(choice, "quit") == 0) {
      break;
    }

    //Adds the given point if user chooses add
    if (strcmp(choice, "add") == 0) {

      Point *pt = parsePoint();

      if (pt == NULL) {
        valid = false;
      } else {
        if (addPoint(ptlist, pt) == false) {
          printf("Invalid command\n");
        }
      }
      //Removes the given point is user chooses remove
    } else if (strcmp(choice, "remove") == 0) {

      char name[STRING_BUFFER] = "";
      
      if (scanf("%s", name) == 1) {
        if (removePoint(ptlist, name) == false) {
          valid = false;
        }
      } else {
        valid = false;
      }
      //Moves the user's location if user chooses move
    } else if (strcmp(choice, "move") == 0) {
      double lat = 0.0;
      double lon = 0.0;

      if (scanf("%lf%lf", &lat, &lon) == 2) {
        if (lat < LAT_MIN || lat > LAT_MAX
            || lon < LON_MIN || lon > LON_MAX) {
          valid = false;
        } else {
          user.lat = lat;
          user.lon = lon;
        }
      } else {
        valid = false;
      }
      //Lists Points on the list if user chooses list
    } else if (strcmp(choice, "list") == 0) {

      listPoints(ptlist, &user, list, NULL);
      
      //Lists Points nearby the user location if use chooses nearby
    } else if (strcmp(choice, "nearby") == 0) {

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

      //Matches Points with the given word in its description
      //if user chooses match
    } else if (strcmp(choice, "match") == 0) {

      char matchstr[STRING_BUFFER] = "";

      if (scanf("%s", matchstr) == 1) {
        if (strlen(matchstr) > NAME_LENGTH) {
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

      //Lists possible options if user chooses help
    } else if (strcmp(choice, "help") == 0) {
      printf("add <name> <latitude> <longitude> <description>\n");
      printf("remove <name>\n");
      printf("move <latitude> <longitude>\n");
      printf("list\n");
      printf("nearby <distance>\n");
      printf("match <word>\n");
      printf("help\n");
      printf("quit\n");

      //Otherwise user entered invalid input
    } else {
      valid = false;
    }

    //If the user entered invalid input, informs user and discards input
    if (!valid) {
      printf("Invalid command\n");
      scanf("%*[^\n]");
      getchar();
    }
    
    //Increment prompt number
    promptNum++;
  }

  //Frees the Points on the Pointlist and the Pointlist itself
  freePointlist(ptlist);

  return EXIT_SUCCESS;
}
