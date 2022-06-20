#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char filename[10];
    int sockfd, newsockfd, portno, clilen, option;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
    error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");
    n = read(newsockfd,buffer,255);
    if (n < 0)
        error("ERROR reading from socket");
    option = atoi(buffer);
    if (option==1)
    {
        n = write(newsockfd,"Enter file name",15);
        if (n < 0) 
            error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(newsockfd,filename,10);
        if (n < 0)
            error("ERROR reading from socket");
        //file name
        puts(filename); //filename
        fp=fopen("1.txt","r");
        if(fp==NULL)
        {
            printf("error opening");
        }
        char c;
        while ((c=fgetc(fp))!=EOF)
        {
            printf("%c",c);
        }

        /*if(fp==NULL)
        {
            n = write(newsockfd,"No such a file",14);
            if (n < 0) 
                error("ERROR writing to socket");
        }
        else
        {
            while (fscanf(fp, "%s", buffer)!=EOF)
            {
                n = write(newsockfd,buffer,255);
                if (n < 0) 
                    error("ERROR writing to socket");
                bzero(buffer,256);
            }
            bzero(buffer,256);
            n = write(newsockfd,"BYE",3);
            if (n < 0) 
                error("ERROR writing to socket");
        }*/
    }
    
    return 0;
 }
