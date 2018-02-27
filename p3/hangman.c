/**
    @file hangman.c
    @author Joey Schauer (rjschaue)
    
    This program will simulate the hangman game by taking a list of words,
    selecting a random word for the user to guess, and output the word or
    hangman character as guesses are made.
*/

#include "display.h"
#include "wordlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define NUMBER_OF_LETTERS 26
#define MAX_PARTS 7

/**
    Starts the program
    
    @param argc the number of command line arguments given
    @param argv an array of strings for each argument
    
    @return program exit status
*/
int main( int argc, char *argv[] ) {
    if (argc < 2) {
        fprintf(stderr, "usage: hangman <> []");
        return EXIT_FAILURE;
    } else if (argc > 2 && atoi(argv[2]) < 0) {
        fprintf(stderr, "usage: hangman <%s> [%s]", argv[1], argv[2]);
        return EXIT_FAILURE;
    }
      
    readWords( argv[1] );
   
    int seed = 0;
    if (argc > 2) {       
        seed = atoi(argv[2]);
    } 

    if (seed > 0) {
        srand(seed);
    } else {
        srand(time(NULL));
    }

    while (true) {
        int index = rand() % wordCount;

        char word[WORD_LENGTH_MAX];
        strcpy(word,  words[index]);

        int letterLength = NUMBER_OF_LETTERS;
        char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 
                          'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
                          'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
                          'y', 'z'};

        int wordLength = strlen(word + 1);
        char tempWord[wordLength];
        strcpy(tempWord, word);
        for (int i = 0; tempWord[i]; i++) {
            tempWord[i] = '_';
        }

        int numberOfParts = 0;

        while (true) {
            displayFigure(numberOfParts);
            if (numberOfParts == MAX_PARTS) {
                printf("You lose!\n");
                printf("The word was %s\n", word);
                break;
            }
            displayWord(tempWord);

            printf("Remaining letters: ");
            for (int i = 0; i < letterLength; i++) {
                printf("%c", letters[i]);
                if (i < letterLength - 1) {
                    printf(" ");
                }
            }
            printf("\n");
            
            char letter[MAX_WORDS] = "";
            bool letterFound = false;
            while (true) {
                printf("letter> ");
                scanf("%s", letter);
                printf("\n");
                if (strlen(letter) > 1) {
                    printf("Invalid letter\n");
                } else {
                    for (int i = 0; i < letterLength; i++) {
                        if (letters[i] == letter[0]) {
                            letterLength--;
                            for (int k = i; k < letterLength; k++) {
                                letters[k] = letters[k + 1];
                            }
                            letterFound = true;
                            break;
                        }
                    }
                    if (letterFound) {
                        break;
                    } else {
                        printf("Invalid Letter\n");
                    }
                }
            }
            bool letterMatch = false;
            for (int i = 0; word[i]; i++) {
                if (word[i] == letter[0]) {
                    tempWord[i] = word[i];
                    letterMatch = true;
                } else if (i == strlen(word) - 1 && !letterMatch) {
                    numberOfParts++;
                }
            }
            if (strcmp(word, tempWord) == 0) {
                printf("You win!\n");
                break;
            }
        } 
        printf("Play again(y,n)> ");
        char terminate[MAX_WORDS] = "";
        scanf("%s", terminate);
        if ((terminate[0] != 'y' && terminate[0] != 'Y') || terminate[0] == EOF) {
            return EXIT_SUCCESS;
        }
        printf("\n");            
    }
    return EXIT_SUCCESS;
}

