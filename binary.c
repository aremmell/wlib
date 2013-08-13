#include "binary.h"

unsigned long bittable[] = {
	0x00000001L,
	0x00000002L,
	0x00000004L,
	0x00000008L,
	0x00000010L,
	0x00000020L,
	0x00000040L,
	0x00000080L,
	0x00000100L,
	0x00000200L,
	0x00000400L,
	0x00000800L,
	0x00001000L,
	0x00002000L,
	0x00004000L,
	0x00008000L,
	0x00010000L,
	0x00020000L,
	0x00040000L,
	0x00080000L,
	0x00100000L,
	0x00200000L,
	0x00400000L,
	0x00800000L,
	0x01000000L,
	0x02000000L,
	0x04000000L,
	0x08000000L,
	0x10000000L,
	0x20000000L,
	0x40000000L,
	0x80000000L 
};

/*
 * FUNCTION: ByteToBinaryStr()
 *
 * SYNOPSIS: Takes an unsigned byte value,
 * and returns its binary string equivalent (e.g. '10101011')
 *
 * ARGUMENTS: Unsigned byte value to convert, and a pointer
 * to a buffer large enough to hold B_BYTEBITS characters plus a null-
 * terminator.
 *
 * RETURN VALUE: Returns 0 if successful, or 1 otherwise.
 *
 */
int ByteToBinaryStr(unsigned char bits, char *out) {
	
  int r = 1;

  if (NULL != out) {

	  r = _copybits(bits, out, B_BYTEBITS);

  }

  return r;
}

/*
 * FUNCTION: ShortToBinaryStr()
 *
 * SYNOPSIS: Takes an unsigned short value,
 * and returns its binary string equivalent (e.g. '0100101010101011')
 *
 * ARGUMENTS: Unsigned short value to convert, and a pointer
 * to a buffer large enough to hold B_SHORTBITS characters plus a null-
 * terminator.
 *
 * RETURN VALUE: Returns 0 if successful, or 1 otherwise.
 *
 */
int ShortToBinaryStr(unsigned short bits, char *out) {

	int r = 1;

  if (NULL != out) {

	  r = _copybits(bits, out, B_SHORTBITS);

  }

  return r;
}

/*
 * FUNCTION: IntToBinaryStr()
 *
 * SYNOPSIS: Takes an unsigned integer value,
 * and returns its binary string equivalent
 * (e.g. '01001010101010110100101010101011')
 *
 * ARGUMENTS: Unsigned integer value to convert, and a pointer
 * to a buffer large enough to hold B_INTBITS characters plus a null-
 * terminator.
 *
 * RETURN VALUE: Returns 0 if successful, or 1 otherwise.
 *
 */
int IntToBinaryStr(unsigned int bits, char *out) {

	int r = 1;

  if (NULL != out) {

	  r = _copybits(bits, out, B_INTBITS);

  }

  return r;
}

/*
 * FUNCTION: LongToBinaryStr()
 *
 * SYNOPSIS: Takes an unsigned long value,
 * and returns its binary string equivalent
 * (e.g. '01001010101010110100101010101011')
 *
 * ARGUMENTS: Unsigned long value to convert, and a pointer
 * to a buffer large enough to hold B_LONGBITS characters plus a null-
 * terminator.
 *
 * RETURN VALUE: Returns 0 if successful, or 1 otherwise.
 *
 */
int LongToBinaryStr(unsigned long bits, char *out) {

	int r = 1;

  if (NULL != out) {

	  r = _copybits(bits, out, B_LONGBITS);

  }

  return r;
}

/*
 * FUNCTION: BinaryPrintByte()
 *
 * SYNOPSIS: Prints a numeric byte value
 * to a stream as binary (e.g. '10110010')
 *
 * ARGUMENTS: The stream to output the binary to,
 * and the numeric value to output.
 *
 * NOTE: If stream is NULL, stdout will be used.
 *
 * RETURN VALUE: returns 0 if successful, or 1 otherwise.
 *
 */
