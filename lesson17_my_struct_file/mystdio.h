#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 1024
typedef enum FLUSH
{
    FLUSH_NONE = 0,
    FLUSH_LINE,
    FLUSH_ALL
}FLUSH;
typedef struct MY_FILE
{
    int fd;//文件描述符
    char buff[MAX];//缓冲区
    FLUSH flag;//刷新策略
    int cur;
}MYFILE;

MYFILE* myfopen(const char *path, const char *mode);
int myfclose(MYFILE* fp);
size_t myfread(void *ptr, size_t size, size_t nmemb, MYFILE *fp);
size_t myfwrite(const void *ptr, size_t size, size_t nmemb, MYFILE *fp);
