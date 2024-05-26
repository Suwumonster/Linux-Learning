#include <stdio.h>
#include <stdlib.h>

int main()
{
    char* mypwd = NULL;
    mypwd = getenv("PWD");
    printf("%s\n", mypwd);
    return 0;
}
