/*
filename server_ipadress portno 
should be same as that of server

argv[0] = filename
argv[1] = server ipaddress
argv[2] = portno

*/

#include<stdio.h>
#include<stdlib.h>  //contains variable types, macros and various functions
#include<string.h>
#include<sys/types.h>   //definition of number of data types used in system calls
#include<sys/socket.h>  //definitions of structures needed for sockets
#include<netinet/in.h>  //structures  and constants for internet domain addresses
#include<unistd.h>      //read write and close fn are in this file
#include <netdb.h>  //hostent structure -- used to store info about given host such as host name and ipv4 address

void error(const char *msg) 
{
    perror(msg);    //inbuilt fn
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd , newsockfd , portno , n;  
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];   //msgs we want tos send or recieved

    if(argc < 3)  //if user does not provides port no
      {
          fprintf(stderr, "usage %s hostname port\n", argv[0]);//std error
          exit(1);
      }
    portno =  atoi(argv[2]);   //turns strings to int here it is using data of port no

    sockfd = socket( AF_INET , SOCK_STREAM , 0);
    if(sockfd < 0)//socket fn resulted in failure, henece socket not created
    {
        error("ERROR opening socket");
    }

    //no new connection is created hence only one file discriptor would be used


    server = gethostbyname(argv[1]);  //we gwet the variable for server to which we want to connect 
    if(server == NULL)
    {
        fprintf(stderr , "ERROR, no such host");
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));    //clears data whatever data is it referencing to

    serv_addr.sin_family = AF_INET;     //using structure 
    bcopy((char *) server->h_addr , (char *)&serv_addr.sin_addr.s_addr, server->h_length);  // copies bytes from host to sockaddr ~~~not confirm
    serv_addr.sin_port = htons(portno);     //host to network short

    //connect to server
     printf("Ankit : ");
    if(connect(sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) <0)
        error("Connection Failed");

    while(1)
    {
        bzero(buffer , 255);
        fgets(buffer , 255 , stdin);
        n = write(sockfd , buffer, strlen(buffer));
        if(n < 0)
            error("Error on writing");

        
        bzero(buffer , 255);
        n = read(sockfd , buffer , 255);
        if(n < 0)
            error("Error on reading");
        printf("Anshu : ");
        printf("%s", buffer);
        

        int i = strncmp("Bye" , buffer , 3);      //if server says bye, then we also say bye meaning we exit
        if(i == 0)
            break;

        printf("Ankit : ");
    }

    close(sockfd);          //closing the file discriptor
    return 0;

}
