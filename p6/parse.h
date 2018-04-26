/**
    @file parse.h
    @author Joey Schauer

    This is the header for parse.c
*/

#ifndef PARSE_H
#define PARSE_H

#include "pattern.h"

/** Parse the given string into Pattern object.

    @param str string cntaining a pattern.
    @return pointer to a representation of the pattern.
***/
Pattern *parsePattern( char const *str );

#endif
