#include "process.h"

void process()
{
    const char* c = "/-\\|";
    char arr[103] = {'\0'};
    for(int i = 0; i <= 100; i++)
    {
        if(i > 0)
        {
            arr[i - 1] = '=';
        }
        if(i != 100)
        {
            arr[i] = '>';
        }
        printf("[%-100s][%d%%][%c]\r", arr, i, c[i%4]);
        fflush(stdout);
        usleep(100000);
    }
    printf("\n");
    return;
}
