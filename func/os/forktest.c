#include<stdio.h>

int main() 
{ 
    int i, j, k;
    /*
    if((i = fork()) && (j = fork())) 
    { 
        k = fork();
    } */
    if((i =fork()) || (j = fork())) 
    { 
        k = fork();
    }
    printf("\n Hello World %d\t%d\t%d\n", i, j, k);
    return 0;
} 
