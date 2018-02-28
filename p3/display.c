/**
    @file display.c
    @author Joey Schauer (rjschaue)

    This program displays the hangman word and the hangman figure
*/

#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayWord( char word[] )
{
    for ( int i = 0; word[i]; i++ ) {
        printf("%c", word[i]);
        if ( i < strlen(word) - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void displayFigure( int numberOfParts )
{
    if ( numberOfParts == 1 ) {
        printf(" O \n\n");
    } else if ( numberOfParts == 2 ) {
        printf(" O \n");
        printf(" | \n\n");
    } else if ( numberOfParts == 3 ) {
        printf(" O \n");
        printf(" | \n");
        printf(" | \n\n");
    } else if ( numberOfParts == 4 ) {
        printf(" O \n");
        printf("/| \n");
        printf(" | \n\n");
    } else if ( numberOfParts == 5 ) {
        printf(" O \n");
        printf("/|\\\n");
        printf(" | \n\n");
    } else if ( numberOfParts == 6 ) {
        printf(" O \n");
        printf("/|\\\n");
        printf(" | \n");
        printf("/\n\n");
    } else if ( numberOfParts == 7 ) {
        printf(" O \n");
        printf("/|\\\n");
        printf(" | \n");
        printf("/ \\\n\n");
    }
}
