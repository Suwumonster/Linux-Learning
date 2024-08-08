#include "task.hpp"

#define childNUM 3


int main()
{
    childProcess cp[childNUM];
    TASK t;
    for(int i = 0; i < childNUM; i++)
    {
        //1.创建管道
        int pipefd[2] = { 0 };
        pipe(pipefd);
        //2.创建子进程
        pid_t id = fork();
        if(id == 0)
        {
            //3.子进程关闭不需要的端口 --- 写端
            close(pipefd[1]);
            while(true)
            {
                int command = -1;
                int n = read(pipefd[0], &command, sizeof(int));
                if(n == sizeof(int) && command != -1)
                {
                    cout << "pid:" << getpid() << "任务:";
                    t.Execute(command);
                }
                else if(n == -1)
                {
                    cout << "pid:" << getpid() << "读异常" << endl;
                    break;
                }
                else if(n == 0)
                {
                    cout << "pid:" << getpid() << "读完毕" << endl;
                    break;
                }
            }
            sleep(10);
            close(pipefd[0]);
            exit(0);
        }
        //3. 父进程关闭不需要的端口 --- 读端
        close(pipefd[0]);

        //4. 记录写端端口和子进程pid, 为了后续数据回收和写入的开展
        cp[i]._id = id;
        cp[i]._fd = pipefd[1];
    }
    //给子进程分配任务
    while(true)
    {
        int command = rand() % t.funcs.size();
        int selectchild = rand() % childNUM;
        write(cp[selectchild]._fd, &command, sizeof(int));
        sleep(1);
    }

    //关闭父进程所有的写端
    for(int i = 0; i < childNUM; i++)
    {
        close(cp[i]._fd);
    }
    return 0;
}