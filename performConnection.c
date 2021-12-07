#include "performConnection.h"
#include "handleRequest.h"

void performConnection(int fileSock) {
    //printf("Wir sind in performConnection angekommen\n");
    char *buffer = (char*) malloc(BUFFERLENGTH*sizeof(char));
    char **requests = (char**)  calloc(REQUESTSLENGTH,sizeof(char*));
    end = 1; //erstmal auf eins setzen, ggf. ändern; Überprüft ob Endplayer geschickt wurde
    
    //hier Überwachung aller Aufgaben und ankommender Dinge
    do{ 

         int line_length; 
         line_length = recv_all(fileSock, buffer, BUFFERLENGTH-1);
         buffer[line_length] = '\0';  
         stringToken(buffer, "\n",requests);  
         int c = 0;                                                             //counter

        do{
        end = !match(requests[c]+2,"ENDPLAYERS");                                //zum Prüfen ob Ende der Prologphase erreicht (match gibt bei erfolgreichem match 1 zurück.)
        if(buffer[0]=='+'){                                                     //Server gibt positive Antwort zurück
          if(strlen(requests[c])>2){                                            
            printf("S: %s\n",(requests[c]+2));                                  //Serveranfrage
            char *response = handle(requests[c]+2);                             //Hilfsmethode handle für Serveranfrage
            if (response!=NULL){                                                
              if(strcmp(response, "Unknown request\n")){                        //Vergleicht Fall ob Antwort-String == unbekannte Anfrage (und strcmp gibt bei Gleichheit 0 zurück)
                send(fileSock,response,strlen(response),0);                        
              }
                printf("C: %s",response);                                       //Antwort des Clients auf Anfrage Server
            }
            if(response!=NULL){                                                 
              free(response);                                                   //Speicher von response leeren
            }
          }
        }else if(buffer[0]=='-'){                                               //Server gibt negative Antwort zurück
          printf("S: Error! %s\nDisconnecting server...\n",buffer+2);           // Fehlerausgabe (Timeout etc.)
          exit(EXIT_FAILURE);                                                   
        }
        c++;
      }while(requests[c]!=NULL && end); 
    }while(end);            //wird mind. einmal durchlaufen, auch wenn Bedingugn nicht erfülllt ist

    if(buffer!=NULL){
        free(buffer);
    }

    if(requests!=NULL){
        free(requests);
    }
    
}



//Beide unteren Methoden werden derzeit nicht benutzt. Sind noch vom alten Ansatz der nicht ganz geklappt hat. Könnte aber später hilfreich sein, falls wir performConnection
// lieber in mehrere verschiedene Funktionen lagern wollen.
void processInformation(char *buffer, int fileSock){
    printf("Angekommen in processInformation \n");
    //Da Server auch mehrere Anfagen hintereinander schicken kann, speichern wir die Anfragen in einem Array zwischen
    char **requests = calloc(BUFFERLENGTH, sizeof(char*));                   //speicher reservieren
    stringToken(buffer, "\n", requests);  

    int i=0;
    do{
        end = !match(requests[i]+2,"QUIT");   
        if(requests[i][0]=='+'){            //positive Antwort
            if(strlen(requests[i])>2){      //auf leeren String überprüfen
              char *response=handle(requests[i]); 
              sendResponse(response, fileSock);

            }else{
                //TODO: Fehlerbehandlung?
            }
            
        }else if (requests[i][0]=='-'){     //negative Antwort
            //TODO: Fehlerbehandlung, timeout ausgeben

        }
        i++;
    }while(requests[i]!=NULL && end);  

    //Speicher freigeben, falls noch nicht geschehen

    if(buffer!=NULL){                                                           
        free(buffer);                                                               
    }
    if(requests!=NULL){                                                           
        free(requests);                                                            
    }

   

} 

void sendResponse(char *response, int fileSock){
    if (response != NULL){
        send(fileSock,response,strlen(response),0);
        printf("C: %s\n",response);                        //Sollen wir ausgeben, was der Client sendet? Könnte gut zum debuggen sein
    }
    if (response != NULL){
        free(response);
    }    
}