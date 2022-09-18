#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No port given");
        exit(0);
    }
    int sockfd,portno,clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    strcpy(buffer, "Hi I am the sender");
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
}