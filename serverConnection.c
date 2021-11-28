// https://openbook.rheinwerk-verlag.de/c_von_a_bis_z/025_c_netzwerkprogrammierung_004.htm


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "header.h"


int connectServer(){
    struct hostenet *hostName;
    struct sockaddr_in server;

    
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); //ggf. hier anstelle AF_INET auch AF_INET6
    if (socket_fd == -1){
        //Fehlerbehandlung
        //perror() oder strerror()
    }

    //herausbekommen der IP-Adresse
    hostName = *gethostbyname(HOSTNAME); //hier ggf.  Fehlerquelle da gethostbyname nur einen Zeiger zurück gibt 
    if (hostName == NULL) {
        //Fehlerbehandlung error
    }                               


    //check für mich, ob wirklich AF_INET oder AF_INET6 anschauen hostName.h_addrtype
    /*
    //hier fehlt noch einiges von der Website, letztes Fenster was mich interessiert
    memset(&server, 0, sizeof(server)); 
    addr = inet_addr(argv[1]);
    */

    memcpy((char *)&server.sin_addr, hostName->h_addr_list[0], hostName->h_length);

    //struct sockaddr_in befüllen/erstellen
    server.sin_family = AF_INET;
    server.sin_port = htons(PORTNUMBER);    //Achtung, Format nochmals nachlesen
    //server.sin_addr = ...;              //durch memcpy gamacht
    //server.pad = ...;                   //k.A.; Affüllbytes für sockaddr. muss glaub nicht gemacht werden


    //connect-Versuch
    int connectSuccess =  connect(socket_fd, (struct sockaddr*) server, sizeof(server));
    if (connectSuccess == -1) {
        //Fehlerbehandlung
        //errno, ähnlich wie oben
        return -1;
    } else {
        printf("With Server connected!");
        return 1;
    }
}


