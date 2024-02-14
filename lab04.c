#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implements !, <<, >> operators. Allows you to convert a bianry string to its
 * ! equivalent and prints out base 10 version of both the inputed string 
 * and ! version. Also, allows you to perform a left and right shift on your 
 * binary string and prints out base ten version.   
 * Usage: ./lab04.out 
*/

int main(int argc, char * argv[]){

    if(argc >= 3){
      unsigned long int x = atol(argv[2]);
      unsigned long int remainder = 0;
      unsigned long int quotient = x;
      unsigned long int bit[64] = {0};
      unsigned long int bitIndex = 0;
      unsigned long int len_x = strlen(argv[2]);
      unsigned long int answer = 0;
      unsigned long int decimal = 1;

      // Stores x in an array 
      while(quotient > 0){
        remainder = quotient % 10;
	quotient = quotient/10;
	bit[bitIndex] = remainder;
	bitIndex++;
      }

      // Converts binary string to not equivalent
      if(strcmp(argv[1],"-not") == 0){
	printf("~");
	printf("%s", argv[2]);
	printf(" evaluates to ");
        unsigned long int bit_2[64] = {0};

	// Copies bit[i]'s elements to bit_2[i]
	for(int i=0; i < len_x; i++){
          bit_2[i] = bit[i];
	}

	// Converts bit_2 to ! equivalent
	for(int i = 0; i < len_x; i++){
          if(!(bit_2[i] == 1)){
            bit_2[i] = 1;
	  }
	  else{
            bit_2[i] = 0;
	  
	  }
	}

	// Prints out not equivalent 
	for(int i = len_x-1; i>= 0; i--){
          printf("%ld", bit_2[i]);
	}

	printf(" using bit strings of length %ld", len_x);
        printf("\n~");

	// Converts original input into base 10
	for(int i=0; i < len_x; i++){
          if(bit[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;

	  }
	  else if(bit[i] == 0){
            decimal = decimal * 2;
	  }
	}

        printf("%ld", answer);
	
        answer = 0;
	decimal = 1; 

	// Converts ! equivalent of original base 10
	for(int i=0; i < len_x; i++){
          if(bit_2[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;

	  }
	  else if(bit_2[i] == 0){
            decimal = decimal * 2;
	  }
	}

        printf(" evaluates to %ld", answer);
	printf(" using unsigned %ld", len_x);
	printf("-bit integers");
      }

      
      // Shifts left binary string 
      if(strcmp(argv[2], "-leftshift") == 0){
        unsigned long int y = atol(argv[1]);
	unsigned long int z = atol(argv[3]);

	quotient = y;

	//Stores y into an array
        while(quotient > 0){
          remainder = quotient % 10;
	  quotient = quotient/10;
	  bit[bitIndex] = remainder;
	  bitIndex++; 

	}
	
	
	printf("%s", argv[1]);
    
        quotient = z;
	remainder = 0;
	bitIndex = 0;
	int bit_z[64] = {0};

	// Converts z to binary
	while(quotient > 0){
          remainder = quotient % 2;
	  quotient = quotient/2;
	  bit_z[bitIndex] = remainder;
	  bitIndex++; 
	}
	
	printf(" << ");

	// Prints binary form of z
	for(int i = strlen(argv[1])-1; i >= 0; i--){
          printf("%d", bit_z[i]);
	}

	// converts y to base 10
	for(int i = 0; i < strlen(argv[1]); i++){
	  if(bit[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit[i] == 0){
            decimal = decimal * 2;
	  }
	}

	
        unsigned long int answer_2 = answer << z;

	quotient = answer_2;
	remainder = 0;
	bitIndex = 0;
	int bit_3[64] = {0};

	// Converts left shifted version of y to binary
	while(quotient > 0){
          remainder = quotient % 2;
	  quotient = quotient/2;
	  bit_3[bitIndex] = remainder;
	  bitIndex++;
	}

	// Prints shifted version of y
	printf(" evaluates to ");
	for(int i = strlen(argv[1])-1; i >= 0; i--){
	  printf("%d", bit_3[i]);
	}

	printf(" using bit strings of length %ld", strlen(argv[1]));
        printf("\n%ld", answer);
	printf(" << ");
	printf("%ld", z);

    	
	answer = 0;
	decimal = 1; 

	// Converts shifted version of y to decimal 
	for(int i = 0; i < strlen(argv[1]); i++){
	  if(bit_3[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit_3[i] == 0){
            decimal = decimal * 2;
	  }
	}

        printf(" evaluates to %ld", answer);
	printf(" using unisgned %ld", strlen(argv[1]));
	printf("-bit integers");
	
       
	
      }
      
      if(strcmp(argv[2], "-rightshift") == 0){
        unsigned long int y = atol(argv[1]);
	unsigned long int z = atol(argv[3]);

	quotient = y;

	// Stores y in array
        while(quotient > 0){
          remainder = quotient % 10;
	  quotient = quotient/10;
	  bit[bitIndex] = remainder;
	  bitIndex++; 

	}
	
	
	printf("%s", argv[1]);
    
        quotient = z;
	remainder = 0;
	bitIndex = 0;
	int bit_z[64] = {0};

	// Converts z to binary 
	while(quotient > 0){
          remainder = quotient % 2;
	  quotient = quotient/2;
	  bit_z[bitIndex] = remainder;
	  bitIndex++; 
	}
	
	printf(" >> ");

	// Prints Binary version of z 
	for(int i = strlen(argv[1])-1; i >= 0; i--){
          printf("%d", bit_z[i]);
	}

	// Converts y to base 10
	for(int i = 0; i < strlen(argv[1]); i++){
	  if(bit[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit[i] == 0){
            decimal = decimal * 2;
	  }
	}

	
        unsigned long int answer_2 = answer >> z;

	quotient = answer_2;
	remainder = 0;
	bitIndex = 0;
	int bit_3[64] = {0};

	// Converts left shift version of y to binanry
	while(quotient > 0){
          remainder = quotient % 2;
	  quotient = quotient/2;
	  bit_3[bitIndex] = remainder;
	  bitIndex++;
	}

	// Prints binary version of y to length specified by user
	printf(" evaluates to ");
	for(int i = strlen(argv[1])-1; i >= 0; i--){
	  printf("%d", bit_3[i]);
	}

	printf(" using bit strings of length %ld", strlen(argv[1]));
        printf("\n%ld", answer);
	printf(" >> ");
	printf("%ld", z);

    	
	answer = 0;
	decimal = 1; 

	// Converts y to base 10
	for(int i = 0; i < strlen(argv[1]); i++){
	  if(bit_3[i] == 1){
            answer = answer + decimal;
	    decimal = decimal * 2;
	  }
	  else if(bit_3[i] == 0){
            decimal = decimal * 2;
	  }
	}

        printf(" evaluates to %ld", answer);
	printf(" using unisgned %ld", strlen(argv[1]));
	printf("-bit integers");
	
       
	
      }

     }


    printf("\n");
    printf("\n");
    
}
