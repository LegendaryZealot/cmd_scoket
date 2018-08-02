#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(3!=argc)
    {
        printf("cmd ip port");
        return 0;
    }
    int sockfd;
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(argv[1]);
    address.sin_port = htons(atoi(argv[2]));

    if (-1==connect(sockfd, (struct sockaddr *)&address, sizeof(address)))
    {
        perror("oops:connect error!\n");
        return -1;
    }

    char buf[128];
    sprintf(buf,"%s","hi from client!");
    int writeCount=write(sockfd, buf,strlen(buf));
    close(sockfd);
    printf("buf size:%ld,write:%d\n",strlen(buf),writeCount);
    return 0;
}