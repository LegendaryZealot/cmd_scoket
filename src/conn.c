#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>

#include "conn.h"
#include "sock.h"

#define BUFFER_SIZE 128

extern AcceptCallback acceptCallBack;

void AcceptCallbackHandle(int sock);
void *AcceptCallbackHandleThread(void *sock);

int openConn()
{
    acceptCallBack=AcceptCallbackHandle;
    if(0!=getServerScok())
    {
        return -1;
    }
    if(0!=runServerSock())
    {
        return -2;
    }
    return 0;
}

int closeConn()
{
    return closeServerSock();
}

void AcceptCallbackHandle(int sock)
{
    pthread_t *my_thread;
    int err;
    if(0!=(err=pthread_create((pthread_t *)&my_thread,NULL,AcceptCallbackHandleThread,(void *)&sock)))
    {
        printf("accept callback thread create error,code:%d\n",err);
    }
}

void *AcceptCallbackHandleThread(void *sock)
{
    int sockfd=*(int *)sock;
    int recv_length=-1;
    char buf[BUFFER_SIZE];
    do
    {
        memset(buf,'\0',BUFFER_SIZE);
        recv_length=recv(sockfd,buf,BUFFER_SIZE,0);
        printf("%s\n",buf);
    }while(recv_length==BUFFER_SIZE);
    memset(buf,'\0',BUFFER_SIZE);
    sprintf(buf,"%s","hi from server");
    send(sockfd,buf,strlen(buf),0);
    close(sockfd);
}