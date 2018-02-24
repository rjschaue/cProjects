/**
    @file wordlist.h
    @author Joey Schauer (rjschaue)
    
    Contains the protoypes for the wordlist functions
*/

/** global variable that gets a list of words up to 20 characters in length */
extern char words[20][50];

/** global variable that counts the number of words in the above list */
extern int wordCount;

/**
    Reads the words in the file and stores them into the words array

    @param filename is the name of the file to read
*/
void readWords( char const *filename );
