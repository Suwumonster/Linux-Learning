#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void myhandler(int signo)
{
    cout << "进程pid:" << getpid() << "收到" << signo << "号信号" << endl;
    exit(0);
}

int main()
{
    signal(2, myhandler);
    while(1)
    {
        cout << "进程pid:" <<getpid() <<"正在运行..." << endl;
        sleep(1);
    }
    return 0;
}
