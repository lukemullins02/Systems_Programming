#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

/* Makes a single call to fork and gives us a parent process and a child process. 
 * The child process is executed first and runs the "ps" linux command. The parent is told
 * to wait till child is finished then it executes countdown.out.
 */ 
int main(int argc, char * argv[]){

  int i,x,y,z;
  char run[] = "/usr/bin/ps";
  char * arg[] = {"ps", NULL};
  char * end[] = {NULL};
  char run_2[] = "countdown.out";
  
  i = fork();

  //If fork doesn't work
  if(i < 0){
    printf("The call to fork failed");
    return 0;
  }

  // If the parent process, it runs these statements and waits for the child to finish before executing countdown 
  if(i != 0){
    printf("The parent's PID is %d.\n", getpid());
    printf("The parent is now forking.\n");
    
    z =  wait(NULL);

    // If wait doesn't work
    if(z == -1){
      printf("The call to wait failed");
      return 0;
    }
    
    x = execve(run_2,argv,NULL);

    // If 1st call to execve doesn't work
    if(x == -1){
      printf("The 1st call to execve failed");
      return 0;
    } 
    
    return 0; 
   }
  
  // If the child process, runs these commands and executes execve before parent process
  if(i == 0){
    printf("The child's PID is %d.\n", getpid());
    printf("The child is executing ps.\n"); 

    y = execve(run, arg, end);

    // If 2nd call to execve doesn't work
    if(y == -1){
      printf("The 2nd call to execve failed");
    }
    
    return 0;  
    } 


  return 0;
  
}
