// https://openbook.rheinwerk-verlag.de/c_von_a_bis_z/025_c_netzwerkprogrammierung_004.htm


#include "header.h"
#include "serverConnectionHeader.h"



int connectServer(){
    struct hostent *hostName;
    struct sockaddr_in server;

    
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //ggf. hier anstelle AF_INET auch AF_INET6
    if (socket_fd == -1){
        //Fehlerbehandlung
         perror("Socket could not be created!\n");
         return(EXIT_FAILURE);
    } 

    //herausbekommen der IP-Adresse
    hostName = gethostbyname(HOSTNAME); //hier ggf.  Fehlerquelle da gethostbyname nur einen Zeiger zurück gibt 
    if (hostName == NULL) {
        //Fehlerbehandlung error
         perror("Hostname missing or not able to resolve!\n");
         return(EXIT_FAILURE);
    }                     

    
    //memset(&server, 0, sizeof(server));
    memcpy((char *)&server.sin_addr, hostName->h_addr_list[0], hostName->h_length);

    //struct sockaddr_in befüllen/erstellen
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUMBER);    

    //connect-Versuch
    //printf("IP-Adresse: %s\n", inet_ntoa(server.sin_addr));
    int connectSuccess =  connect(socket_fd, (struct sockaddr*) &server, sizeof(server));
    if (connectSuccess == -1) {
        //Fehlerbehandlung
        //errno, ähnlich wie oben
         perror("Not able to connect with Server!\n");
         return(EXIT_FAILURE);
    } else if(connectSuccess ==0){
        printf("With Server connected!\n");
        //Hier muss wahrscheinlich noch performConnection() aufgerufen werden. Kann lokal probiert werden
        performConnection(socket_fd);
        return 1;
    }
    return connectSuccess;
}


