#include<stdio.h>
#include<stdlib.h>  //contains variable types, macros and various functions
#include<string.h>
#include<sys/types.h>   //definition of number of data types used in system calls
#include<sys/socket.h>  //definitions of structures needed for sockets
#include<netinet/in.h>  //structures  and constants for internet domain addresses
#include<unistd.h>      //read write and close fn are in this file

//client server model -- 
/*
        server              client
         |                   |
        socket()             socket()
        bind()              
        listen()
        accept()  <------    connection()
        read()    <------     write()
        write()   ------>      read()
        close()   <----->     close()
*/
void error(const char *msg) 
{
    perror(msg);    //inbuilt fn
    exit(1);
}
//argv[0] contains file name and argv[1] contains port no
int main(int argc, char *argv[])
{
      if(argc < 2)  //if user does not provides port no
      {
          fprintf(stderr, "Port No not provided\nTerminating\n");//std error
          exit(1);
      }

    //sockfd - file discriptor
    //after creating socket functioning server file, new file discriptor would be required
    //portno port number
    int sockfd , newsockfd , portno , n;  
    char buffer[255]; //for sending msgs

    struct sockaddr_in serv_addr , cli_addr; //already defined in header file netinet-- internet addr 
    //information about internet address
    socklen_t clilen;   //datatype in socket.h used for length cli_addr

    sockfd = socket( AF_INET , SOCK_STREAM , 0);
    //frst arg is communiation domain, second arg is communication type-- sock_stream uses tcp to send data in a stream, thrd arg is protocol--defclilengthault value for tcp is 0, creates teh socket

    if(sockfd < 0)//socket fn resulted in failure, henece socket not created
    {
        error("Error opening socket");
    }

    bzero((char *) &serv_addr , sizeof(serv_addr));    //clears data whatever data is it referencing to

    portno =  atoi(argv[1]);   //turns strings to int here it is using data of port no

    serv_addr.sin_family = AF_INET;     //using structure  
    serv_addr.sin_addr.s_addr = INADDR_ANY;     //using structure 
    serv_addr.sin_port = htons(portno);     //host to network short

     //serv_addr typecasted to sockaddr data structure, if fn binding fails it returns -1
     //socket binded -- meaning addr is given to socket
     if(bind(sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))<0)
        error("Bindidng failed");

     listen(sockfd , 5);     //listening who is trying to connect, file descriptr nd second arg is max limit of client which can get connected to the server

    clilen = sizeof(cli_addr);      //size of structure cli_addr

    newsockfd = accept(sockfd , (struct sockaddr *) &cli_addr ,  &clilen);   //new file discriptor which accepts discriptor nd cli_addr nd the length

    if(newsockfd < 0)
        error("Error on accepting");

    while(1)
    {
        bzero(buffer , 255);    //removes everything in buffer
        n = read(newsockfd , buffer ,  255);    //reads the buffer through socket
        if(n < 0)
            error("ERROR ON READING");
        printf("Ankit : %sAnshu : ", buffer);       //if not found any error then we will print the client nd print the data we got through reading 
        bzero(buffer, 255);     //again deletes everything
        fgets(buffer , 255 , stdin);    //fn reads bytes from stram which we want to send

        n = write(newsockfd , buffer , strlen(buffer));     //writes teh data in the clients actually posts the data not write
        if(n < 0)
            error("Error on Writing");      //if error aa gyi toh

        int i = strncmp("Bye" , buffer , 3);      //if server says bye, then we also say bye meaning we exit
        if(i == 0)
            break;
    }

    close(newsockfd);       //close the file discriptor
    close(sockfd);          //closing the file discriptor
    return 0;
    


    





    

}
