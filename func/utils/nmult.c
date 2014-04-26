#include<stdio.h>

char *partial_prod(char *num, char *p)
{
}

char *add_to_partial_prod(char *sum, char *partial_prod)
{
}

void reverse(char *str)
{
    int len, i;
    char temp;
    len = strlen(len);
    for(i=0;i<len/2;i++)
    {
        temp=*(str+i);
        *(str+i)=*(str+len-1-i);
        *(str+len-1-i)=temp;
    }
}

int main(int argc, int**argv)
{
    char *str1, *str2;
    int l1,l2;
    char sum[100], temppro[100];
    
    if(argc<2)
    {
        printf("\n Use ./a.out   <num1>   <num2>   :\n");
        exit(1);
    }
    str1=argv[1];
    str2=argv[2];
        
}
