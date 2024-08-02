//文件操作—系统方案
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define LOG "log.txt"
void clearWrite()
{
    umask(0);
    int fd = open(LOG, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1)
    {
        printf("errno:%d, strerror: %s\n", errno, strerror(errno));
        return ;
    }
    printf("errno:%d, strerror: %s\n", errno, strerror(errno));

    const char* buff = "abcd";
    int i = 0;
    char str[1024];
    for(i = 0; i < 3; i++)
    {
        snprintf(str, sizeof(str), "%d: %s\n", i + 1, buff);
        write(fd, str, strlen(str));
    }

    close(fd);
}

void appendWrite()
{
    umask(0);
    int fd = open(LOG, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if(fd == -1)
    {
        printf("errno:%d, strerror: %s\n", errno, strerror(errno));
        return ;
    }
    printf("errno:%d, strerror: %s\n", errno, strerror(errno));

    const char* buff = "HELLO";
    int i = 0;
    char str[1024];
    for(i = 0; i < 3; i++)
    {
        snprintf(str, sizeof(str), "%d: %s\n", i + 1, buff);
        write(fd, str, strlen(str));
    }

    close(fd);
}
void OSread()
{
    int fd = open(LOG, O_RDONLY);
    if(fd == -1)
    {
        printf("errno:%d, strerror: %s\n", errno, strerror(errno));
        return;
    }
    printf("errno:%d, strerror: %s\n", errno, strerror(errno));

    char str[1024] = { 0 };
    read(fd, str, sizeof(str));
    printf("%s", str);

    close(fd);
}
int main()
{
    OSread();
    return 0;
}


//文件操作——C语言方案
//#include <stdio.h> 
//#include <string.h>
//#define LOG "log.txt"
//
////清空文件写入
//void clearWrite()
//{
//    FILE* file = fopen(LOG, "w");
//    if(file == NULL)
//    {
//        perror("fopen");
//    }
//    const char* buff = "abcd";
//    int i = 0;
//    char str[1024];
//    for(i = 0; i < 1; i++)
//    {
//        snprintf(str, sizeof(str), "%d: %s\n", i + 1, buff);
//        fwrite(str, sizeof(char), strlen(str), file); 
//    }
//    fclose(file);
//}
//
//void appendWrite()
//{
//    FILE* file = fopen(LOG, "a");
//    if(file == NULL)
//    {
//        perror("fopen");
//    }
//    const char* buff = "hello Linux OS, hello file";
//    int i = 0;
//    char str[1024];
//    for(i = 0; i < 1; i++)
//    {
//        snprintf(str, sizeof(str), "%d: %s\n", i + 1, buff);
//        fwrite(str, sizeof(char), strlen(str), file); 
//    }
//    fclose(file);
//
//}
//void fileRead()
//{
//    FILE* file = fopen(LOG, "r");
//    if(file == NULL)
//    {
//        perror("fopen");
//    }
//    char buff[1024] = { 0 };
//    while(fgets(buff, 1023, file))
//    {
//        printf("%s", buff);
//    }
//    fclose(file);
//}
//
//int main()
//{   
//    fileRead();
//    return 0;
//}
