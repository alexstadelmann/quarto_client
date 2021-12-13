#include "config.h"
#include "header.h"

char* readConfig(char* name) {

    FILE *file = NULL;       
    char *substring = NULL;
    char *firstOcc = NULL;
    char *line = NULL;
    char *config = confile;   
    const char *delim = "= \n";                                                   
    char string[BUFFERLENGTH] = {0};                                           

    firstOcc = strstr(string, name);                          // finds the first occurrence of string in name
    line = fgets(string,BUFFERLENGTH,file);                   //reads a line from the specified stream and stores it into the string pointed to by string
  
    file = fopen(config, "r");                                //open config

    if(file == NULL) {                                        //filter error: couldn't open file
        
        perror("Error: Couldn't open file!");
        exit(EXIT_FAILURE);

    } else {                                                                        
         
        while(line) {                                         //while line true
            
            if(firstOcc != NULL) {                             // filter 

                substring = findValueParam(delim, string);   //function returns value of the parameter
                break;

            } 
        } 
   }

  fclose (file);             //close config                                                  

  char *res = NULL;
  res = (char *)calloc(BUFFERLENGTH, sizeof(char));           // allocates the requested memory, returns a pointer to it and sets allocated memory to zero
  strcpy(res, substring);  //copies the string pointed to
  return res;
}


char* findValueParam(const char *delim, char *string) {  

    char *pointer = NULL;                                                                 
    char *res = NULL;

    pointer = strtok(string, delim);            //breaks string into a series of tokens using delim

    while(pointer != NULL) {                             //while pointer is not finished

      res = pointer;
      pointer = strtok(NULL, delim);            //pointer moves one further

    }
   // free(pointer);
    return res;
}


void createClientConfig() {

  FILE *file = NULL;

  file = fopen(confile, "r");                                                                               //open file

  if(file != NULL) {

    fclose(file);                                                                                           //close file

  } else {

    printf("Creating client.conf \n");           
    file = fopen(confile, "w");                                                                             //create client.conf

    if(file == NULL) {                                                                                      //check whether the file can be accessed

  	   perror("Error");  

    } else {

      fprintf(file, "hostname=%s\nportnumber=%i\ngamekindname=%s", HOSTNAME,PORTNUMBER,GAMEKINDNAME);
      fclose(file);                                                                                        //close file

    }
  }
}