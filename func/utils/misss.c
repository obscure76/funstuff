#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>

bool bit_at(int n, int pos)
{
    return ((n>>pos) & 1);
}

int find_missing(int a[], int n)
{
    int  missing = 0;
    int i,j,k=0,l=0,p=1,one=0, zero=0, len =0;
    char ones[6], zeros[6], *indexes;
    indexes = malloc(7);
    memset(indexes, 0 , 7);
    for(i=0;i<6;i++)
    {
        ones[i]=0;
        zeros[i]=0;
        indexes[i]=i+'0';
    }
    indexes[i]='\0';
    for(i=0;i<3;i++)//For each bit
    {
        //find num of ones and zeros at each i
        len = strlen(indexes);
        for(j=0;j<len;j++)
        {
           if(bit_at(a[indexes[j]-'0'], i))
           {
               one++;
               ones[k++]=indexes[j]; 
           } else {
               zero++;
               zeros[l++]=indexes[j];
           }
        }
        ones[k]='\0';
        zeros[l]='\0';
        printf(" \n ones %d     zeros %d\n", one, zero);
        printf(" \n oneindexes %s     zeroindexes %s\n", ones, zeros);
        if(one >= zero)
        {
            missing |= (1<<i);
            printf("\n  zero missing %d\n\n", missing);
            //Eliminate num with lsb 1
            memset(indexes, 0, 7);
            strncpy(indexes, zeros, l);
        } else {
            //eliminate num eith lsb 0
            memset(indexes, 0, 7);
            strncpy(indexes, ones, k);
        }
        one=0;zero=0;
        memset(zeros, 0 , 6);l=0;
        memset(ones, 0 , 6);k=0;
    }
}

int main()
{
    int a[] = {1, 2, 4, 5, 6, 7};
    printf("The missing num is %d", find_missing(a, 6));

    return 0;
}

