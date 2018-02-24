/**
    @file display.h
    @author Joey Schauer (rjschaue)
    
    Contains prototype functions for displaying hangman word and figure
*/

/**
    Displays the hangman word or underscores if letter not found

    @param word is the word to be output
*/
void displayword( char word[] );

/**
    Displays the hangman figure as user incorrectly guesses letters

    @param numberOfParts is the number of parts to output
*/
void displayFigure( int numberOfParts );
