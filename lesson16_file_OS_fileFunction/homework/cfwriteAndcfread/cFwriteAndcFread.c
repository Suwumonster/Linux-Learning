#include <stdio.h>
#include <string.h>

int main()
{
    //FILE* f = fopen("bite", "w");
    FILE* f = fopen("bite", "r");
    if(f == NULL)
    {
        perror("fopen");
        return 1;
    }
    //const char* str = "linux so easy!\n";
    //fwrite(str, sizeof(char), strlen(str), f);
    char buff[1024] = { 0 };
    fread(buff, sizeof(char), sizeof(buff), f);
    printf("%s", buff);
    fclose(f);
    return 0;
}
