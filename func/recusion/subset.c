#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int use[4];
void print_array(int* a)
{
    int i;
    for(i=0;i<4;i++)
    {
        if(use[i] == 1)
        {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}

void find_subset(int *a, int n, int size, int curr, int start)
{
    int i;
    if(curr == size)
    {
        print_array(a);
        return;
    } else {
        for(i=start;i<(n);i++)
        {
            if(use[i] == 0)
            {
                use[i]=1;
                find_subset(a, n, size, curr+1, i+1);
                use[i]=0;
            }
        }
    }
}


int main()
{
    int a[] = {1, 2, 3 ,4};
    int i, j =0;
    for(i=0;i<4;i++)
    {
        use[i]=0;
    }

    for(i=1;i<=4;i++)
    {
        find_subset(a, 4, i, j, 0);
    }
    return 0;
}
