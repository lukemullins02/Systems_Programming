#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Compares two binary numbers using the bitwise operators |, && , and ^. 
 * Then prints out the comparison and provides the length of the bit strings.
 * Next it converts the two initial binary and the comparison into base ten.
 * Then prints out the bit length of the unisgned integers.
 * Usage: ./lab03.out 0011 -and 1111
 * ./lab03.out 11110 -or 11
 * ./lab03.out 110110 -xor 1110 
 */

int main (int argc, char * argv[]){

    int status = 0;  
    if(argc >= 4){
      long int x = atol(argv[1]);
      long int y = atol(argv[3]);		  
      long int bitIndex_X = 0;
      long int bitIndex_Y = 0;
      int bit_x[64] = {0};
      int bit_y[64] = {0};
      long int remainder_x = 0;
      long int quotient_x = x; 
      long int remainder_y = 0;
      long int quotient_y = y;
      long int len_x = strlen(argv[1]);
      long int len_y = strlen(argv[3]);

      
      // stores first int into an array
      while(quotient_x > 0){
	remainder_x = quotient_x % 10;
	quotient_x = quotient_x/10;
        bit_x[bitIndex_X] = remainder_x;
	bitIndex_X++;
      }

      //stores secom\nd int into an array
      while(quotient_y > 0){
        remainder_y = quotient_y % 10;
	quotient_y = quotient_y/10;
	bit_y[bitIndex_Y] = remainder_y;
	bitIndex_Y++;
      }

      // Used for when input is 0
      if(x == 0){
	bit_x[0] = 0;
        }

      // Used for when input is 0
      if(y == 0){
	bit_y[0] = 0; 
     }

      // Adds 0's to front of the first binary number when its length is less than the second's
      if(len_x < len_y){
	int length = len_y - len_x; 
	  for(int i = 0; i < length; i++){
            printf("%d", 0);
	  }
	}

	  
        printf("%s", argv[1]);
	
        // checks to see what bitwise operator the user typed in and prints it out
	if(strcmp(argv[2], "-and") == 0) {
          printf(" & ");
	}
	else if(strcmp(argv[2], "-or") == 0){
          printf(" | ");
        }
        else if(strcmp(argv[2], "-xor") == 0){
	   printf(" ^ ");
        }

	// Adds 0's to the front of the second binary number when its length is less than the first's
        if(len_y < len_x){
          int length = len_x - len_y;
	  for(int i = 0; i < length; i++){
            printf("%d", 0);
	  }
        }

	
        printf("%s", argv[3]);

        long int bitIndex_Z = 0; 
        int bit_z[64] = {0};

	// If user choose -and compares the two strings using && and makes a new bit string based off comparison
	if(strcmp(argv[2], "-and") == 0){
          for(int i = 0; i< 64; i++){
            if((bit_x[i] == 1) & (bit_y[i] == 1)){
              bit_z[i] = 1; 
	    }
	    else{
              bit_z[i] = 0; 
	    }
	  }
    	}	       

	// If user choose -or compares the two strings using | and makes a new bit string based off comparison
	if(strcmp(argv[2], "-or") == 0){
          for(int i = 0; i < 64; i++){
	    if((bit_x[i] == 1) | (bit_y[i] == 1)){
              bit_z[i] = 1;
	    }
	    else{
              bit_z[i] = 0; 
	    }
	  }

	}

	// If user choose -xor compares the two strings using ^ and makes a new bit string based off comparison
	if(strcmp(argv[2], "-xor") == 0){
          for(int i = 0; i < 64; i++){
	    if((bit_x[i] == 1) ^ (bit_y[i] == 1)){
              bit_z[i] = 1;
	    }
	    else{
              bit_z[i] = 0; 
	    }
	  }

	}


	
        printf(" evaluates to ");

	// For the following statements chekcs to see which length is bigger between x and y and assgins bitIndex_Z the bigger one
        if(len_x < len_y){
          bitIndex_Z = len_y;
	}
	
	if(len_x > len_y){
          bitIndex_Z = len_x;
	}

	if(len_x == len_y){
          bitIndex_Z = len_x;
	}

	// Prints the comparison's bits in reverse order
	for(int i = bitIndex_Z-1; i >= 0; i--){
          printf("%d", bit_z[i]);
	}

        printf(" using bit strings of length ");
	printf("%ld", bitIndex_Z);
	
	long int answer = 0;
	long int decimal = 1;

	// Converts first input into base 10
        for(int i= 0; i < bitIndex_Z; i++){
          if(bit_x[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit_x[i] == 0){
            decimal = decimal * 2;
	  }
	}
        
	printf("\n");
	printf("%ld", answer);

	
	// Same as above prints out bitwise operator based on user input
        if(strcmp(argv[2],"-and")==0){
          printf(" & "); 
	}

	if(strcmp(argv[2], "-or") == 0){
          printf(" | "); 
	}

	if(strcmp(argv[2], "-xor") == 0){
          printf(" ^ "); 
	}
	
        answer = 0;
	decimal = 1;

	// Converts second input into base 10
	for(int i = 0; i < bitIndex_Z; i++){
          if(bit_y[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit_y[i] == 0){
            decimal = decimal * 2;
	  }
	}
        
	printf("%ld", answer);

	answer = 0;
	decimal = 1;

	// Converts comparison into base 10
	for(int i = 0; i < bitIndex_Z; i++){
	  if(bit_z[i] == 1){
	    answer = answer + decimal; 
	    decimal = decimal * 2;
	  }
	  else if(bit_z[i] == 0){
            decimal = decimal * 2; 
	  }
	}	 

       	
        printf(" evaluates to %ld", answer);
	printf(" using unsigned %ld", bitIndex_Z);
	printf("-bit integers");
      }
      else{
	printf("Error: This program requires 4 command line args\n");
	status = 1;

      }

     return status;
     } // Main




