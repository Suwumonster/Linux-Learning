#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024
#define argvMax 32

void splitComd(char commandstr[], char* Argv[])
{
    int i = 0;
    Argv[0] = strtok(commandstr, " ");
    for(i = 1; i < argvMax; i++)
    {
        Argv[i] = strtok(NULL, " "); 
    }
}

void DebugTest(const char* commandstr)
{
    printf("%s\n", commandstr);

}
enum DUP
{
    dup_none = 0,
    dup_input = 1,
    dup_output = 2,
    dup_append = 3
};
int main()
{
    char myenv[32][256];
    int env_index = 0;
    int QuitCode = 0;
    int stdinFd = dup(0);
    int stdoutFd = dup(1);
    while(1)
    {
        extern char **environ;
        enum DUP dupval = dup_none;
        char commandstr[MAX] = { 0 };
        char* Argv[argvMax + 1] = { NULL };
        
        //把fd[0] fd[1] 重定向回来
        close(0);
        close(1);
        dup2(stdinFd, 0);
        dup2(stdoutFd, 1);

        printf("[mybashTest@VM-8-2-centos myshell]$ ");
        fflush(NULL);
        fgets(commandstr, MAX - 1, stdin);
        //处理\n
        int i = 0;
        for(i = 0; i < MAX - 1; i++)
        {
            if(commandstr[i + 1] == '\0')
            {
                commandstr[i] = '\0';
                break;
            }
        }
        //DebugTest(commandstr);
        splitComd(commandstr, Argv);
        //查找是否有重定向符号
        char *duparr[2] = {NULL};
        for(i = 0; Argv[i]; i++)
        {
            if(strcmp(Argv[i], "<") == 0)
            {
                dupval = dup_input;
                duparr[0] = Argv[i];
                duparr[1] = Argv[i + 1];
                Argv[i] = Argv[i + 1] = NULL;
                break;
            }
            if(strcmp(Argv[i], ">") == 0)
            {
                dupval = dup_output;
                duparr[0] = Argv[i];
                duparr[1] = Argv[i + 1];
                Argv[i] = Argv[i + 1] = NULL;
                break;
            }
            if(strcmp(Argv[i], ">>") == 0)
            {
                dupval = dup_append;
                duparr[0] = Argv[i];
                duparr[1] = Argv[i + 1];
                Argv[i] = Argv[i + 1] = NULL;
                break;
            }
        }
        //处理重定向
        int fd = -1;
        if(dupval == dup_input)
        {
            fd = open(duparr[1], O_RDONLY); 
            if(fd != -1)
            {
                close(0);
                dup2(fd, 0);
            }
        }
        else if(dupval == dup_output)
        {
            fd = open(duparr[1], O_WRONLY | O_CREAT | O_TRUNC, 0666); 
            if(fd != -1)
            {
                close(1);
                dup2(fd, 1);
            }
        }
        else if(dupval == dup_append)
        {
            fd = open(duparr[1], O_WRONLY | O_CREAT | O_APPEND, 0666); 
            if(fd != -1)
            {
                close(1);
                dup2(fd, 1);
            }
        }
        if(strcmp(Argv[0], "cd") == 0)//内建命令
        {
            if(Argv[1])
            {
                chdir(Argv[1]);
            }
            continue;
        }
        else if(strcmp(Argv[0], "env") == 0)//内建命令
        {
            for(i = 0; environ[i]; i++)
            {
                printf("%d:%s\n", i, environ[i]);
            }
            continue;
        }
        else if(strcmp(Argv[0], "export") == 0)
        {
            if(Argv[1])
            {
                if(env_index < 32)
                {
                    strcpy(myenv[env_index], Argv[1]);
                    putenv(myenv[env_index++]);
                }
            }
            continue;
        }
        else if(strcmp(Argv[0], "echo") == 0)
        {
            if(Argv[1][0] == '$')
            {
                if(Argv[1][1] == '?')
                {
                    printf("%d\n", QuitCode);
                }
                else
                {
                    char tmp[256];
                    strcpy(tmp, &Argv[1][1]);
                    printf("%s\n", getenv(tmp));
                }
            }
            else
            {
                printf("%s\n", Argv[1]);
            }
            continue;
        }
        else if(strcmp(Argv[0], "ls") == 0)
        {
            for(i = 1; Argv[i] && i < argvMax; i++)
            {

            }
            if(i < argvMax)
            {
                Argv[i] = (char*)"--color=auto";
            }
        }
        pid_t id = fork();
        if(id == 0)
        {
            //child command process
            
            execvp(Argv[0], Argv);
            exit(1);
        }
        else if(id > 0)
        {
            //parent mybash
            int status = 0;
            waitpid(id, &status, 0);
            QuitCode = status >> 8;            
        }
    }
    return 0;
}
