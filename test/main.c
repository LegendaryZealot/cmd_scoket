#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int sockfd;
    int len;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(3491);

    if (-1==connect(sockfd, (struct sockaddr *)&address, sizeof(address)))
    {
        perror("oops:connect error!\n");
        exit(1);
    }

    char buf[128];
    int bufSize=sizeof(buf);
    sprintf(buf,"%s","hi from client!");
    write(sockfd, buf,strlen(buf));
    int readSzie;
    do{
        readSzie=read(sockfd,buf,bufSize-1);
        printf("%s\n", buf);
        buf[readSzie]='\0';
    }while(readSzie==bufSize);
    printf("client finished!\n");
    close(sockfd);
    exit(0);
}