// https://openbook.rheinwerk-verlag.de/c_von_a_bis_z/025_c_netzwerkprogrammierung_004.htm


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int socket = socket(AF_INET, SOCK_STREAM, 0); //ggf. hier anstelle AF_INET auch AF_INET6
if socket == -1{
    //Fehlerbehandlung
    //perror() oder strerror()
}

//herausbekommen der IP-Adresse
struct hostenet hostName;
hostName = *gethostbyname(...); //hier übergeben einer const char *rechnername - whrsl eine Konstante
                                //hier ggf. eine Fehlerquelle da gethostbyname nur einen Zeiger zurück gibt

//check für mich, ob wirklich AF_INET oder AF_INET6 anschauen hostName.h_addrtype

/*
//hier fehlt noch einiges von der Website, letztes Fenster was mich interessiert
memset(&server, 0, sizeof(server));  /k.A. wozu das gut ist
addr = inet_addr(argv[1]);
memcpy((char *)&server.sin_addr, &addr, sizeof(addr));
*/


//struct sockaddr_in befüllen/erstellen
struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_port = ...;              //hier die Konstante einfügen die zuvor definiert wurde; Achtung, Format nochmals nachlesen
server.sin_addr = ...;              //hier irgendwie noch die IP-Adresse einfügen; whrsl das Ergebnis von gethostbyname
server.pad = ...;                   //k.A.; Affüllbytes für sockaddr.


//connect-Versuch
int connectSuccess =  connect(socket, (struct sockaddr*) server, sizeof(server));
if connectSuccess == -1 {
    //Fehlerbehandlung
    //errno, ähnlich wie oben
}



