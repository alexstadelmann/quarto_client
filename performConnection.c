#include "performConnection.h"
#include "handleRequest.h"

void performConnection(int fileSock) 
{
  
    char *buffer = (char*) malloc(BUFFERLENGTH*sizeof(char));
    char **requests = (char**)  malloc(REQUESTSLENGTH*sizeof(char*));
    
    //hier Überwachung aller Aufgaben und ankommender Dinge
    do{ 
      
      int line_length; 
      line_length = recv_all(fileSock, buffer, BUFFERLENGTH-1);
      buffer[line_length] = '\0'; 
      int number_of_lines; 
      number_of_lines = stringToken(buffer, "\n",requests);  
      int c = 0;                                                             //counter

      do{
        //zum Prüfen ob Ende der Prologphase erreicht (match gibt bei erfolgreichem match 1 zurück.)
        end = !match(requests[c]+2,"ENDPLAYERS");     

        //Server schickt positive Nachricht                       
        if(buffer[0]=='+'){   

          //Prüfen, dass Nachricht nicht bloß aus + besteht                                         
          if(strlen(requests[c])>2){ 

            //Servernachricht ausgeben
            printf("S: %s\n",(requests[c]+2));

            //Antwort generieren  
            char *response = handle(requests[c]+2);
            
            //Ist die Antwort leer, dann springen wir zur nächsten Servernachricht
            if(response == NULL) {
              c++;
              continue;
            }
            //Antwort an Server schicken
            send(fileSock,response,strlen(response),0);                        
            
            //Gesendete Antwort ausgeben
            printf("C: %s",response);
            
            //den Speicher von response freigeben  
                                                     
            free(response);                                                   
          }
        //Negative Nachricht vom Server erhalten  
        }else if(buffer[0]=='-'){

          //Fehlermeldung ausgeben
          printf("S: Error! %s\nDisconnecting server...\n",buffer+2);

          //Speicher freigeben
          free(buffer);
          free(requests[0]);
          free(requests);
          return;                                                   
      }
      //Zähler inkrementieren
      c++;
      //solange es neue Lines gibt und wir "ENDPLAYERS" nicht erreicht haben bleiben wir in der Schleife
      } while(requests[c]!=NULL && end);
      
     free(requests[0]);
    //springen heraus sobald wir "ENDPLAYERS" erreichen
    }while(end);            

    //Speicher freigeben  
    free(buffer);
    free(requests);
    
    
    

    
}
