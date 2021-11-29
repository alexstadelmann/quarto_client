#include "performConnection.h"

void performConnection(int fileSock){
    end = 1; //erstmal auf eins setzen, ggf. ändern; Überprüft ob Endplayer geschickt wurde
    
    //hier Überwachung aller Aufgaben und ankommender Dinge
    do{
         //Beobachtung des Sockets mit select(); Sinvoll, da später auch die Pipe it überwacht werden kann
        FD_ZERO(&readfd);                                                          //Set bereinigen
        FD_SET(fileSock, &readfd);                                                     //Socket (Gameserver) hinzufügen
        
        //Intervall festlegen
        tv.tv_sec = 1;                                                              
        tv.tv_usec = 0;    
        //regelmäßig überprüfen, ob neue Daten ankommen
        retval = select(sizeof(readfd)*2, &readfd, NULL, NULL, &tv);
        if(retval == 1){
            //TODO: Fehlerbehandlung
        }else if(retval){
            socketData = FD_ISSET(fileSock, &readfd);                               //Socket auslesen
            if(socketData!=0){                                                       
                char *buffer = calloc(BUFFERLENGTH,sizeof(char));                   //Speicher reservieren und mit 0 belegen                   
                if((read(fileSock, buffer, BUFFERLENGTH)) < 0){                            
                   //TODO: Fehlerbehandlung                                    
                }
                processInformation(buffer, fileSock);
            }
        }


    }while(end);            //wird mind. einmal durchlaufen, auch wenn Bedingugn nicht erfülllt ist
    
}

void processInformation(char *buffer, int fileSock){
    //Da Server auch mehrere Anfagen hintereinander schicken kann, speichern wir die Anfragen in einem Array zwischen
    char **requests = calloc(BUFFERLENGTH, sizeof(char*));                   //speicher reservieren
    strtoken(buffer, "\n", requests);  

    int i=0;
    do{
        end = !match(requests[i]+2,"QUIT");   
        if(requests[i][0]=='+'){            //positive Antwort
            if(strlen(requests[i])>2){      //auf leeren String überprüfen
              char *response; //TODO: Funktion aufrufen, die je nach Fall reagiert 
              sendResponse(response, fileSock);

            }else{
                //TODO: Fehlerbehandlung?
            }
            
        }else if (requests[i][0]=='-'){     //negative Antwort
            //TODO: Fehlerbehandlung
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
        printf("Client: %s\n",response);                        //Sollen wir ausgeben, was der Client sendet? Könnte gut zum debuggen sein
    }
    if (response != NULL){
        free(response);
    }
        
}