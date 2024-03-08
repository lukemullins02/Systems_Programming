#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* Takes in flags -decimal, -bits, and -binary. -decimal and -bits must be used together. -decimal
 * takes in a decimal number that you want to convert to binary and -bits provides the length of the
 * binary string. -binary converts a binary number to a signed decimal number. So it could end up 
 * being negative. Also, at the end of both it prints out the length of bits used.  
 */
int main(int argc, char * argv[]){

   signed int x = 0;
   int y = 0;
   unsigned long int quotient;
   int remainder = 0;
   int bit[64] = {0};
   int bitIndex = 0; 
   signed long int answer = 0;
   signed long int decimal = 1;

   if(((strcmp(argv[1],"-decimal") == 0) && (strcmp(argv[3], "-bits") == 0)) | ((strcmp(argv[1], "-bits") == 0) && (strcmp(argv[3], "-decimal") == 0))){
   // Checks if negative number inputted by user
    if((argv[2][0] == '-') | (argv[4][0] == '-')){    
  
      // Makes sure negatives bits won't be printed 
     if(((strcmp(argv[1], "-bits") == 0) && (argv[2][0] == '-')) | ((strcmp(argv[3], "-bits") == 0) && (argv[4][0] == '-'))){
          printf("bits can't be negative.");
     }
    else{
     // Checks where negative number is located and assigns x and y accordingly
     if(argv[2][0] == '-'){ 
        y = atoi(argv[4]);
	x = atoi(argv[2]);
      }
     else if (argv[4][0] == '-'){
       y = atoi(argv[2]);
       x = atoi(argv[4]);
      }


      quotient = ~x + 1;

      // Converts Integer inputed by user after decimal into binary in an array
      while(quotient > 0){
        remainder = quotient % 2;
	quotient = quotient/2;
	bit[bitIndex] = remainder;
	bitIndex++;
      }

      // Simulates not operator on binary version of integer  
      for(int i=0; i < y; i++){
        if(bit[i] == 0){
          bit[i] = 1;
	}
	else if(bit[i] == 1){
          bit[i] = 0;
	 }
       } 

      // Converts not version to decimal
      for(int i = 0; i < y; i++){
        if(bit[i] == 1){
          answer = answer + decimal;
	  decimal = decimal * 2;
	 }
	else if(bit[i] == 0){
          decimal = decimal * 2;
	 }
       }

      quotient = answer + 1;
      remainder = 0; 
      int bit2[64] = {0};
      bitIndex = 0;
       
      // Converts not version + 1 to binary
      while(quotient > 0){
        remainder = quotient % 2;
	quotient = quotient/2;
	bit2[bitIndex] = remainder;
	bitIndex++;
      }

      printf("%d in decimal is equal to ", x);

      // Prints binary version of original integer
      for(int i = y-1; i >= 0; i--){
        printf("%d", bit2[i]);
      }
     
      printf(" in binary using %d-bit two's complement representation",y);
     }  
     }
   // Checks where flag -decimal and -bits are located  
   else if((argv[2][0] != '-') && (argv[4][0] != '-')){
 
     // chekcs where -decimal and -bits is and assigns x and y accordingly
     if((strcmp(argv[1], "-decimal") == 0) && (strcmp(argv[3], "-bits") == 0)){
  	 x = atoi(argv[2]);
	 y = atoi(argv[4]);
       } 
     else if((strcmp(argv[1],"-bits") == 0) && (strcmp(argv[3], "-decimal") == 0)){
	 x = atoi(argv[4]);
	 y = atoi(argv[2]);
       }

      
     quotient = x;

     // converts integer after -decimal to binary
     while(quotient > 0){
       remainder = quotient % 2;
       quotient = quotient/2;
       bit[bitIndex] = remainder;
       bitIndex++;
     }

    int len_x = y - bitIndex;

    printf("%d in decimal is equal to ", x);

    // Adds 0 accordingly to length of bits specified by user
    for(int i = 0; i < len_x; i++){
      printf("0"); 
    } 

    // Prints out binary version of the integer after -decimal
    for(int i = bitIndex-1; i  >= 0; i--){
      printf("%d", bit[i]);
    } 	 

    printf(" in binary using %d-bit two's complement representation", y);
     
   }
   }
   // Checks if -binary flag is inputed by user 	 
 else if(strcmp(argv[1], "-binary") == 0){

   int len_x = strlen(argv[2]);
    
   quotient = atol(argv[2]);

   // Stores number after -binary into array
   while(quotient > 0){
     remainder = quotient % 10;
     quotient = quotient/10;
     bit[bitIndex] = remainder;
     bitIndex++;  
   }

   printf("%s in binary is equal to ", argv[2]);

   // Goes through array and converts number after -binary into base 10
   for(int i = 0; i < len_x; i++){
     if(bit[i] == 1 && (i != len_x - 1)){
       answer = answer + decimal;
       decimal = decimal * 2;
     }
     else if(bit[i] == 0){
       decimal = decimal * 2;
     }
     else if(bit[i] == 1 && (i = len_x - 1)){
       answer = answer - decimal;
       } 
     else if(bit[i] == 1 && (len_x = 1)){
       answer = 0 - 1; 
     }
   }
     
  printf("%ld in decimal using %d-bit two's complement representation.", answer, len_x);

   
   

 } 
    
     
   printf("\n\n");

} // Main 
