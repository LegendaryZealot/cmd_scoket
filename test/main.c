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
    struct sockaddr_in address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(3491);

    if (-1==connect(sockfd, (struct sockaddr *)&address, sizeof(address)))
    {
        perror("oops:connect error!\n");
        return -1;
    }

    char buf[128];
    sprintf(buf,"%s","hi from client!");
    write(sockfd, buf,strlen(buf));
    close(sockfd);
    return 0;
}