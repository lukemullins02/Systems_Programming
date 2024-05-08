#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* Compares input files one and two by user. Writes every byte of file 1 that is different then
 * file two in differenceFoundInFile1.txt. Accesses one byte at time of each file. 
 */
void step1(int a, int b, int c);

/* Compares input files one and two by usesr. Writes every byte of file 2 that is different then
 * file two in differencesFoundInFile2.txt. Reads both files into dynamically allocated arrays.
  That are the excact number of bytes needed. 
*/
void step2(char * x, char * y,int a, int b, int c);

// Handls exceptions in main method that could occur
void handleExceptions(int argc,int fdr_1, int fdr_2, int fdw_1, int fdw_2);

/* This program takes two inputs from the user of two files. If the user makes an error a message pops up
 * to let user know their error. Writes two new files into users directory. Frees all memory allocated and 
 * prints time in milliseconds each step took. 
 */ 
int main(int argc, char * argv[]){ 

  int fdr_1 = -1;
  int fdr_2 = -1;
  int fdw_1 = -1;
  int fdw_2 = -1;

  fdr_1 = open(argv[1], O_RDONLY);
  fdr_2 = open(argv[2], O_RDONLY);
  fdw_1 = open("differencesFoundInFile1.txt",O_WRONLY | O_CREAT | O_TRUNC, 0600); 
  fdw_2 = open("differencesFoundInFile2.txt",O_WRONLY | O_CREAT | O_TRUNC, 0600); 
  handleExceptions(argc, fdr_1, fdr_2, fdw_1, fdw_2);

  // Used to measure time of step1
  struct timeval start,end;

  gettimeofday(&start,NULL);
  
  step1(fdr_1,fdr_2,fdw_1);

  gettimeofday(&end,NULL);

  double time_1;

  time_1 = (end.tv_sec - start.tv_sec) * 1e6;
  time_1 = (time_1 + (end.tv_usec - start.tv_usec)) *1e-6;
  time_1 = time_1 * 1000;
  
  struct timeval start_2,end_2; 

  // Used to measure time of step2
  gettimeofday(&start_2, NULL);
  
  step2(argv[1], argv[2], fdr_1, fdr_2, fdw_2); 
  
  gettimeofday(&end_2, NULL);

  double time_2;

  time_2 = (end_2.tv_sec - start_2.tv_sec) * 1e6;
  time_2 = (time_2 + (end_2.tv_usec - start_2.tv_usec)) *1e-6;
  time_2 = time_2 * 1000;
  
  printf("Step 1 took %f milliseconds\n", time_1);
  printf("Step 2 took %f milliseconds\n", time_2);
  
  close(fdr_1);
  close(fdr_2);
  close(fdw_1);
  close(fdw_2);

  return 0; 
}

void handleExceptions(int argc, int fdr_1, int fdr_2, int fdw_1, int fdw_2){
  if(argc != 3){
    printf("Usage: proj3.out <file1> file2>\n");
    exit(0);
  }
  if((fdr_1 < 0) | (fdr_2 < 0)){
    printf("There was an error reading a file.\n");
    exit(0);
  }
  if((fdw_1 < 0) | (fdw_2 < 0)){
    printf("There was an error writing a file.\n");
    exit(0);
  }
}

void step1(int a, int b, int c){

  int bufferSize = 2;

  char * buffer = (char *) malloc(sizeof(char) * bufferSize);
  buffer[bufferSize - 1] = '\0';
  char * buffer_2 = (char *) malloc(sizeof(char) * bufferSize);
  buffer_2[bufferSize - 1] = '\0';
  
  int bytesRead = read(a, buffer, bufferSize - 1);
  int bytesRead_2 = read(b, buffer_2, bufferSize - 1);

  // While loop is used to compare two files. Loads a new byte each time. 
  while((bytesRead > 0) | (bytesRead_2 > 0)){

    for(int i = 0; (buffer[i] != '\0') | (buffer_2[i] != '\0'); i++){
      if(buffer[i] != buffer_2[i]){
        write(c, buffer, bytesRead);
      }
    }

    bytesRead = read(a,buffer, bufferSize - 1);
    bytesRead_2 = read(b,buffer_2, bufferSize-1);
  
  }
  
  free(buffer);
  free(buffer_2); 
 
}


void step2(char * x, char * y, int a, int b, int c){
  
  struct stat file_1;
  struct stat file_2;
 
  int i;
  int n;
  int z;

  a = -1;
  b = -1;

  i = stat(x, &file_1);
  n = stat(y, &file_2);

  if((i == -1) | (n == -1)){
    printf("Unable to stat file 1 or file 2.");
    exit(0);
  }
 
  
  a = open(x, O_RDONLY);
  b = open(y, O_RDONLY);
  
  char * buffer_3 = (char *) malloc(sizeof(char) * ( (int) file_1.st_size + 1));
  buffer_3[(int) file_1.st_size] = '\0';
  char * buffer_4 = (char *) malloc(sizeof(char) * ( (int) file_2.st_size + 1));
  buffer_4[(int) file_2.st_size] = '\0';

  int bytesRead = read(a, buffer_3, (int) file_1.st_size); 
  int bytesRead_2 = read(b, buffer_4, (int) file_2.st_size);

  if((bytesRead == -1) | (bytesRead_2 == -1)){
    printf("Unable to read file 1 or file 2.");
    exit(0);   
  }
  
  if((int) file_1.st_size > (int) file_2.st_size){
    z = (int) file_1.st_size;
  }
  else{
    z = (int) file_2.st_size;
  }
  
  char * buffer_5 = (char *) malloc(sizeof(char) * (z + 1));
  buffer_5[z] = '\0';

  int q = 0;

  // Compares file 1 and 2 and writes differences into the new buffer
  for(int w = 0; buffer_4[w] != '\0'; w++){
    if(buffer_4[w] != buffer_3[w]){
      buffer_5[q] = buffer_4[w];
      q++;
    }
  }

  write(c,buffer_5, q);  

  close(a);
  close(b);
  close(c);
  free(buffer_3);
  free(buffer_4);
  free(buffer_5);
}
