#include <stdio.h>
#include <unistd.h>


int main()
{
    pid_t ret = fork();
    if(ret == 0)
    {
        //child
        while(1)
        {
            printf("我是子进程，pid是%d，我的父进程是%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else if(ret > 0)
    {   
        //parent
        while(1)
        {
            printf("我是父进程，pid是%d，我的父进程是%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    return 0;
}
