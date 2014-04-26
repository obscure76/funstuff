#include<stdio.h>

char b[]={'d','e','f','g','h'};
int count=0;
void print_array(int *a)
{
    int i;
    count++;
    for(i=0;i<5;i++)
        printf(" %d", a[i]);
    printf("    ");
    if(count%3==0)
        printf("\n");
}

void swap(int *a, int left, int right)
{
    int temp;
    temp = a[left];
    a[left]=a[right];
    a[right]=temp;
}

void perm_sorted(int *a, int left, int right)
{
    int k;
    int temp,i;
    if(left==right)
    {
        print_array(a);
    } else {
        for (k=left;k<=right;k++)
        {
            if(k==left)
            {
                swap(a, left, k);
                perm_sorted(a, left+1, right);
                swap(a, left, k);
            } else if(a[left]!=a[k]){
                swap(a, left, k);
                temp=a[k];
                for(i=k;i>left+1;i--)
                {
                    a[i]=a[i-1];
                }
                a[left+1]=temp;
                perm_sorted(a, left+1, right);
                temp=a[left+1];
                for(i=left+1;i<k;i++)
                {
                    a[i]=a[i+1];
                }
                a[k]=temp;
                swap(a, left, k);
            }
        }
    }
}

void perm(int *a, int left, int right)
{
    int k;
    int temp,i;
    if(left==right)
    {
        print_array(a);
    } else {
        for (k=left;k<=right;k++)
        {
            swap(a, left, k);
            perm(a, left+1, right);
            swap(a, left, k);
        }
    }
}

int main()
{
    int i;
    int a[5];
    for(i=0;i<5;i++)
        a[i]=i;
    //perm_sorted(a, 0, 4);
    perm(a,0,2);
    return 0;
}
