#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        int mycnt = 10;
        while(mycnt)
        {
            printf("child, pid = %d, ppid = %d, restSecond %d s\n", getpid(), getppid(), mycnt);
            sleep(1);
            mycnt--;
        }
        return 2;
    }
    else
    {
        //father
        printf("father, pid = %d, ppid = %d\n", getpid(), getppid());
        while(1)//WNOHANG
        {
            int status = 0;
            int ret = waitpid(id, &status, WNOHANG);
            if(ret == -1)//waitpid error
            {
                printf("waitpid error\n");
                exit(-1);
            }
            else if(ret == 0)//child process is not done.do smt else.
            {
                printf("child process is not done.do smt else\n");
                sleep(1);
                continue;
            }
            else//child process done its work.father process print quitCode and sys signal
            {
                int signal = status & 0xff;
                if(signal == 0)//child quit normally
                {
                    //only in this case, quitCode is useful
                    int quitCode = status >> 8;
                    printf("child process(pid = %d) quit normally, quitCode is %d\n", id, quitCode);
                }
                else//child quit by sys signal
                {
                    int coreDump = signal >> 7;
                    int realSignal = signal & 0x7f;
                    printf("child process(pid = %d) quit by sys signal, signal is %d\n", id, realSignal);
                }
                exit(3);
            }
        }
    }
}
