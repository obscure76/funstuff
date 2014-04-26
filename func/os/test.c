#include <stdio.h>

int main()
{
    int i = fork(), j = fork();
    printf("%d\t%d\n\n",i, j);
    return 0;
}
