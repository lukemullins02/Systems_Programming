#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void compress(int a, char** b){

  if(a >= 0){

    int len = strlen(b[2]);    
    int i = 0;
    printf("%d ", len);
    bool go = true;
    unsigned char a = 130; 
    unsigned char t = 21;    
    unsigned char l = 72;
    unsigned char l_2 = 4;
    // Converts G's and C's to L's and Q's bc the program breaks with G and C for some reason 
    for(int w = 0; w < len; w++){
      if(b[2][w] == 'C'){
	b[2][w] = 'L';
      }
    else if(b[2][w] == 'G'){
      b[2][w] = 'Q';
    }

    }

    while(go){

     unsigned char num[8] = {0};

       
     // Converts DNA String into Binary strings of length 8 and prints them out
     for(int j = 0; j < 8; j = j+2){
       if(b[2][i] == a>>1){
          num[j] = 0;
	  num[j+1] = 0;	  
          }
	else if(b[2][i] == t<<2){
          num[j] = 0;
      	  num[j+1] = 1;
	  }
	else if(b[2][i] == (l | l_2)){
 	  num[j] = 1;
	  num[j+1] = 0;
	   }
	else if(b[2][i] == 'Q'){
	  num[j] = 1;
	  num[j+1] = 1;
	   }
	i++;
    }

      unsigned long int answer = 0;
      unsigned long int decimal = 1;

      // Converts binary strings to base 10
       for(int z = 7; z >= 0; z--){
         if(num[z] == 1){
           answer = answer + decimal;
	   decimal = decimal * 2;
        }
         else if(num[z] == 0){
           decimal = decimal * 2;
        }
       }
       
       printf("%ld ", answer);

       // Closes while loop when you reach end of string 
       if((b[2][i] != 'A') & (b[2][i] != 'T') & (b[2][i] != 'L') & (b[2][i] != 'Q')){
	 go = false;
       }
       
       
        }
       }    

 

}
 
  

 

