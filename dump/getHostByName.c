#include <stdio.h>  
#include <stdlib.h>
#include <netdb.h>  //for struct hostent, the return type of gethostbyname(), and struct addrinfo
#include <arpa/inet.h> //for inet_ntop()
#include <string.h> //for memset()

#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"



//compile and run this file to get the ip addresses of the HOSTNAME specified above
//two different ways to get the IP addresses of a host by his name
int main() {

  //way one: use the function gethostbyname(). Seems to only work with IPv4.
  struct hostent *host_data;
  host_data = gethostbyname(HOSTNAME);

  //print host_data
  puts("\n\nWay one: use gethostbyname(): \n\n");
  printf("official name of host: %s\n", host_data->h_name);

  //loop through possible aliases
  int i = 0;
  while(host_data->h_aliases[i] != NULL) {
    printf("host alias: %s\n", host_data->h_aliases[i]);
    i++;
  }

  printf("address type of host(2 stands for classic IPv4): %d\n", host_data->h_addrtype);

  printf("length of one address: %d\n", host_data->h_length);

  //loop through possible addresses
  i = 0;
  while(host_data->h_addr_list[i] != NULL) {
    char currentAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, host_data->h_addr_list[i], currentAddress, INET_ADDRSTRLEN);
    printf("IP address number %d is: %s\n", i + 1, currentAddress);
    i++;
  }

  puts("\n\nWay two: use getaddrinfo():\n");

  //declare one struct of type addrinfo and one pointer to such a struct
  struct addrinfo hints, *response;
  char ip_address[INET6_ADDRSTRLEN]; // can hold both IPv4 and IPv6 addresses

  //prepare the hints struct 
  memset(&hints, 0, sizeof hints); //fill the whole thing with zeros(needed for later casting)
  hints.ai_family = AF_UNSPEC; //meaning unspecified: both IPv4 and IPv6
  hints.ai_socktype = SOCK_STREAM; //we want TCP

  //getaddrinfo gets called, instead of NULL we could pass a port number
  if(getaddrinfo(HOSTNAME, NULL,&hints, &response) != 0) {
    perror("something went wrong with getaddrinfo");
    return EXIT_FAILURE;
  }
  struct addrinfo *p;

  for(p = response; p != NULL; p = p->ai_next) {
    printf("\nprotocol family: %d\nlength of socket address: %d\n", p->ai_family,(int)p->ai_addrlen);
    if(p->ai_family == AF_INET) {
      struct sockaddr_in *ipv4 = (struct sockaddr_in*) (p->ai_addr);
      inet_ntop(AF_INET, &(ipv4->sin_addr), ip_address, INET_ADDRSTRLEN);
      printf("IPv4 address: %s\n", ip_address);
    } else {
      inet_ntop(AF_INET6, p->ai_addr->sa_data, ip_address, INET6_ADDRSTRLEN);
      printf("IPv6 address: %s\n", ip_address);
    }
    
  }
  freeaddrinfo(response); //free linked list response
  return EXIT_SUCCESS;
  
}