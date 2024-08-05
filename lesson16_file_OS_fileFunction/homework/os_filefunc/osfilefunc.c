#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    //int fd = open("bite", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    int fd = open("bite", O_RDONLY);
    //const char* str = "i like linux!\n";
    //write(fd, str, strlen(str));
    char buff[1024] = { 0 }; 
    read(fd, buff, sizeof(buff));
    printf("%s", buff);
    close(fd);
    return 0;
}
