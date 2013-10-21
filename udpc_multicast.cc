/*
 SDN-based application for efficient video streaming -Internet2 Innovative Application award 2013
 Aditi Ghag
 Rasha El-Jaroudi
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>
#include <strings.h>
#include <fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <errno.h>

#define Multicast_PORT 5000
#define Multicast_GROUP "239.0.0.1"
#define multiip "10.0.0.11"
#define BUF_SIZE 50000

int main(int argc, char **argv)
{
  struct sockaddr_in addr;
  int  sock, cnt;
  socklen_t addrlen;
  struct ip_mreq mreq;
  char message[BUF_SIZE];
  ssize_t numRead;

    if(argc!=4)
      { 
        printf("Usage: %s Multicast_GROUP Multicast_interface_ip port_num \n",argv[0]); 
        exit(1);
      }
   
  sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) 
      {
        perror("socket");
     
      }
  bzero((char *)&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(atoi(argv[3]));
  addrlen = sizeof(addr);

      
    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) 
      {        
        perror("bind");
	 
      }    
  
  /* Add multicast characterstics */
  mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);         
  mreq.imr_interface.s_addr = inet_addr(argv[2]);       
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,&mreq, sizeof(mreq)) < 0) 
      {
	      perror("setsockopt mreq");
        int n = 1024 * 1024;
        setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)) ;
	 
      }         
  
  FILE *f;
  char buf[1024];
  f = fdopen(sock, "a+");
  fgets(buf,sizeof(buf),f);

  printf("Receiving file %s\n",buf);
  int rFile;
  rFile = open(buf,O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
  ssize_t sum=0;
    while(1)

      {
        numRead= recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*) &addr,&addrlen);
        //printf("numread:%ld\n",numRead);
        sum+=numRead;
        //printf("Sum:%ld\n",sum);
        write(rFile,message,numRead);
 
      }   
 }