int BinaryPrintByte(FILE *stream, unsigned char bits) {

  return _printbits(stream, bits, B_BYTEBITS);
}

/*
 * FUNCTION: BinaryPrintShort()
 *
 * SYNOPSIS: Prints a numeric short value
 * to a stream as binary (e.g. '1011001010001110')
 *
 * ARGUMENTS: The stream to output the binary to,
 * and the numeric value to output.
 *
 * NOTE: If stream is NULL, stdout will be used.
 *
 * RETURN VALUE: returns 0 if successful, or 1 otherwise.
 *
 */
int BinaryPrintShort(FILE *stream, unsigned short bits) {

  return _printbits(stream, bits, B_SHORTBITS);
}

/*
 * FUNCTION: BinaryPrintInt()
 *
 * SYNOPSIS: Prints a numeric integer value
 * to a stream as binary
 * (e.g. '10110010100011100101001010010101')
 *
 * ARGUMENTS: The stream to output the binary to,
 * and the numeric value to output.
 *
 * NOTE: If stream is NULL, stdout will be used.
 *
 * RETURN VALUE: returns 0 if successful, or 1 otherwise.
 *
 */
int BinaryPrintInt(FILE *stream, unsigned int bits) {

  return _printbits(stream, bits, B_INTBITS);
}

/*
 * FUNCTION: BinaryPrintLong()
 *
 * SYNOPSIS: Prints a numeric integer value
 * to a stream as binary
 * (e.g. '10110010100011100101001010010101')
 *
 * ARGUMENTS: The stream to output the binary to,
 * and the numeric value to output.
 *
 * NOTE: If stream is NULL, stdout will be used.
 *
 * RETURN VALUE: returns 0 if successful, or 1 otherwise.
 *
 */
int BinaryPrintLong(FILE *stream, unsigned long bits) {

  return _printbits(stream, bits, B_LONGBITS);
}

unsigned char BinaryStrToByte(char *binary) {

  unsigned char r = 0U;

  if (NULL != binary) {

    r = (unsigned char)_string2numeric(binary, B_BYTEBITS);

  }

  return r;
}

unsigned short BinaryStrToShort(char *binary) {

  unsigned short r = 0U;

  if (NULL != binary) {

    r = (unsigned short)_string2numeric(binary, B_SHORTBITS);

  }

  return r;
}

unsigned int BinaryStrToInt(char *binary) {

  unsigned int r = 0U;

  if (NULL != binary) {

    r = (unsigned int)_string2numeric(binary, B_INTBITS);

  }

  return r;
}

unsigned long BinaryStrToLong(char *binary) {

  unsigned long r = 0U;

  if (NULL != binary) {

    r = _string2numeric(binary, B_LONGBITS);

  }

  return r;
}


/* ------------------------------------------
 *
 * Internal functions;
 * don't touch these, bitches!
 *
 * ------------------------------------------
 */


int _copybits(unsigned long bits, char *out, unsigned int depth) {

	int n = 0;

  if (0U < depth) {

	  for (n = depth; n > 0; n--) {

		  if (bits & bittable[n-1]) {
        strcat(out, "1");
      } else {
        strcat(out, "0");
      }

	  }

    return 0;
  }

	return 1;
}

int _printbits(FILE *f, unsigned long bits, unsigned int depth) {

  int r        = 1;
	char out[33] = {0};

  f = (NULL == f) ? stdout : f;

  if (0 == _copybits(bits, out, depth)) {

    if (0 > fprintf(f, "%s", out)) {

      r = 0;

    }

  }

	return r;
}

unsigned long _string2numeric(char *binary, int depth) {

	int n             = 0;
	unsigned long  r  = 0;

	for (n = 0; n < depth; n++) {

		if (binary[n - 1] == '1') { r |= bittable[depth - n]; }

	}

	return r;
}