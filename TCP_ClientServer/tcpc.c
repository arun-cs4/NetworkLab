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
    int sockfd,portno;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    strcpy(buffer, "hi i am the sender");
    send(sockfd, buffer, strlen(buffer),0);
}