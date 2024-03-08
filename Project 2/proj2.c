#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* Program allows user to input grades using scanf. The user is told if they input a negative number the program ends. Once program ends average is calucalted, how many allocations, frees, and total bytes were allocated. 
 */
int main(void){

  double * p;
  double * z;
  int x = 40;
  bool y = true;
  int len = 0;
  int k = 0;
  int n = 0;
  int bytes = 0;
  int alloc = 0;
  double w;
  
  printf("Enter a list of grades below where each grade is separated by a newline character.\n");
  printf("After the last grade is entered, enter a negative value to end the list.\n");

  while(y){

  len += 5;

  // Keeps going through process till user puts negative number
  for(; k < len && n != 1; k++){

    // handles case 0 if the user types negative number bytes not allocated
   if(k == 0){

     scanf("%lf", &w);

     if(w >= 0){
       p = (double *) malloc(x);
       *(p + k) = w; 
       printf("Allocated %d bytes to the heap at %p\n", x, (void*) p);
       printf("Stored %.6lf in the heap at %p\n", *(p + k), (void*) (p+k));
       bytes = 40;
       alloc++;
     }
     else if(w < 0){
	n = 1;
     }
   }

   // handles rest of the cases user types in before inputting a negate number
   if( k > 0){  
     scanf("%lf",(p + k));
     if(*(p + k) >= 0){
       printf("stored %.6lf in the heap at %p\n",*(p + k), (void*) (p+k));
     }
     else if(*(p + k) < 0){
       n = 1;   
     }
   }
    
 }

  // Breaks out of the while loop 
  if(n == 1){
    y = false;
  }

  // If number isn't negative
  if(n != 1){
    printf("Stored %d grades (%d bytes) in the heap at %p\n", k,x,(void*) p);
    printf("Heap at %p is full.\n", (void*) p);

    alloc++;

    x += 40;

    bytes = x + bytes;    
    
    z = (double *) malloc(x);

    // Puts doubles allocated to the previous byte block of memory to next
    for(int i = 0; i < len; i++){
      *(z + i) = *(p + i);
    }

    printf("Allocated %d bytes to the heap at %p\n", x,(void*) z);
    printf("Copied %d grades from %p to %p\n",k, (void*) p, (void *) z);
    printf("Freed %d bytes from the heap at %p\n", x-40,(void*) p);
    
    free(p);
    
    p = z;
    
 
  }
 }


  k--;

  double avg = 0;

  // Adds all the numbers together
  for(int i = 0; i < k; i++){
    avg = avg + *(p + i);
  }

  // Calculates average 
  if(avg != 0){
    avg = avg/k;
  }

  printf("The average of %d grades is %lf.\n",k,avg);

  // Calculates if input by user was greater than or equal to number or less than
  for(int i = 0; i < k; i++){
    if(*(p + i) >= avg){
      printf("%d. The grade of %lf is >= the average.\n", i + 1, *(p + i));
    }
    else if(*(p + i) < avg){
      printf("%d. The grade of %lf is < the average.\n",i + 1,*(p + i));
    }
  }

 // Makes sure that if bytes aren't allocated thus number isn't printed 
 if(k != 0){
   printf("Freed %d bytes from the heap at %p\n",x, (void*) p);
 }

 printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", alloc, alloc, bytes);

  free(p);

 

}

  
