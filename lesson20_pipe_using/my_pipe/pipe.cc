#include <iostream>
#include <cerrno>
#include <cstring>
#include <unistd.h>
using namespace std;




int main()
{
    //1.创建管道
    int pipefd[2] = { 0 };
    int n = pipe(pipefd);
    if(n == -1)
    {
        cout << "pipe error:" << strerror(errno) << endl;
        return 1;
    }
    //2. 创建父子进程
    pid_t id = fork();
    if(id == 0)
    {
        //child
        //3.关闭不需要的pipe端口
        close(pipefd[1]);
        //4.读取
        char buff[1024] = { 0 };
        read(pipefd[0], buff, sizeof(buff));
        cout << buff;
        close(pipefd[0]);
        exit(0);
    }
    //parent
    //3.关闭不需要的pipe端口
    close(pipefd[0]);
    //4.写入
    const char buff[] = "i am father\n";
    write(pipefd[1], buff, strlen(buff));
    close(pipefd[1]);
    return 0;
}
