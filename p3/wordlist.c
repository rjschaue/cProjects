/**
    @file wordlist.c
    @author Joey Schauer (rjschaue)
    
    This program gets a list of words to be used for hangman
*/

#include "wordlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char words[MAX_WORDS][WORD_LENGTH_MAX];

int wordCount = 0;

void readWords( char const *filename ) {
    FILE *stream = fopen( filename, "r" );

    if (!stream) {
        fprintf(stderr, "Can't open word file");
        exit(EXIT_FAILURE);
    }
    
    char string[MAX_WORDS] = ""; 
    while (fscanf(stream, "%s", string) == 1) {
        wordCount++;
        if (wordCount > MAX_WORDS) {
            fprintf(stderr, "Invalid word file");
            exit(EXIT_FAILURE);
        }
        if (strlen(string) > WORD_LENGTH_MAX - 1) {
            fprintf(stderr, "Invalid word file");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; string[i]; i++) {
            if (string[i] < 'a' || string[i] > 'z') {
                fprintf(stderr, "Invalid word file");
                exit(EXIT_FAILURE);
            }
        }
        strcpy(words[wordCount - 1], string);
    }

    fclose(stream);
}
