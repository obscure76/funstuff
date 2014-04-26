#include <stdio.h>

int main()
{
    int i, j;

    if((i= fork()) && (j=fork()))
        printf("\n Both valid ya\n");
    else if (i)
        printf("\n 1 valid ya\n");
    else if (j)
        printf("\n 2 valid ya \n");
    else 
        printf("\n None valid ya\n");
    return 0;

}
