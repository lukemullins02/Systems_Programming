#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
/* Program uses calls to socket, send, connect, and close. Sends a message to 
 * server which once it recieves it prints it out. Limits user to port numbers
 * between 60,000 and 65,535. Allows user to specify ip address type. 
 */
int main(int argc, char * argv[]){

  // Error checking for if user doesn't put enough arguments
  if(argc < 4){

    printf("./lab13.out <ip address> <port> <message>\n");

  }
  else{
    
  // creates socket for client
  int soc = socket(AF_INET, SOCK_STREAM, 0);
  
  int port = atoi(argv[2]);

  // Error handling if user goes under or over range of port numbers allowed
  if( (port < 60000) | (port > 65535) ){
    printf("Port can't be less than 60000 or greater than 65535\n");
    return 0;
  }

  
  char msg[80] = "The server received: %s";

  int x = 21; 

  // Gets rid of apostrophe from argv[3] and adds to msg
  for(int i = 3; i < 4; i++){
    for(int j = 3; argv[i][j] != '\0'; j++){
      msg[x] = argv[i][j];
      x++;
    }
    msg[x] = ' '; 
    x++;
  }

  // adds rest of arguments between argv[3] and last one
  for(int i = 4; i < argc-1; i++){
    for(int j = 0; argv[i][j] != '\0'; j++){
      msg[x] = argv[i][j];
      x++;
    }
    msg[x] = ' ';
    x++;
    }

  int n = 0;

  // Finds where the apostrophe is in argv[argc-1]
  for(int i = argc-1; i < argc; i++){
    for(int j = 0; argv[i][j] != '\0'; j++){
      n++;
    }
  }

  // adds the last argv to msg
  for(int i = argc-1; i < argc; i++){
    for(int j = 0; j < n-3; j++){
      msg[x] = argv[i][j];
      x++;
    }
    
  }
  
  char * ip = argv[1];

  // Holds ip address, ip address type (ipv4), and port number
  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = inet_addr(ip);

  // Makes connection 
  int status = connect(soc, (struct sockaddr*)&server, sizeof(server));

  // in case call to connect fails
  if(status == -1){

    printf("Call to connect failed\n");
    
  }

  // send msg to server
  send(soc,msg, sizeof(msg), status);

  // close socket
  close(soc);
  
  }
}
