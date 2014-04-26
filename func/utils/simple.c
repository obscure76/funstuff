#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *a;
    a = malloc(10);
    printf("\n %d", sizeof(*a));
    return 0;
}
