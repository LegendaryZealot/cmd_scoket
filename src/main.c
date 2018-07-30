#include <stdio.h>

#include "conn.h"

int main(int argc, char const *argv[])
{
    int codeTmp;
    if(0!=(codeTmp=openConn()))
    {
        printf("open error:%d\n",codeTmp);
    }
    return 0;
}
