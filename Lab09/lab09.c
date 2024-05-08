#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
/* Takes in flags -f and -d. If user inputs -f, program prints out 32 bit IEEE 754 encoding using >> bitwise operator. 
 * If user inputs -d, program prints out 64 bit IEEE 754 encoding using >> bitwise operator. Also, prints out sign bit
 * , exponenet, and fraction for both.
 */

//Stores float and int in same block of memory
union mix_f {
  float f;
  int i; 

} mix;

// Stores double and long in same block of memory
union mix_d{
  double d;
  long l; 

}mix_2;

  int main(int argc, char * argv[]){

    // Checks if -f was inputted by user 
    if(strcmp(argv[1], "-f") == 0){ 
    
      mix.f = atof(argv[2]);

      printf("%.6f encoded in binary using a 32 bit IEEE 754 encoding is below.\n", mix.f);

      int bit[32] = {0};
      int bitIndex = 0;

      // Uses bitwise operator >> to store the binary version of the float into an array
      while(bitIndex < 32){

        if(mix.i % 2 == 0){
          bit[bitIndex] = 0;
        }

        if(mix.i % 2 != 0){
          bit[bitIndex] = 1;
        }

        bitIndex++; 
      
        mix.i = mix.i >> 1; 
       }

      // Prints out floating point in binary
      for(int i = 31; i >= 0; i--){
        printf("%d", bit[i]);
       }

      printf("\nsign bit:          %d\n", bit[31]);

      printf("exponent (8 bit):  ");
      
      // Prints out Exponent
      for(int i = 30; i > 22; i--){
        printf("%d",bit[i]); 
      }

      printf("\n");

      printf("fraction (23 bit): ");
      
      // Prints out fraction
      for(int i = 22; i >= 0; i--){
        printf("%d", bit[i]);
      }
      
    }

    // Checks if -d inputted by user
    if(strcmp(argv[1], "-d") == 0){ 
    
      mix_2.d = atof(argv[2]);

      printf("%.6f encoded in binary using a 64 bit IEEE 754 encoding is below.\n", mix_2.d);

      int bit[64] = {0};
      int bitIndex = 0;

      // Uses bitwise operator >> to store binary version of double into an array
      while(bitIndex < 64){

        if(mix_2.l % 2 == 0){
          bit[bitIndex] = 0;
        }

        if(mix_2.l % 2 != 0){
          bit[bitIndex] = 1;
        }

        bitIndex++; 
      
        mix_2.l = mix_2.l >> 1; 
       }

      // Prints binary version of double
      for(int i = 63; i >= 0; i--){
        printf("%d", bit[i]);
       }

      printf("\nsign bit:          %d\n", bit[63]);

      printf("exponent (11 bit): ");
      
      // Prints exponent
      for(int i = 62; i > 51; i--){
        printf("%d",bit[i]); 
      }

      printf("\n");

      printf("fraction (52 bit): ");

      // Prints fraction
      for(int i = 51; i >= 0; i--){
        printf("%d",bit[i]);
      }
      
    }
  
    printf("\n\n");
    
    return 0; 
  }
