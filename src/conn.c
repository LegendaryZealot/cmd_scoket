#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include "conn.h"
#include "sock.h"
#include "gpio.h"

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
    if(0<fork())
    {
        printf("sockfd%d\n",sock);
        int recv_length=-1;
        char buf[BUFFER_SIZE];
        do
        {
            memset(buf,'\0',BUFFER_SIZE);
            recv_length=recv(sock,buf,BUFFER_SIZE,0);
            if(recv_length<=0)
            {
                printf("sockfd:%d,recv code:%d,error:%s,errno:%d\n",sock,recv_length,strerror(errno),errno);
                close(sock);
                exit(0);
            }
            printf("sockfd:%d,recv:%d,%s\n",sock,recv_length,buf);
            int left,right;
            sscanf(buf,"%d %d",&left,&right);
            SetCarWheel(left,right);
        }while(1);
    }
}