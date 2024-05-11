#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int ret = fork();
    if(ret == 0)
    {
        //子进程
        while(1)
        {
            printf("我是子进程，我的pid是%d, 我的父进程pid是%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else if(ret > 0)
    {
        //父进程
        while(1)
        {
            printf("我是父进程，我的pid是%d, 我的子进程pid是%d\n", getpid(), ret);
            sleep(1);
        }
    }
    return 0;
}
