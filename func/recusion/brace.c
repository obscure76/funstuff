#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(char *s)
{
    printf("%s\n", s);
}

void find_comb(char *s, int open_a, int close_a, int open_u, int close_u, int total, int start)
{
    if(open_u+close_u == total)
    {
        s[total]='\0';
        print_array(s);
        return;
    }
    else 
    {
        if(open_a > 0 && open_u <= 3)
        {
            // use (
            s[start]='(';
            open_u++;
            open_a--;
            find_comb(s, open_a, close_a, open_u, close_u, total, start+1);
            open_u--;
            open_a++;
        }
        if((open_u > close_u)&& open_u >0)
        {
            // use )
            s[start]=')';
            close_u++;
            close_a--;
            find_comb(s, open_a, close_a, open_u, close_u, total, start+1);
            close_u--;
            close_a++;
        }
    }
}

int main()
{
    char *s;
    s = malloc(7);
    memset(s, 0, 7);
    find_comb(s, 3, 3, 0, 0, 6, 0);
    return 0;
}
