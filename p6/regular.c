/**
    @file regular.c
    @author Joey Schauer (rjschaue)

    This program will take a regular expression and compare it against any
    number of given strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern.h"
#include "parse.h"

// On the command line, which argument is the pattern.
#define PAT_ARG 1

// On the command line, which argument is the input file.
#define FILE_ARG 2

// Buffer for lines read from input
#define STRING_BUFFER 1024

// Maximum string length
#define STRING_MAX 100

// Red ANSI escape code
#define RED "\x1b[31m"

// Black ANSI escape code
#define BLACK "\x1b[0m"

/**
  Function used to print out all matches
  @param pat is the pattern to match to the string
  @param str is the string to be matched to the pattern
*/
void reportMatches( Pattern *pat, char const *str )
{
  // Report all the matches.
  int len = strlen( str );
  int pos = 0;
  bool match = false;
  for ( int begin = 0; begin <= len; begin++ ) {
    for ( int end = begin; end <= len; end++ ) {
      if ( matches( pat, begin, end ) ) {
        bool more = false;
        if (end < len && matches(pat, begin, end + 1)) {
          more = true;
        }
        if (!more) {
          for (int j = pos; j < begin; j++)
            printf( "%c", str[ j ] );
            printf(RED);
            // Print the matchng string.
          for ( int k = begin; k < end; k++ )
            printf( "%c", str[ k ] );

          printf(BLACK);
          pos = end;
          match = true;
        }
      }
    }
  }
  if (match) {
    for (int i = pos; i < len; i++) {
      printf( "%c", str[i] );
    }
    printf("\n");
  } 
}

/**
   Entry point for the program, parses command-line arguments, builds
   the pattern and then tests it against lines of input.

   @param argc Number of command-line arguments.
   @param argv List of command-line arguments.
   @return exit status for the program.
*/
int main( int argc, char *argv[] )
{
  //Prints error if invalid number of command line arguments
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "usage: regular <pattern> [input-file.txt]\n");
    return EXIT_FAILURE;
  }
  
  //Creates new file then attempts to open given input file
  FILE *input = NULL;

  if (argc > 2) {
    input = fopen(argv[FILE_ARG], "r");
    if (!input) {
      fprintf(stderr, "Can't open input file: %s\n", argv[2]);
      return EXIT_FAILURE;
    }
  }
  
  //Parses the given pattern from the command line
  Pattern *pat = parsePattern(argv[PAT_ARG]);
  
  //Loop to iterate through a given input file or arguments from the command line
  while (true) {
    char str[STRING_BUFFER];
    
    if (input) {
      if (fscanf(input, "%1023[^\n]%*[\n]", str) > 0) {
        if (strlen(str) > STRING_MAX) {
          fprintf(stderr, "Input line too long\n");
          return EXIT_FAILURE;
        }
      } else {
        fclose(input);
        break;
      }
    } else {
      if (scanf("%1023[^\n]%*[\n]", str) > 0) {
        if (strlen(str) > STRING_MAX) {
         fprintf(stderr, "Input line too long\n");
         return EXIT_FAILURE;
        }
      } else {
        break;
      }
    }
    //Locates all pattern matches in the string
    pat->locate( pat, str );
  
    //Prints out all matches
    reportMatches(pat, str);
  }

  //Frees memory from all patterns
  pat->destroy( pat );

  return EXIT_SUCCESS;
}
