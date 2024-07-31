#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t id = fork();
    if(id == 0)
    {
        //child
        printf("i am child process\n");
        sleep(5);
        _exit(11);
    }
    else if(id > 0)
    {
        //parent
        int status = 0;
        if(waitpid(id, &status, 0) > 0)
        {
            int coredump = status & 0x80;
            int signal = status & 0x7f;
            int QuitCode = status >> 8;
            printf("coredump: %d, signal: %d, QuitCode: %d\n", coredump, signal, QuitCode);
        }
        else{
            printf("child process quit fail!\n");
        }
    }
    return 0;
}
