#include "mystdio.h"

MYFILE* myfopen(const char *path, const char *mode)
{
    //1.申请MYFILE对象
    MYFILE* fp = (MYFILE*)malloc(sizeof(MYFILE));
    if(fp == NULL)
    {
        return NULL;
    }
    //2.调用系统接口打开文件
    int fd = -1;
    if(strcmp(mode, "w") == 0)
    {
        fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    }
    else if(strcmp(mode, "r") == 0)
    {
        fd = open(path, O_RDONLY);
    }
    else if(strcmp(mode, "a") == 0)
    {
        fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
    }
    else{
        //other mode 
    }
    if(fd == -1)
    {
        free(fp);//打开文件失败释放申请好的对象
        return NULL;
    }
    //3.给MYFILE对象赋值/初始化
    fp->fd = fd;
    fp->flag = FLUSH_LINE;
    memset(fp->buff, '\0', sizeof(fp->buff));
    fp->cur = 0;
    return fp;
}

int myfflush(MYFILE* fp)
{
    //1.把用户层的缓冲区刷给内核层的缓冲区
    write(fp->fd, fp->buff, fp->cur);
    fp->cur = 0;
    //2.把内核层的缓冲区刷新给对应文件
    fsync(fp->fd); 
    return 0;
}
int myfclose(MYFILE* fp)
{
    //1.缓冲区还有数据冲刷给对文件
    if(fp->cur != 0)
    {
        myfflush(fp);
    }
    //2.关闭文件
    close(fp->fd);
    //3.释放文件对象
    free(fp);
    return 0;
}
//size_t myfread(void *ptr, size_t size, size_t nmemb, MYFILE *fp)
//{
//}
size_t myfwrite(const void *ptr, size_t size, size_t nmemb, MYFILE *fp)
{
    //1.缓冲区满，刷给文件
    if(fp->cur == MAX)
    {
        myfflush(fp);
    }
    //2.写入
    size_t writebyte = size * nmemb;
    size_t restbyte = (MAX - fp->cur) / size * size;
    size_t ret = 0;
    if(writebyte > restbyte)
    {
       memcpy(fp->buff, ptr, restbyte);
       ret = restbyte / size;
    }
    else
    {
       memcpy(fp->buff, ptr, writebyte);
       ret = writebyte / size;
    }
    fp->cur += ret * size;
    //3.根据刷新策略进行缓冲区刷新
    if(fp->flag == FLUSH_NONE)
    {
        myfflush(fp);
    }
    else if(fp->flag == FLUSH_LINE)
    {
        if(fp->buff[fp->cur] == '\n')
        {
            myfflush(fp);
        }
    }
    else if(fp->flag == FLUSH_ALL)
    {
        if(fp->cur == MAX)
        {
            myfflush(fp);
        }
    }
    return ret;
}
