/**
    @file bits.c
    @author Joey Schauer (rjschaue)
    
    This program has functions for writing out bit sequences to and from a file
*/

#include "bits.h"

void writeBits( const char *code, BitBuffer *buffer, FILE *fp)
{
    for (int i = 0; code[i]; i++) {
        if (buffer->bcount == BITS_PER_BYTE) {
            fwrite(&(buffer->bits), 1, 1, fp);
            buffer->bits = 0x00;
            buffer->bcount = 0;
        }

        char mask = 0x80;

        if (code[i] == 1) {
            mask = mask >> buffer->bcount;
            buffer->bits = buffer->bits | mask;
            buffer->bcount++;
        }
    }
}

void flushBits( BitBuffer *buffer, FILE *fp )
{
    fwrite(&(buffer->bits), 1, 1, fp);
}

int readBit( BitBuffer *buffer, FILE *fp )
{
    char mask = 0x80;

    if (buffer->bcount == 0) {
        if (fread(&(buffer->bits), 1, 1, fp) == 0) {
            return -1;
        }
        buffer->bcount++;
        if ((buffer->bits | mask) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    
    mask = mask >> buffer->bcount;
    if (buffer->bcount == BITS_PER_BYTE) {
        buffer->bcount = 0;
    } else {
        buffer->bcount++;
    }

    if ((buffer->bits | mask) == 0) {
        return 0;
    } else {
        return 1;
    }

}
