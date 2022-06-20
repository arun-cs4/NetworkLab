#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<stdbool.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
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
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

    //Stop and Wait
    
    char lost_frames[1024];
    printf("Enter lost Frames with - as tokenizer\n Example: 1-2-3\n");
    gets(lost_frames);
    do
    {
        bool ACK=true;
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0)
            error("ERROR reading from socket");
        char* token=strtok(lost_frames,"-");
        while(token != NULL)
        {
            if(strcmp(buffer,token) == 0)
            {
                ACK=false;
                break;
            }
            token=strtok(NULL,"-");
        }
        if(ACK)
        {
            printf("Sending ACK\n");
            int temp=atoi(buffer);
            temp++;
            strcpy(buffer,itoa(temp));
            n = write(sockfd,buffer,strlen(buffer));
            if (n < 0) 
                error("ERROR writing to socket");
            bzero(buffer,256);
        }
        else
        {
            printf("Not sending ACK");
            char ch=*token;
            int i=0;
            while(lost_frames[i] != ch)
            {
                i++;
            }
            lost_frames[i]="-";
        }
    }
    while(strcmp(buffer,"NULL"));

    //Stop and Wait

return 0;

}
