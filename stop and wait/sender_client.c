#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<string.h>
#include<time.h>
//counter function
int counter()
{
    clock_t time_delay = 4 + clock()/CLOCKS_PER_SEC;
    while (time_delay > (clock()/CLOCKS_PER_SEC));
    return -1;
}

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Stop and Wait

    int flag=0;
    char frames[1024];
    printf("Enter the string to be sent with - as tokenizer\n Example: 1-2-3\n");
    gets(frames);

    char* current_frame;
    char* token=strtok(frames,"-");
    do
    {
        printf("Sending frame : %s\n",token);
        //Writting to socket
        bzero(buffer,256);
        strcpy(buffer,token);//writting token to buffer 
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
            error("ERROR writing to socket");
        strcpy(current_frame,token);//current frame saved
        token=strtok(NULL,"-");//jumped to next token
        //Reading from socket , using time counter
        flag=counter();
        while((strcpy(buffer,current_frame)==0) && flag==0)
        {
            bzero(buffer,256);
            n = read(sockfd,buffer,255);
            if (n < 0) 
                error("ERROR reading from socket");
        }
        flag=0;
        if(strcmp(buffer,token) != 0)
        {
            printf("Resending Frame");
            bzero(buffer,256);
            strcpy(buffer,current_frame);//writting token to buffer 
            n = write(sockfd,buffer,strlen(buffer));
            if (n < 0) 
                error("ERROR writing to socket");
        }
        else
        {
            printf("Valid ACK received");
        }
    }
    while(current_frame != NULL);

    //Stop and Wait

return 0;

}
