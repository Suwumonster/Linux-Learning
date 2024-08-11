#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

void myhandler(int signo)
{
    cout << "进程pid:" << getpid() << "收到" << signo << "号信号" << endl;
}

int main()
{
    //signal(9, myhandler); //9号信号不能被自定义动作捕捉, 1-31 号的其余信号可以
    //kill(getpid(), 9); //kill系统调用向指定进程pid,发送对应信号

    // signal(3, myhandler);
    // raise(3); //向当前进程发送对应信号

    // signal(6, myhandler);
    // cout << "--------" << endl;
    // abort();//6号信号  6号信号虽然可以被自定义动作捕捉，但动作完成后还是会结束当前进程
    // cout << "--------" << endl;
    
    // alarm(10);//14号信号 , 收到后 在 seconds秒后关闭当前进程, 
    // //如果倒计时内,又接受到一个新的14号信号，返回值就是剩余的秒数
    // int s = 10;
    // while(1)
    // {
    //     cout << "倒计时:" << s-- << endl;
    //     sleep(1);
    // }
    
    return 0;
}