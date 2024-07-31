#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("program ready to turn to ls!\n");
    execlp("ls", "ls", "-l", "-a", NULL);
    return 0;
}
