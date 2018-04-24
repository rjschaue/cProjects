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

#define RED "\x1b[31m"

#define BLACK "\x1b[0m"

// You won't need this function in the final version of your program.
// It prints out the input string and all matches of the pattern inside
// it.
void reportMatches( Pattern *pat, char const *pstr, char const *str )
{
  // Report the original string and copies of all the matches.
  int len = strlen( str );
  //bool match = false;
  for ( int begin = 0; begin <= len; begin++ ) {
    for ( int end = begin; end <= len; end++ ) {
      if ( matches( pat, begin, end ) ) {

        //match = true;
        
        for (int j = 0; j < begin; j++) 
          printf( "%c", str[ j ] );
        
        printf(RED);
        // Print the matchng string.
        for ( int k = begin; k < end; k++ )
          printf( "%c", str[ k ] );
        
        printf(BLACK);
        for ( int l = end; l < len; l++ ) 
          printf( "%c", str[ l ] );

        printf("\n");
      } 
    }
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
  // Temporary code to show how the pattern matching mechanism is
  // supposed to work.  You'll need to replace this with code to do
  // what the program is actually supposed to do, get a pattern from
  // the command line, match it against lines from an input file, and
  // report matching lines with occurrences of the matches
  // highlighted.
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "usage: regular <pattern> [input-file.txt]\n");
    return EXIT_FAILURE;
  }

  FILE *input;

  if (argc > 2) {
    input = fopen(argv[2], "r");
    if (!input) {
      fprintf(stderr, "Can't open input file: %s\n", argv[2]);
      return EXIT_FAILURE;
    }
  }

  Pattern *pat = parsePattern(argv[1]);
  
  while (true) {
    char str[STRING_BUFFER];
    
    if (input) {
      if (fscanf(input, "%1023[^\n]%*[\n]", str) > 0) {
        if (strlen(str) > 100) {
          fprintf(stderr, "Input line too long\n");
          return EXIT_FAILURE;
        }
      } else {
        fclose(input);
        break;
      }
    } else {
      if (scanf("%1023s", str) != EOF) {
        if (strlen(str) > 100) {
         fprintf(stderr, "Input line too long\n");
         return EXIT_FAILURE;
        }
      } else {
        break;
      }
    }
    
    pat->locate( pat, str );
  
    reportMatches(pat, argv[1], str);
  }

  pat->destroy( pat );

  return EXIT_SUCCESS;
}
