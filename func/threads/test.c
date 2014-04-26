#include<stdio.h>

int main()
{
    int t = 5, k;
    void *p;
    p = (void *) t;
    k = (int) p;
    printf("\n %d", k);
    return 0;
}
