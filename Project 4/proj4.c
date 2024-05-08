#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <pthread.h>
/* Multithreaded program that finds all the diagonal sums equal to input s. Writes it to a text file. 
 * which is a 2d grid with n by n rows and columns. Mallocs and free memory on the heap. Uses pointers. 
 * Uses file i/o system calls read, write, close and open. 
 */

/*                                                                                            
 * The struct grid_t contains a pointer p to a 2D array of                                      
 * unsigned chars with n rows and n columns stored on                                           
 * the heap of this process. Once this is initialized properly,                                 
 * p[i][j] should be a valid unsigned char for all i = 0..(n-1)                                 
 * and j = 0..(n-1).                                                                            
 * Do not alter this typedef or struct in any way.                                              
 */
typedef struct grid_t {
  unsigned int n;
  unsigned char ** p;
} grid;

/* Used for diagonalSums function. Contains two ** char pointers to 2d arrays. f is             
 * initialized to input->p in diagonal sums. d is initialized output->p in diagonal sums.       
 * int a is initialized input->n (the rows). int s is initialied to sum specified by user by in
 * put->s.                                                                                         
 */
typedef struct find_t{
  unsigned int a;
  unsigned char **f;
  unsigned char **d;
  unsigned int s;
} find;

void initializeGrid(grid * g, char * fileName){

  int fdr = -1;

  // Opens file inputted by user
  fdr = open(fileName, O_RDONLY);

  int i;
 
  struct stat file;
  
  // stat call gives file size
  i = stat(fileName, &file);

  // In case call to stat fails 
  if(i == - 1){
    printf("Unable to state file1.\n");
    exit(0);
  }
  
  // Mallocs buffer space for contnets of file
 unsigned char * buffer = (unsigned char *) malloc((int) file.st_size);

 // Reads file onto buffer location on heap
 int bytesRead = read(fdr, buffer,(int) file.st_size);

 // In case bytesRead fails
 if(bytesRead == -1){
   printf("read() failed");
   exit(0);
  }
 
 
 int f = 0;

 // Computes rows and columns by finding number of newline characters in file
 for(int i = 0; i < (int) file.st_size; i++){
   if(buffer[i] == '\n'){
     f++;
   }

 }

  g->n = f;

  // Malloc space for pointer which will take the contents of buffer and put into 2D array. Adds columns.
  g->p = (unsigned char **) malloc(g->n * sizeof(char *));

  // Same process as above adds rows
  for(int i = 0; i < g->n; i++){
   g->p[i] = (unsigned char *) malloc(g->n * sizeof(char));
 }
 
 int w = g->n;
 int z = 0;
 int a = g->n + 1;

 // Puts buffer content onto a heap
 for(int i = 0; i < g->n; i++){
   for(int j=0; j < g->n; j++){
    if(z != w){
     g->p[i][j] = buffer[z];
       z++;
    }
    else if(z == w){
      w += a;
      z++;
      j--;
    }
   }
  }

  free(buffer);
  close(fdr);
}

void * even(void * arguments){
  // Gives struct * args contents of the struct arguments
  find * args = (find *) arguments;

  // Computes one half of left diagonal
    for(int i = args->a-2; i > -1; i-=3){
      int r = 0,col = i;
      
      int x = r, y  = i;
      int sum1 = 0;  
      
      while( r < args->a && col > -1){

	sum1 = sum1 + ((int) args->f[r][col] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	  while(sum1 > args->s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	 }
 
	if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
     }

    // Computes 2nd half of left diagonals
      for(int i = 1; i <  args->a; i+=3){
        int r = i,col = args->a-1;
        int x = r, y  = args->a-1;
        int sum1 = 0;  
      while( r < args->a && col > -1){
	sum1 = sum1 + ((int) args->f[r][col] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > args->s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	   }
 
	 if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
      }

   // Computes all of right diagonal
   for(int i = 1; i < args->a; i+=3){

      int r = 0, col = i;
      int x = r, y  = i;
      int x2 = r, y2 = i;
      int sum1 = 0, sum2 = 0;
      
      while(col < args->a && r < args->a){
	sum1 = sum1 + ((int) args->f[r][col] - 48);
	sum2 = sum2 + ((int) args->f[col][r] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > args->s){
             x++;
	     y++;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2++;    
	   }
	 }
        if(sum2 > args->s){
	  int r2 = x2;
	  int col2 = y2;  
	   while(sum2 > args->s){
             x2++;
	     y2++;
	     sum2 = sum2 - ((int) args->f[col2][r2] - 48);
	     r2++;
	     col2++;
	   }
	 }
	 if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z >= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z--;
	    }
	     
	 }
	 if(sum2 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x2 && z >= y2; w--){
	      args->d[z][w] = args->f[z][w];
	      z--;
	    } 
	 }
	 r++;
	 col++;
      }
      }

   return NULL; 


}

