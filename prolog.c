#include "performConnection.h"
#include "handleRequest.h"
#include "prolog.h"
#include <unistd.h>

bool prolog(int socket_fd) {
  char *line = (char*) malloc(BUFFERLENGTH*sizeof(char));

  do {

    if(!read_line(socket_fd, line)) {
      perror("reading line");
      return false;
    };
    

    end = match(line + 2, "ENDPLAYERS");

    //positive message
    if(line[0] == '+') {

      
      char *response = handle(line + 2);
      
      //if response is empty, skip to next message
      if(response == NULL) {
      continue;
      }
      //Antwort an Server schicken
      send(socket_fd,response, strlen(response),0);                        
            
      //Gesendete Antwort ausgeben
      printf("C: %s",response);
      free(response);

    }  else {
      printf("S: Error! %s\nDisconnecting server...\n",line+2);
      free(line);
    }
  } while (end != 1);
  free(line);
  return true;
}  



