#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a, int b, int c)
{
    if(a>b)
    {
        if(a>c)
            return a;
        else 
            return c;
    } else {
        if(b>c)
            return b;
        else
            return c;
    }
}

int palindrome(char *str, int start, int end, int in, int *curr, int *max)
{
    int temp;
    if(start==end-1)
    {
        if(in)
        {
            if (str[start]==str[end-1])
            {
                temp = (*curr);
                temp++;
                (*curr)=temp;
                if(*max<*curr)
                    *max=*curr;
            }
            return 0;
        } else {
            if (str[start]==str[end-1])
            {
                temp = (*curr);
                temp++;
                (*curr)=temp;
                if(*max<*curr)
                    *max=*curr;
            }
            return 0;
        }
    } else if(start==end)
    {
        temp = (*curr);
        temp++;
        (*curr)=temp;
        if(*max<*curr)
           *max=*curr;
        return 0;
    }
    if(str[start]!=str[end])
    {
        *curr=0;
        palindrome(str, start, end-1, 0, curr, max);
        palindrome(str, start+1, end, 0, curr, max);
    } else {
        if(in)
        {
            temp = (*curr);
            temp++;
            (*curr)=temp;
            palindrome(str, start+1, end-1, 1, curr, max);
        }
    }
}

int main()
{
    char *str="forgeeksskeegfor";
    char pal[20];
    int curr=0, i, max=0;
    for(i=0;i<20;i++)
        pal[i]='\0';
    printf("%d",palindrome(str,0,strlen(str),0, &curr, &max));
    printf("\n %d  %d", curr, max);
    return 0;
}
