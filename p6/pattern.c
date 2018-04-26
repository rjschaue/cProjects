/**
    @file pattern.c
    @author Joey Schauer (rjschaue)

    This program has multiple different types of patterns to be used to
    create a binary tree representing a given pattern. Functions within will
    then be used to compare patterns against given strings.
*/

#include "pattern.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** A buffer for any strings */
#define STRING_BUFFER 100
/** 
    Free the table inside a pattern, if there is one.

    @param this The pattern we're supposed to operate on.
*/
static void freeTable( Pattern *this )
{
  if ( this->table ) {
    for ( int r = 0; r <= this->len; r++ )
      free( this->table[ r ] );
    free( this->table );
  }
}

/** 
    Make and initialize a new match table inside the given pattern,
    large enough to store matches for the given string.

    @param this The pattern we're supposed to operate on.
    @param str The string we're going to store mageches for 
*/
static void initTable( Pattern *this, char const *str )
{
  // If we already had a table, free it.
  freeTable( this );

  // Make a table big enough for str.
  this->len = strlen( str );
  this->table = (bool **) malloc( ( this->len + 1 ) * sizeof( bool * ) );
  for ( int r = 0; r <= this->len; r++ )
    this->table[ r ] = (bool *) calloc( ( this->len + 1 ), sizeof( bool ) );
}

// Documented in the header.
bool matches( Pattern *pat, int begin, int end )
{
  return pat->table[ begin ][ end ];
}

/**
   A simple function that can be used to free the memory for any
   pattern that doesn't allocate any additional memory other than the
   struct used to represent it (e.g., if it doesn't contain any
   sub-patterns).  It's like a default implementation of the destroy
   method.

   @param pat The pattern to free memory for.
*/
static void destroySimplePattern( Pattern *pat )
{
  freeTable( pat );
  // If we don't need fields that are specific to the sub-type, we can just
  // free the block of memory where the object is stored.
  free( pat );
}

/**
   Type of pattern used to represent a single, ordinary symbol,
   like 'a' or '5'. 
*/
typedef struct {
  // Fields from our superclass.
  int len;
  bool **table;
  void (*locate)( Pattern *pat, char const *str );
  void (*destroy)( Pattern *pat );
  
  /** Symbol this pattern is supposed to match. */
  char sym;
} SymbolPattern;


// Overridden locate() method for a SymbolPattern
static void locateSymbolPattern( Pattern *pat, char const *str )
{
  // Cast down to the struct type pat really points to.
  SymbolPattern *this = (SymbolPattern *) pat;

  // Make a fresh table for this input string.
  initTable( pat, str );

  // Find all occurreces of the symbol we're supposed to match, and
  // mark them in the match table as matching, 1-character substrings.
  for ( int begin = 0; str[ begin ]; begin++ )
    if ( str[ begin ] == this->sym )
      this->table[ begin ][ begin + 1 ] = true;
}

// Documented in the header.
Pattern *makeSymbolPattern( char sym )
{
  // Make an instance of SymbolPattern, and fill in its state.
  SymbolPattern *this = (SymbolPattern *) malloc( sizeof( SymbolPattern ) );
  this->table = NULL;
  
  this->locate = locateSymbolPattern;
  this->destroy = destroySimplePattern;
  this->sym = sym;

  return (Pattern *) this;
}

// Overridden locate() method for a DotPattern
static void locateDotPattern( Pattern *pat, char const *str )
{
  //Cast down to the struct type pat really points to.
  SymbolPattern *this = (SymbolPattern *) pat;

  //Make a fresh table for this input string
  initTable( pat, str );

  //Set all single symbol occurrences to true
  for (int begin = 0; str[begin]; begin++) {
    
    this->table[begin][begin + 1] = true;
    
  }
}

//Documented in the header.
Pattern *makeDotPattern( char sym )
{ 
  // Make an instance of the pattern and fill in the states
  SymbolPattern *this = (SymbolPattern *) malloc( sizeof( SymbolPattern ) );
  this->table = NULL;

  this->locate = locateDotPattern;
  this->destroy = destroySimplePattern;
  this->sym = sym;

  return (Pattern *) this;
}

