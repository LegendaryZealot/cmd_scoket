#include <stdio.h>
#include <stdlib.h>

#include "conn.h"

int main(int argc, char const *argv[])
{
    int codeTmp;
    if(0!=(codeTmp=openConn()))
    {
        printf("open error:%d\n",codeTmp);
        exit(-1);
    }
    if(0!=(codeTmp=closeConn()))
    {
        printf("close error:%d\n",codeTmp);
        exit(-1);
    }
    return 0;
}
