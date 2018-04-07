/**
    @file codes.c
    @author Joey Schauer (rjschaue)

    This program will take the contents of a code file, store them, and has
    functions to convert them between symbols and binary codes to represent
    the symbols
*/ 

#include "codes.h"

void populateList( List *list, FILE *fp ) 
{
    
}

void freeList( List *list ) 
{
   Node *n = list->head;
   while(n) {
       Node *next = n->next;
       free(n);
       n = next;
   }
}

const char * symToCode( int ch ) 
{

}

int codeToSym( const char *code ) 
{

}
