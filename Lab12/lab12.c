#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
/* Uses UNIX system calls pipe and dup2 for interprocess communication between parent and child processes.
 * Makes calls to fork, execvp, and wait as well. Standard output of child process is piped to parent process.
 */
int main(int argc, char * argv[]){
  
  int fd[2];
  pid_t cpid;

  
  int w;
  int i;

  // Gives w the position -pipe is located
  for(i = 0; i < argc; i++){
    if(strcmp(argv[i], "-pipe") == 0){
      w = i;
      i = argc;
    }
  }
  
  char * list[w];

  list[w-1] = NULL;

  // Passes all the arguments in argv after ./lab12.out but before -pipe
  for(int x = 0; x < w-1; x++){
    list[x] = argv[x+1];
    } 

  // Executes for function, allows us to send output from child process as input to parent process
  pipe(fd);

  // Creates child and parent process
  cpid = fork();


  if(cpid == 0){

    // Takes output from child process puts it in fd[1]
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);

    // executes arguments in list
    int x = execvp(argv[1], list);
    
    // if execvp fails
    if(x == -1){
      printf("First call to execvp failed.\n");
      return 1; 
    }
    
    
  }
  else{

    // Takes output from fd[1] and uses it as input
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);

    int y = argc - w;

    char * list2[y];

    list2[y-1] = NULL;

    // Copies arguments after -pipe into list2
    for(int x = 0; x < y-1; x++){
       list2[x] = argv[w + 1 + x];
    }

    // executes arguments in list2
    int z = execvp(argv[w+1], list2); 

    // If execvp fails
    if(z == -1){
      printf("Send call to execvp failed.\n");
      return 2;
    }

    // Parent process waits for child process to finish
    wait(NULL);
    
    }
  
}
