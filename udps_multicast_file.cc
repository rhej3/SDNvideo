/*
   SDN-based application for efficient video streaming -Internet2 Innovative Application award 2013
   Aditi Ghag
   Rasha El-Jaroudi
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>

#define Multicast_PORT 5000
#define Multicast_GROUP "239.0.0.1"
#define multiip "10.0.0.10"
#define BUF_SIZE 10000

int main(int argc, char **argv)
{
   struct sockaddr_in addr;
   int addrlen, sock, cnt;
   struct ip_mreq mreq;
   char message[BUF_SIZE];
   
   if(argc!=5)
    { printf("Usage: %s Multicast_GROUP Multicast_interface_ip port_num File_name \n",argv[0]); 
      exit(1);
    }

   
  /* Set up a socket */
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

  /* Add multicast characterstics */
  addr.sin_addr.s_addr =inet_addr(argv[1]);
  struct ip_mreq imr;
  mreq.imr_interface.s_addr = inet_addr(argv[2]);
  setsockopt(sock,IPPROTO_IP,IP_MULTICAST_IF,&mreq.imr_interface,sizeof(struct in_addr));
      	

 
  char buf[4096],buf1[4096];
  int file_fd;
  ssize_t numread;
  int lenf;


  
  char file[1024];
  snprintf(file,sizeof(file),argv[4]);
 
  printf("file:%s\n",file);
   if(( file_fd = open(file,O_RDONLY)) == -1)   
    {
       
      printf("fd:%d File does not exist\n",file_fd);
    }  
  else
  {
 
    printf("Sending File\n");
    sendto(sock,file,sizeof(file),0,(struct sockaddr*) &addr,addrlen) ;  
    lenf = (long)lseek(file_fd, (off_t)0, SEEK_END); 
    printf("Size of the file:%d\n",lenf);
    (void)lseek(file_fd, (off_t)0, SEEK_SET); 
    ssize_t sum=0;
    while(1) 
    {
      /* Send the file into chunks*/
      while (  (numread = read(file_fd, message, sizeof(message))) > 0 ) 
  
      {
   
  
          sum+=numread;
          //printf("sum:%ld \n",sum);      
          int flags= fcntl(sock,F_GETFL,0);
          fcntl(sock,F_SETFL,flags | O_NONBLOCK);
          sendto(sock,message,numread,0,(struct sockaddr*) &addr,addrlen) ;   
          
          /* Add buffer time before sending out a new batch of packets*/
          int r;
          fd_set rfds;
          struct timeval tv;

          FD_ZERO(&rfds);
          FD_SET(sock, &rfds);

          tv.tv_sec = 0;
          tv.tv_usec = 75000;

          r=select(sock+1, &rfds, NULL, NULL, &tv);

          //usleep(45000);
   }

}
  

}  


  
}
