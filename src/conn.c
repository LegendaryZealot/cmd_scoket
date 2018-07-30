#include "conn.h"
#include "sock.h"

extern AcceptCallback acceptCallBack;

void AcceptCallbackHandle(int sock);

int openConn()
{
    if(0!=getServerScok())
    {
        return -1;
    }
    if(0!=runServerSock())
    {
        return -2;
    }
    acceptCallBack=AcceptCallbackHandle;
    return 0;
}

int closeConn()
{
    return closeServerSock();
}

void AcceptCallbackHandle(int sock)
{
    
}