#include <stdio.h>
#include <stdlib.h>

/*
 * Prints the binary versions of the integers inputed by the user
 * Also calculates the hamming distance between the binary versions of the integers
 * Usage: ./lab02.out 5 8
 */

int main(int argc, char * argv[]){

  int status = 0;
  if(argc >= 3){
    
    int x = atol(argv[1]);
    int y = atol(argv[2]);
    int remainder_x = 0;
    int remainder_y = 0;
    int bitIndex_X = 0;
    int bitIndex_Y = 0;
    int bit_x[64] = {0};
    int bit_y[64] = {0};
    int quotient_x = x;
    int quotient_y = y;

    // Calculates binary form of the first int 
    while(quotient_x > 0){
      remainder_x = quotient_x % 2;
      quotient_x = quotient_x/2;
      bit_x[bitIndex_X] = remainder_x;
      bitIndex_X++;
    }

    // Calculates binary form of the second int 
    while(quotient_y > 0){
      remainder_y = quotient_y % 2;
      quotient_y = quotient_y/2;
      bit_y[bitIndex_Y] = remainder_y;
      bitIndex_Y++; 
    }

    // Used for when input is 0
    if(x == 0){
      bit_x[0] = 0;
      bitIndex_X += 1;
    }

    // Used for when input is 0
    if(y == 0){
      bit_y[0] = 0;
      bitIndex_Y += 1;
    }
    
    // Adds 0's to first int when it's length is shorter than the 2nd int
    if(bitIndex_X < bitIndex_Y){
      int length = bitIndex_Y - bitIndex_X;
      for(int i = 0; i < length; i++){
        printf("%d", 0);
      }
      
    }

    // Prints first int's bits in reverse order
    for(int i = bitIndex_X - 1; i >= 0; i--){
      printf("%d", bit_x[i]);
      }
  
    printf(" is the bit string for ");
    printf("%d", x);
    printf(".\n");

    // Adds 0's to end when the 2nd int's length is less than the first int's length 
    if(bitIndex_Y < bitIndex_X){
      int length_y = bitIndex_X - bitIndex_Y;
      for(int i = 0; i < length_y; i++){
        printf("%d", 0);
      }
    }

    // Prints second integer's bits in reverse order
    for(int i = bitIndex_Y - 1; i >= 0; i--){
      printf("%d", bit_y[i]);
    }

    printf(" is the bit string for ");
    printf("%d", y); 
    printf(".");

    int dist = 0;

    // Calculates hamming distance by looping through both arrays 
    for(int i = 0; i < 64; i++){
      if(bit_x[i] != bit_y[i]){
      dist++;
      }
    }

    printf("\n");
    printf("%d", dist);
    printf(" is the hamming distance between the bit strings.");
    
  } 
  else{
    printf("Error: This program requires 3 command line args\n");
    status = 1;
  } 

  return status;
}
