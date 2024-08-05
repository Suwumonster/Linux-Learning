#include "mystdio.h"

int main()
{
    MYFILE* fp = myfopen("log.txt", "a");
    const char* str = "hello linux!\n";
    myfwrite(str, 1, strlen(str), fp);
    myfclose(fp);
    return 0;
}