// Overridden locate() method for an AnchorPattern
static void locateAnchorPattern( Pattern *pat, char const *str )
{ 
   //Cast down to the struct type pat really points to.
  SymbolPattern *this = (SymbolPattern *) pat;
  
  //Make a fresh table for this input string.
  initTable( pat, str );

  //If start anchor, set first slot in table to true, if end, set the last
  if (this->sym == '^') {
    this->table[0][0] = true;
  } else {
    this->table[this->len][this->len] = true;
  }
}

//Documented in the header.
Pattern *makeAnchorPattern( char sym )
{
  //Make an instance of the pattern and fill in the states
  SymbolPattern *this = (SymbolPattern *) malloc( sizeof( SymbolPattern ) );
  this->table = NULL;

  this->locate = locateAnchorPattern;
  this->destroy = destroySimplePattern;
  this->sym = sym;

  return (Pattern *) this;
}

/**
   Representation for a type of pattern that contains two sub-patterns
   (e.g., concatenation).  This representation could be used by more
   than one type of pattern, as long as it uses a pointer to a
   different locate() function.
*/
typedef struct {
  // Fields from our superclass.
  int len;
  bool **table;
  void (*locate)( Pattern *pat, char const *str );
  void (*destroy)( Pattern *pat );
  
  // Pointers to the two sub-patterns.
  Pattern *p1, *p2;
} BinaryPattern;

// destroy function used for BinaryPattern
static void destroyBinaryPattern( Pattern *pat )
{
  // Cast down to the struct type pat really points to.
  BinaryPattern *this = (BinaryPattern *) pat;

  // Free our table.
  freeTable( pat );
  // Free our two sub-patterns.
  this->p1->destroy( this->p1 );
  this->p2->destroy( this->p2 );
  // Free the struct representing this object.
  free( this );
}

// locate function for a BinaryPattern used to handle concatenation.
static void locateConcatenationPattern( Pattern *pat, const char *str )
{
  // Cast down to the struct type pat really points to.
  BinaryPattern *this = (BinaryPattern *) pat;

  initTable( pat, str );

  // Let our two sub-patterns figure out everywhere they match.
  this->p1->locate( this->p1, str );
  this->p2->locate( this->p2, str );

  // Then, based on their matches, look for all places where their
  // concatenaton matches.  Check all substrings of the input string.
  for ( int begin = 0; begin <= this->len; begin++ )
    for ( int end = begin; end <= this->len; end++ ) {
      
      // For the [ begin, end ) range, check all places where it could
      // be split into two substrings, the first matching p1 and the second
      // matching p2.
      for ( int k = begin; k <= end; k++ )
        if ( matches( this->p1, begin, k ) &&
             matches( this->p2, k, end ) )
          this->table[ begin ][ end ] = true;
    }
}

// Documented in header.
Pattern *makeConcatenationPattern( Pattern *p1, Pattern *p2 )
{
  // Make an instance of Binary pattern and fill in its fields.
  BinaryPattern *this = (BinaryPattern *) malloc( sizeof( BinaryPattern ) );
  this->table = NULL;
  this->p1 = p1;
  this->p2 = p2;
  
  this->locate = locateConcatenationPattern;
  this->destroy = destroyBinaryPattern;
  
  return (Pattern *) this;
}

// locate function for a BinaryPattern used to handle alternation.
static void locateAlternationPattern( Pattern *pat, const char *str )
{
  // Cast down to the struct type pat really points to.
  BinaryPattern *this = (BinaryPattern *) pat;

  initTable( pat, str );

  //  Let our two sub-patterns figure out everywhere they match.
  this->p1->locate( this->p1, str );
  this->p2->locate( this->p2, str );

  // Then, based on their matches, look for all places where their
  // alternaton matches.  Check all substrings of the input string.
  for ( int begin = 0; begin <= this->len; begin++ )
    for ( int end = begin; end <= this->len; end++ ) {
      if (matches(this->p1, begin, end) || matches(this->p2, begin,end)) {
        this->table[begin][end] = true;
      }
    }
}

// Documented in header.
Pattern *makeAlternationPattern( Pattern *p1, Pattern *p2 )
{
  // Make an instance of Binary pattern and fill in its fields.
  BinaryPattern *this = (BinaryPattern *) malloc( sizeof( BinaryPattern ) );
  this->table = NULL;
  this->p1 = p1;
  this->p2 = p2;
  
  this->locate = locateAlternationPattern;
  this->destroy = destroyBinaryPattern;
  
  return (Pattern *) this;
}