void * odd(void * arguments){
  // Gives struct * args values of struct arguments
  find * args = (find *) arguments;

    // Computes one half of left diagonals
    for(int i = args->a-3; i > -1; i-=3){
      int r = 0,col = i;
      
      int x = r, y  = i;
      int sum1 = 0;  
      
      while( r < args->a && col > -1){

	sum1 = sum1 + ((int) args->f[r][col] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	  while(sum1 > args->s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	 }
 
	if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
     }
    // Computes 2nd half of left diagonals
    for(int i = 2; i <  args->a; i+=3){
      int r = i,col = args->a-1;
      int x = r, y  = args->a-1;
      int sum1 = 0;  
      while( r < args->a && col > -1){
	sum1 = sum1 + ((int) args->f[r][col] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > args->s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	   }
 
	 if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
      }
      
      // Computes all of the right diagonals  
   for(int i = 2; i < args->a; i+=3){

      int r = 0, col = i;
      int x = r, y  = i;
      int x2 = r, y2 = i;
      int sum1 = 0, sum2 = 0;
      
      while(col < args->a && r < args->a){
	sum1 = sum1 + ((int) args->f[r][col] - 48);
	sum2 = sum2 + ((int) args->f[col][r] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > args->s){
             x++;
	     y++;
	     sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	     r2++;
	     col2++;    
	   }
	 }
        if(sum2 > args->s){
	  int r2 = x2;
	  int col2 = y2;  
	   while(sum2 > args->s){
             x2++;
	     y2++;
	     sum2 = sum2 - ((int) args->f[col2][r2] - 48);
	     r2++;
	     col2++;
	   }
	 }
	 if(sum1 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z >= y; w--){
	      args->d[w][z] = args->f[w][z];
	      z--;
	    }
	     
	 }
	 if(sum2 == args->s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x2 && z >= y2; w--){
	      args->d[z][w] = args->f[z][w];
	      z--;
	    } 
	 }
	 r++;
	 col++;
      }
      }


  return NULL;
}


void * sum(void * arguments){
  // Gives struct * args values of struct arguments
  find * args = (find *) arguments;

  // Computes 1st half of left diagonals 
  for(int i = args->a-1; i > -1; i--){
        int r = 0,col = i;
        int x = r, y  = i;
        int sum1 = 0;  
      while( r < args->a && col > -1){
	sum1 = sum1 + ((int) args->f[r][col] - 48);
	if(sum1 > args->s){
	  int r2 = x;
	  int col2 = y;
	    while(sum1 > args->s){
              x++;
	      y--;
	      sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	      r2++;
	      col2--;    
	    }
	}
 
       if(sum1 == args->s){ 
	 int w = r;
	 int z = col; 
       for( ;w >= x && z <= y; w--){
	  args->d[w][z] = args->f[w][z];
	  z++;
       }	     
      }
         r++;
	 col--;
      }
     }

  // Computes 2nd half of left diagonals
   for(int i = 0; i <  args->a; i++){
     int r = i,col = args->a-1;
     int x = r, y  = args->a-1;
     int sum1 = 0;  
     while( r < args->a && col > -1){
       sum1 = sum1 + ((int) args->f[r][col] - 48);
       if(sum1 > args->s){
	 int r2 = x;
	 int col2 = y;
	 while(sum1 > args->s){
           x++;
	   y--;
	   sum1 = sum1 - ((int) args->f[r2][col2] - 48);
	   r2++;
	   col2--;    
	 }
      }
 
	if(sum1 == args->s){ 
	  int w = r;
	  int z = col; 
	  for( ;w >= x && z <= y; w--){
	    args->d[w][z] = args->f[w][z];
	    z++;
	  }   
       }
	 r++;
	 col--;
      }
     }


  
  return NULL;
}

