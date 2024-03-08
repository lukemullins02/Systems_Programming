#ifndef DECOMPRESS_H
#define DECOMPRESS_H
/* User provides length desired of DNA string. Program converts the following numbers to a DNA string.
 * Does this by first converting the numbers to binary than comparing the binary string with DNA Strings 
 * binary encodings.
 * Usage: ./proj1.out -d 6 22 240
 */
void decompress(int a, char** b);
#endif
