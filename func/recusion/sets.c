#include<stdio.h>
int use[4];

void print_array(int *a, int *use)
{
    int i;
    printf("\n");
    for(i=0;i<4;i++)
    {
        if(use[i]==1)
            printf("%d ", a[i]);
    }
    printf("\n");
}

int get_sets(int *a, int curr, int count, int len)
{   
    int i;
    if(0==count)
    {
        print_array(a, use);
    } else {
        if(curr<len)
        {
            use[curr]=1;
            get_sets(a, curr+1, count-1, len);
            use[curr]=0;
            get_sets(a, curr+1, count, len);
        }
    }
    return 0;
}

int main()
{
    int a[]={1,2,3,4};
    int i;
    for (i=0;i<4;i++)
    {
        use[i]=0;
    }
    for(i=1;i<4;i++)
    {
        get_sets(a, 0, i, 4);
    }
    return 0;
}

