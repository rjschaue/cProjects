/**
    @file codes.c
    @author Joey Schauer (rjschaue)

    This program will take the contents of a code file, store them, and has
    functions to convert them between symbols and binary codes to represent
    the symbols
*/ 

#include "codes.h"

List *list = NULL;

void populateList(char const *filename ) 
{
  FILE *stream = fopen( filename, "r" );

  if (!stream) {
      perror(filename);
      exit(EXIT_FAILURE);
  }  
  
  char symbol[STRING_BUFFER] = "";
  char binary[STRING_BUFFER] = ""; 
   
  while (fscanf(stream, "%19s%19s", symbol, binary) == 2) {
      
      if ((symbol[0] < 'a' || symbol[0] > 'z') && strcmp(symbol, "space") != 0
          && strcmp(symbol, "newline") != 0 && strcmp(symbol, "eof") != 0) {
          fprintf(stderr, "Invalid code file\n");
          freeList(list);
          fclose(stream);
          exit(EXIT_FAILURE);
      }

      if (strlen(binary) < 1 || strlen(binary) > 12) {
          fprintf(stderr, "Invalid code file\n");
          freeList(list);
          fclose(stream);
          exit(EXIT_FAILURE);
      }
      
      for (int i = 0; binary[i]; i++) {
          if (binary[i] != '1' && binary[i] != '0') {
              fprintf(stderr, "Invalid code file\n");
              freeList(list);
              fclose(stream);
              exit(EXIT_FAILURE);
          }
      }

      Node *n = (Node *)malloc(sizeof(Node));
      if (strcmp(symbol, "space") == 0) {
          n->symbol = ' ';
      } else if (strcmp(symbol, "newline") == 0) {
          n->symbol = '\n';
      } else if (strcmp(symbol, "eof") == 0) {
          n->symbol = 'E';
      } else {
          n->symbol = symbol[0];
      }

      strcpy(n->binary, binary);

      n->next = list->head;
      list->head = n;
  }
}

void freeList() 
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
    for (Node *n = list->head; n; n = n->next ) {
        if (ch == n->symbol) {
            return n->binary;
        }
    }
    return NULL; 
}

int codeToSym( const char *code ) 
{
    for (Node *n = list->head; n; n = n->next ) {
        if (strcmp(code, n->binary) == 0) {
            if (n->symbol == 'E') {
                return -1;
            } else {
                return n->symbol;
            }
        }
    }
    return -2;
}
