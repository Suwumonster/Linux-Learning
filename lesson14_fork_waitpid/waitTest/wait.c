#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int mycnt = 10;
        while(mycnt--)
        {
            printf("child, my pid is %d, father pid is %d\n", getpid(), getppid());
            sleep(1);
        }
        return 12;
    }
    else
    {
        //father
        printf("parent, my pid is %d, father pid is %d\n", getpid(), getppid());
        sleep(1);
        int status = 0;
        int ret = wait(&status);
        if(ret == -1)//wait error
        {
            printf("wait error\n");
        }
        else//success
        {
            int signal = status & 0xff;
            printf("status is %d\n", status);
            if(signal == 0)//quit process not by sys call
            {
                //only in this case, quit code is useful
                int quitCode = status >> 8;
                printf("child process normal quit, quitCode is %d\n", quitCode);
            }
            else//by sys call
            {
                int coreDump = signal >> 7 & 0x1;//coreDump
                int realSignal = signal & 0x7f;//realsignal
                printf("child process quit by sys call, sys signal is %d\n", realSignal);
            }
        }
        return 11;
    }
}
