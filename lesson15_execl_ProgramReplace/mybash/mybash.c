#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
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
int main()
{
    char myenv[32][256];
    int env_index = 0;
    int QuitCode = 0;
    while(1)
    {
        extern char **environ;

        char commandstr[MAX] = { 0 };
        char* Argv[argvMax + 1] = { NULL };

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
        if(strcmp(Argv[0], "cd") == 0)//内建命令
        {
            if(Argv[1])
            {
                chdir(Argv[1]);
            }
            continue;
        }
        
        if(strcmp(Argv[0], "env") == 0)//内建命令
        {
            for(i = 0; environ[i]; i++)
            {
                printf("%d:%s\n", i, environ[i]);
            }
            continue;
        }
        
        if(strcmp(Argv[0], "export") == 0)
        {
            if(Argv[1])
            {
                if(env_index < 32)
                {
                    strcpy(myenv[env_index], Argv[1]);
                    putenv(myenv[env_index]);
                }
            }
            continue;
        }
        if(strcmp(Argv[0], "echo") == 0)
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
        if(strcmp(Argv[0], "ls") == 0)
        {
            for(i = 1; Argv[i] && i < argvMax; i++)
            {

            }
            if(i < argvMax)
            {
                Argv[i] = "--color=auto";
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
