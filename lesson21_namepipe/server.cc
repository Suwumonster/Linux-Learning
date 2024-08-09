#include "same.h"

int main()
{
    Init t(SERVER);
    char buff[MAX] = { 0 };
    while(1)
    {
        int n = read(t.getFd(), buff, sizeof(buff) - 1);
        if(n == -1)
        {
            cerr << "error, errno:" << errno  << ", reason:" << strerror(errno) << endl;
            break;
        }
        else if(n == 0)
        {
            cout << "读完了, 准备结束SERVER" << endl;
            break;
        }
        else
        {
            buff[n] = '\0';
            cout << "client :> " << buff << endl;
        }
    }
    return 0;
}