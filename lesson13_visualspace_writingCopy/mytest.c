#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int galval = 100;
int main()
{
    pid_t pid = fork();
    assert(pid >= 0);
    if(pid == 0)
    {
        //child
        while(1)
        {
            printf("我是子进程，pid是%d，父进程是%d,galval=%d,galval地址=%p\n", getpid(), getppid(), galval, &galval);
            sleep(1);
            galval = 200;
        }
    }
    else
    {
        //father
        while(1)
        {
            printf("我是父进程，pid是%d，父进程是%d,galval=%d,galval地址=%p\n", getpid(), getppid(), galval, &galval);
            sleep(1);
        }
    }
    return 0;
}
