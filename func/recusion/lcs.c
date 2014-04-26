#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int a, int b)
{
    if(a>b)
        return a;
    return b;
}
int lcs(char *a, char*b, int lena, int lenb)
{
    if(lena==0 || lenb==0)
        return 0;
    if(a[lena]==b[lenb])
        return 1 + lcs(a, b, lena-1, lenb-1);
    else {
        return max(lcs(a, b, lena, lenb-1), lcs(a,b, lena-1, lenb));
    }
}


int main()
{
    char *a="GeeksforGeeks", *b="GeeksQuiz";
    printf(" b  %d", strlen(b)); 
    printf("  %d", lcs(a,b, strlen(a), strlen(b)));
}
