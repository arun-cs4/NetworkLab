#include<stdio.h>
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
    int sockfd, newsockfd,clilen, portno;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("error on binding");
        exit(0);
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    bzero(buffer,1024);
    recv(newsockfd, buffer, 1024, 0);
    printf("From sender : %s",buffer);
}
