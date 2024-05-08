#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


// Used to add sums of user inputted doubles
double answer; 

// Handles kill -8 signal and prints users sums added
void f(int num){
  printf("The sum is %lf\n", answer);
  printf("Program ended by handling the signal from kill -8 %d.\n", getpid());
  exit(0);
}

// Handles kill -10 signal and prints users sums added
void g(int num){
  printf("The sum is %lf\n", answer);
  printf("Program ended by handling the signal from kill -10 %d.\n", getpid());
  exit(0);
}

// Handles kill -12 signal and prints users sums added 
void h(int num){
  printf("The sum is %lf\n", answer);
  printf("Program ended by handling the signal from kill -12 %d.\n", getpid());
  exit(0);
}

int main(int argc, char * argv[]){

  signal(8, f);
  signal(10, g);
  signal(12, h);  
   
  long pid = getpid();

  bool yes = true;
  
  
  printf("Program started with pid = %ld\n", pid);

  printf("Enter a list of doubles to sum,\nand to to end the program,\nrun one of the following unix commands\n");

  printf("  kill -8 %ld\n", pid);
  printf("  kill -10 %ld\n", pid);
  printf("  kill -12 %ld\n", pid);

  answer = 0;

  // Creates infinite loop to scanf user inputs till they input a signal mentioned above
  while(yes){

       
    double handler[1] = {0};
    char c[80] = {0};
    int check;
    
    // Scans user input
    check = scanf("%lf", handler);

    // If scan if successful
    if(check == 1){      
      answer = answer + handler[0];
    }
    // If scan is unsuccessful
    if(check == 0){
      scanf("%79[^\n]s", c);
      printf("Error: please input a numeric value.\n");	
    }
    // If input is from redirected file
    if(check == -1){
      sleep(60);
      printf("The sum is %lf\n",answer);
      printf("The program ended after sleeping for 60 seconds.\n");
      exit(0);
    }
            
  } 
  
 }


