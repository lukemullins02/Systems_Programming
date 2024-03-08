#ifndef COMPRESS_H
#define COMPRESS_H
/* function compress takes arguments (int, char*). Converts a DNA string of length 4
 * compsed of the letters (A,T,C,G) into a binary string of length 8 and then converts
 * the binary string to base 10. If the string is less than length 8 the end is padded 
 * with 0's. 
 * Usage: ./proj1.out -c ATTCGG
 */
void compress(int a, char** b); 
#endif