void diagonalSums(grid * input, unsigned long s, grid * output, int t){

  output->n = input -> n; 

  // Mallocs output pointer onto heap creating a 2d array, line below does columns
  output->p = (unsigned char **) malloc(input->n * sizeof(char *));

  // Does rows
  for(int i = 0; i < input->n; i++){
   output->p[i] = (unsigned char *) malloc(input->n * sizeof(char));
 }

  // Initializes values in output->p
  for(int i = 0; i < input->n; i++){
    for(int j = 0; j < input->n; j++){
      output->p[i][j] = '0';
    }
  }

  if(t == 1){

    // All below computes all the diagonal sums, no threads used
    for(int i = 0; i < input->n; i++){

      int r = 0, col = i;
      int x = r, y  = i;
      int x2 = r, y2 = i;
      int sum1 = 0, sum2 = 0;
      
      while(col < input->n && r < input->n){
	sum1 = sum1 + ((int) input->p[r][col] - 48);
	sum2 = sum2 + ((int) input->p[col][r] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y++;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2++;    
	   }
	 }
        if(sum2 > s){
	  int r2 = x2;
	  int col2 = y2;  
	   while(sum2 > s){
             x2++;
	     y2++;
	     sum2 = sum2 - ((int) input->p[col2][r2] - 48);
	     r2++;
	     col2++;
	   }
	 }
	 if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z >= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z--;
	    }
	     
	 }
	 if(sum2 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x2 && z >= y2; w--){
	      output->p[z][w] = input->p[z][w];
	      z--;
	    } 
	 }
	 r++;
	 col++;
      }
      }

    for(int i = input->n-1; i > -1; i--){
      int r = 0,col = i;
      
      int x = r, y  = i;
      int sum1 = 0;  
      
      while( r < input->n && col > -1){

	sum1 = sum1 + ((int) input->p[r][col] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	 }
 
	if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
      }


    for(int i = 0; i <  input->n; i++){
      int r = i,col = input->n-1;
      int x = r, y  = input->n-1;
      int sum1 = 0;  
      
      while( r < input->n && col > -1){
	sum1 = sum1 + ((int) input->p[r][col] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	   }
 
	 if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
    }
   
  }




  if(t == 2){

    // Calls struct find which will allows the ability to pass input and output values to sum
   find args;

   args.f = input->p;
   args.d = output->p;
   args.a = input->n;
   args.s = s; 

   // declares a thread 
   pthread_t t1;

   // creates a thread 
   pthread_create(&t1, NULL, &sum, &args);

   // Computes right diagonals
   for(int i = 0; i < input->n; i++){

      int r = 0, col = i;
      int x = r, y  = i;
      int x2 = r, y2 = i;
      int sum1 = 0, sum2 = 0;
      
      while(col < input->n && r < input->n){
	sum1 = sum1 + ((int) input->p[r][col] - 48);
	sum2 = sum2 + ((int) input->p[col][r] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y++;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2++;    
	   }
	 }
        if(sum2 > s){
	  int r2 = x2;
	  int col2 = y2;  
	   while(sum2 > s){
             x2++;
	     y2++;
	     sum2 = sum2 - ((int) input->p[col2][r2] - 48);
	     r2++;
	     col2++;
	   }
	 }
	 if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z >= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z--;
	    }
	     
	 }
	 if(sum2 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x2 && z >= y2; w--){
	      output->p[z][w] = input->p[z][w];
	      z--;
	    } 
	 }
	 r++;
	 col++;
      }

      }
   
   // Basically wait function for threads allows main and thread to complete 
   pthread_join(t1,NULL);

  
   
  }

  if(t == 3){

    // Gives ability to pass arguments to even and odd functions
   find args1;

   args1.f = input->p;
   args1.d = output->p;
   args1.a = input->n;
   args1.s = s; 

   // Declares two more threads
   pthread_t t1,t2;

   // Creates threads below that compute a third each of diagonal sums
   pthread_create(&t1, NULL, &even, &args1);
   pthread_create(&t2, NULL, &odd, &args1);

   // Computes a third below 
     for(int i = input->n-1; i > -1; i-=3){
       int r = 0,col = i;
       int x = r, y  = i;
       int sum1 = 0;  
      
       while( r < input->n && col > -1){

	sum1 = sum1 + ((int) input->p[r][col] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	 }
 
	if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
     }

      for(int i = 0; i <  input->n; i+=3){
        int r = i,col = input->n-1;
        int x = r, y  = input->n-1;
        int sum1 = 0;  
      while( r < input->n && col > -1){
	sum1 = sum1 + ((int) input->p[r][col] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y--;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2--;    
	   }
	   }
 
	 if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z <= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z++;
	    }
	     
	  }
	 r++;
	 col--;
      }
      }
     
   for(int i = 0; i < input->n; i+=3){

      int r = 0, col = i;
      int x = r, y  = i;
      int x2 = r, y2 = i;
      int sum1 = 0, sum2 = 0;
      
      while(col < input->n && r < input->n){
	sum1 = sum1 + ((int) input->p[r][col] - 48);
	sum2 = sum2 + ((int) input->p[col][r] - 48);
	if(sum1 > s){
	  int r2 = x;
	  int col2 = y;
	   while(sum1 > s){
             x++;
	     y++;
	     sum1 = sum1 - ((int) input->p[r2][col2] - 48);
	     r2++;
	     col2++;    
	   }
	 }
        if(sum2 > s){
	  int r2 = x2;
	  int col2 = y2;  
	   while(sum2 > s){
             x2++;
	     y2++;
	     sum2 = sum2 - ((int) input->p[col2][r2] - 48);
	     r2++;
	     col2++;
	   }
	 }
	 if(sum1 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x && z >= y; w--){
	      output->p[w][z] = input->p[w][z];
	      z--;
	    }
	     
	 }
	 if(sum2 == s){ 
	   int w = r;
	   int z = col; 
	    for( ;w >= x2 && z >= y2; w--){
	      output->p[z][w] = input->p[z][w];
	      z--;
	    } 
	 }
	 r++;
	 col++;
      }
      }

   // Lets all three threads finish 
      pthread_join(t1,NULL);
      pthread_join(t2,NULL);
  }

 
}

void writeGrid(grid * g , char * fileName){

  int fdw = -1;

  // Opens second file to write correct output into
  fdw = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0600);

  // In case open fails
  if(fdw < 0){
    printf("Call to write failed.\n");

  }
  
  // Assgins buffer to write values from diagonal sums into a file
  unsigned char * buffer = (unsigned char *) malloc( (g->n * g->n) + g->n);

  int z = (g->n * g->n) + g->n;
  
  int x = 0;
  
  int i = 0;
  int j = 0;

  // Adds a new line character to the buffer
  for(int i = g->n; i < z; i+= (g->n + 1)){
    buffer[i] = '\n';
  }

  // Gives buffer values needed to write to file
  while(x < z){

    if(j != g->n){
      buffer[x] = g->p[i][j];
      x++;
      j++;
      
    }
    if(j == g->n){
      j = 0;
      i++;
      x++;      
    }

  }
 
  // Writes file into output file text
  write(fdw, buffer, z);
  free(buffer);
  close(fdw);
 
}

void freeGrid(grid * g){

  // Frees 2D array
  for(int i = 0; i < g->n; i++){
      free(g->p[i]);    
  }
  // frees pointer too 2d array
  free(g->p);

  }




