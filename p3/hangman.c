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
    //Error testing for incorrect number of command line arguments
    if (argc < 2) {
        fprintf(stderr, "usage: hangman <word-file> [seed]\n");
        return EXIT_FAILURE;
    } else if (argc > 2 && atoi(argv[2]) < 0) {
        fprintf(stderr, "usage: hangman <word-file> [seed]\n");
        return EXIT_FAILURE;
    }
    
    //Adds words from file to global word list 
    readWords( argv[1] );

    //Seeds the randomizer 
    int seed = 0;
    if (argc > 2) {
        seed = atoi(argv[2]);
    }

    if (seed > 0) {
        srand(seed);
    } else {
        srand(time(NULL));
    }
    
    printf("\n");
    //Outer while loop to initialize hangman word and letter array
    while (true) {
        //Chooses word for hangman game
        int index = rand() % wordCount;
        
        char word[WORD_LENGTH_MAX];
        strcpy(word,  words[index]);

        //Initializes the array of possible letters to choose from
        int letterLength = NUMBER_OF_LETTERS;
        char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                          'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                          'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                          'y', 'z'};
        
        //Creates a temporary word to be filled in as letters are guessed
        int wordLength = strlen(word + 1);
        char tempWord[wordLength];
        strcpy(tempWord, word);
        for (int i = 0; tempWord[i]; i++) {
            tempWord[i] = '_';
        }

        int numberOfParts = 0;
        
        //Loop for the hangman parts, printing letters and user success/failure
        while (true) {
            //Prints hangman figure and outputs if user fails
            displayFigure(numberOfParts);            
            if (numberOfParts == MAX_PARTS) {
                printf("You lose!\n");
                printf("Word was %s\n\n", word);
                break;
            }
            //Prints word with correct guesses
            displayWord(tempWord);
            printf("\n");

            //Prints remaining letters to choose from
            printf("Remaining letters: ");
            for (int i = 0; i < letterLength; i++) {
                printf("%c", letters[i]);
                if (i < letterLength - 1) {
                    printf(" ");
                }
            }
            printf("\n\n");
            
            char letter[MAX_WORDS] = "";
            bool letterFound = false;
            
            //Checks user input for letter guesses
            while (true) {
                //Prompts user for guess and exits if EOF
                printf("letter> ");
                if (scanf("%s", letter) == EOF) {
                    return EXIT_SUCCESS;
                }
                printf("\n");
                
                //Checks for invalid input
                if (strlen(letter) > 1) {
                    printf("Invalid letter\n\n");
                } else {
                    //Checks to see if letter is valid
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
                    //Breaks loop if a valid letter is found
                    if (letterFound) {
                        break;
                    } else {
                        printf("Invalid letter\n\n");
                    }
                }
            }
            //Checks word against chosen letter to see if it is correct
            bool letterMatch = false;
            for (int i = 0; word[i]; i++) {
                if (word[i] == letter[0]) {
                    tempWord[i] = word[i];
                    letterMatch = true;
                } else if (i == strlen(word) - 1 && !letterMatch) {
                    numberOfParts++;
                }
            }
            //Tells user they win if word is completed
            if (strcmp(word, tempWord) == 0) {
                displayWord(word);
                printf("\n");
                printf("You win!\n\n");
                break;
            }
        } 
        //Prompts user if they want to play again, exiting for anything other
        //than a 'y' or 'Y'
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
