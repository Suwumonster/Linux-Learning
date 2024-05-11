#include <stdio.h>

int addtotop(int n)
{
    int i = 0;
    int sum = 0;
    for(i = 0; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    int n = 100;
    int sum = addtotop(n);
    printf("%d\n", sum);
    return 0;
}