/**
   Representation for a type of pattern that contains one sub-pattern
   (e.g., repetition).
*/
typedef struct {
  // Fields from our superclass.
  int len;
  bool **table;
  void (*locate)( Pattern *pat, char const *str );
  void (*destroy)( Pattern *pat );
  
  //The character for the type of repetition pattern (*, +, ?)
  char type;
  // Pointer to the repeating pattern.
  Pattern *p;
} RepetitionPattern;

// destroy function used for RepetitionPattern
static void destroyRepetitionPattern( Pattern *pat )
{
  // Cast down to the struct type pat really points to.
  RepetitionPattern *this = (RepetitionPattern *) pat;

  // Free our table.
  freeTable( pat );
  // Free our sub-pattern.
  this->p->destroy( this->p );
  // Free the struct representing this object.
  free( this );
}

// Locate function for RepetitionPattern to handle repetition
static void locateRepetitionPattern( Pattern *pat, const char *str ) 
{
  // Cast down to the struct type pat really points to.
  RepetitionPattern *this = (RepetitionPattern *) pat;

  initTable( pat, str );

  //  Let our sub-pattern figure out everywhere it matches.
  this->p->locate( this->p, str );

  // Check through the sub-pattern for repetition depending on the type of pattern
  bool match = false;
  int temp = 0;
  for ( int begin = 0; begin <= this->len ; begin++ ) {
    if (this->type == '*' || this->type == '?') {
      this->table[begin][begin] = true;
    }
    for ( int end = begin; end <= this->len; end++) {
      if ( matches(this->p, begin, end)) {
        this->table[ begin ][ end ] = true;
        if (this->type != '?') {
          int length = end - begin;
          for (int i = length; i < this->len - begin; i+=length) {
            if (matches(this->p, begin + i, end + i)) {
              if (match) {
                this->table[begin][end + temp] = false;
              }
              this->table[begin][end + i] = true;
              match = true;
              temp = i;
            } else {
              break;
            }
          }
        }
      }
    }
  }
}

//Documented in header.
Pattern *makeRepetitionPattern( char type, Pattern *p ) 
{
  //Make an instance of Repetition pattern and fill in its fields
  RepetitionPattern *this = (RepetitionPattern *) malloc( sizeof( RepetitionPattern ) );
  this->table = NULL;
  this->type = type;
  this->p = p;

  this->locate = locateRepetitionPattern;
  this->destroy = destroyRepetitionPattern;

  return (Pattern *) this;
}

/**
    Representation for a type of pattern that contains a string of symbols
    (e.g. brackets)
*/
typedef struct {
  // Fields from our superclass.
  int len;
  bool **table;
  void (*locate)( Pattern *pat, char const *str );
  void (*destroy)( Pattern *pat );
  
  //A string with the different symbols in the brackets
  char symbols[STRING_BUFFER];
} BracketPattern;

// destroy function used for BracketPattern
static void destroyBracketPattern( Pattern *pat )
{
  // Cast down to the struct type pat really points to.
  BracketPattern *this = (BracketPattern *) pat;

  // Free our table.
  freeTable( pat );
  // Free the struct representing this object.
  free( this );
}

// Overridden locate() method for a BracketPattern
static void locateBracketPattern( Pattern *pat, char const *str )
{
  // Cast down to the struct type pat really points to.
  BracketPattern *this = (BracketPattern *) pat;

  // Make a fresh table for this input string.
  initTable( pat, str );

  for ( int begin = 0; str[ begin ]; begin++ ) {
    if ( strchr(this->symbols, str[begin]) != NULL ) {
      this->table[ begin ][ begin + 1 ] = true;
    }
  }
}


//Documented in header.
Pattern *makeBracketPattern( char *symbols ) 
{
  //Make an instance of BracketPattern and fill in all its fields
  BracketPattern *this = (BracketPattern *) malloc( sizeof( BracketPattern ) );
  this->table = NULL;
  strcpy(this->symbols, symbols);

  this->locate = locateBracketPattern;
  this->destroy = destroyBracketPattern;

  return (Pattern *) this;
}
