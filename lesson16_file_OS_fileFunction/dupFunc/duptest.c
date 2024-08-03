#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); 
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");
    
    //先把标准输出的fd表拷贝一份.
    int stdoutfd = dup(1);

    //拷贝了stdout的fd表后,
    //可以把fdarr[fd] 拷贝到 fdarr[1] 中了
    //重定向操作
    close(1);
    dup2(fd, 1);
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");

    //重定向之后,再把预先拷贝备份好的stdoutfd表中内容拷贝回1号下标.
    close(fd);
    dup2(stdoutfd, 1);
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");
    printf("stdout\n");
    return 0;
}
