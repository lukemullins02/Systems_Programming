#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "compress.h"
#include "decompress.h"

int main(int argc, char * argv[]){

  // Calls compress method when user types flag "-c"
  if(strcmp(argv[1], "-c")==0){
    compress(argc, argv);
  }

  // Calls decompress method when user types "-d"
  if(strcmp(argv[1], "-d")==0){
    decompress(argc, argv);
  }


  return 0;
}//main
 
