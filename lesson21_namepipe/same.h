#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <unistd.h>
using namespace std;

#define NAMEPIPE "/home/suwu/Linux-Learning/lesson21_namepipe/fifo"
mode_t mode = 0660;

#define SERVER 0
#define CLIENT 1
#define MAX 1024 //写入和读取数据的缓冲区大小


//封装fifo文件的创建，打开，关闭和销毁
class Init
{
public:
    Init(int type): _type(type)
    {
        if(_type == SERVER)
        {
            umask(0);
            int n = mkfifo(NAMEPIPE, mode);
            if(n == -1)
            {
                cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
                exit(1);
            }
            int fd = open(NAMEPIPE, O_RDONLY);
            if(fd == -1)
            {
                cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
                exit(2);
            }
            _fd = fd;
        }
        else//client
        {
            int fd = open(NAMEPIPE, O_WRONLY | O_TRUNC);
            if(fd == -1)
            {
                cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
                exit(2);
            }
            _fd = fd;
        }
    }
    ~Init()
    {
        sleep(5);//观察fifo文件
        if(close(_fd))
        {
            cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
            exit(2);
        }
        if(_type == SERVER)
        {
            if(unlink(NAMEPIPE) == -1)
            {
                cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
                exit(3);
            }
        }
    }
    int getFd()
    {
        return _fd;
    }
private:
    int _type;
    int _fd;
};