/**
    @file codes.h
    @author Joey Schauer (rjschaue)

    This header contains a data structure to store codes as well as functions to
    read codes from a file, convert ASCII code for symbols to a string
    representation of it and vice versa.
*/

#ifndef _CODES_H_
#define _CODES_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
   The struct to represent a Node that contains a symbol and it's binary
   representation.
*/  
typedef struct NodeTag {
    /** A string representing the symbol */ 
    char *symbol;
    /** A string representing the binary version of the symbol */
    char *binary;
    /** The next node in the sequence */
    struct NodeTag *next;
} Node;

/**
    A struct used to represent a list of nodes
*/
typedef struct {
    /** The head node of the linked list */
    Node *head;
} List;

/**
    Function used to take the contents of a code file and store them in
    a list of nodes

    @param list is the list to store codes to
    @param fp is a pointer to the file to get codes from
*/
void populateList( List *list, FILE *fp );

/**
    Function used to free memory from the dynamically allocated list
    
    @param list is the list to free memory for
*/
void freeList( List *list );

/**
    This function returns a string containing the code used to represent the
    given ASCII code for a symbol or EOF.

    @param ch is the given ASCII code
    @return a string containing a representation of the given ASCII code
*/
const char * symToCode( int ch );

/**
    This function returns the ASCII character (or EOF) represented by the
    given string containing a code.

    @param code is the string containing a code
    @return the ASCII character (or EOF) represented by the given code
*/
int codeToSym( const char *code );

#endif
