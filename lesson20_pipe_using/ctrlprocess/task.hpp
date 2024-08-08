#pragma once
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;


#define TASK_MYSQL 0
#define TASK_PRINT 1
#define TASK_REQUEST 2

typedef void(*func)();

class childProcess
{
public:
    childProcess(pid_t id = 0, int fd = 0):_id(id), _fd(fd){}
    pid_t _id;
    int _fd;
};

void mysql_task()
{
    cout << "正在执行数据库任务..." << endl; 
}
void print_task()
{
    cout << "正在执行打印任务..." << endl; 
}
void request_task()
{
    cout << "正在执行网络请求任务..." << endl; 
}


class TASK
{
public:
    TASK()
    {
        funcs.push_back(mysql_task);
        funcs.push_back(print_task);
        funcs.push_back(request_task);
    }
    void Execute(int command)
    {
        if(0 <= command && command < funcs.size()) funcs[command]();
    }
    
    vector<func> funcs;
};