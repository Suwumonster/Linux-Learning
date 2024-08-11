#include "same.h"

int main()
{
    //1.通过ftok获取key值
    key_t key = ftok(PATHNAME, PROJ_ID);

    //2. 打开已经server创建的shm，获取shmid
    int shmid = shmget(key, SIZE, IPC_CREAT);

    //3. shm关联进程 shmat
    char* buff = (char*)shmat(shmid, nullptr, 0);

    //4. IPC
    int cnt = 0;
    char ch = 'A';
    while(ch <= 'Z')
    {
        buff[cnt++] = ch;
        buff[cnt] = '\0';
        ch++;
        sleep(1);
    }

    //5. shm取消关联进程 shmdt
    shmdt(buff);

    return 0;
}