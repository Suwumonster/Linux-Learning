#include "same.h"



int main()
{
    //1.通过ftok获取key值
    key_t key = ftok(PATHNAME, PROJ_ID);
    umask(0);
    //2. 创建shm，获取shmid
    //shmget 的权限设置 是与flags一起做按位或操作一起的.
    int shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | mode);
    if(shmid == -1)
    {
        cerr << errno << ":" << strerror(errno) <<endl;
    }
    //3. shm关联进程shmat
    char* buff = (char*)shmat(shmid, nullptr, 0);
    //4.IPC
    int cnt = 0;
    sleep(5);
    while(cnt <= 30)
    {
        cout << "client :>" << buff << endl;
        sleep(1);
        cnt++;
    }
    //5.进程取消关联shm，shmdt
    shmdt(buff);
    //6.销毁shm
    int n = shmctl(shmid, IPC_RMID, nullptr);
    if(n == -1)
    {
        cerr << errno << ":" << strerror(errno) <<endl;
    }
    return 0;
}