#ifndef _BINARY_H_INCLUDED
#define _BINARY_H_INCLUDED

#include <stdio.h>
#include <string.h>

/*
 * Constants
 */
#define B_BYTEBITS       8
#define B_SHORTBITS     16
#define B_INTBITS       32
#define B_LONGBITS      32

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Conversion of numeric to binary string
 */
int ByteToBinaryStr(unsigned char bits, char *out);
int ShortToBinaryStr(unsigned short bits, char *out);
int IntToBinaryStr(unsigned int bits, char *out);
int LongToBinaryStr(unsigned long bits, char *out);

/*
 * Conversion and printing of numeric to binary string
 */
int BinaryPrintByte(FILE *stream, unsigned char bits);
int BinaryPrintShort(FILE *stream, unsigned short bits);
int BinaryPrintInt(FILE *stream, unsigned int bits);
int BinaryPrintLong(FILE *stream, unsigned long bits);

/*
 * Conversion of binary string to numeric
 */
unsigned char BinaryStrToByte(char *binary);
unsigned short BinaryStrToShort(char *binary);
unsigned int BinaryStrToInt(char *binary);
unsigned long BinaryStrToLong(char *binary);

/*
 * Internally used functions.
 */
int _copybits(unsigned long bits, char *out, unsigned int depth);
int _printbits(FILE *f, unsigned long bits, unsigned int depth);
unsigned long _string2numeric(char *binary, int depth);

#ifdef __cplusplus
}
#endif

#endif /* _BINARY_H_INCLUDED */
