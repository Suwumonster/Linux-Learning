#include "same.h"

int main()
{
    Init t(CLIENT);
    char buff[MAX] = { 0 };
    //写入
    while(cin >> buff)
    {
        if(strcasecmp("quit", buff) == 0)
        {
            cout << "结束CLIENT" << endl;
            break;
        }
        int n = write(t.getFd(), buff, strlen(buff));
        if(n == -1)
        {
            cout << "写入错误,准备结束CLIENT" << errno << "," << strerror(errno) << endl;
            break;
        }
    }
    return 0;
}