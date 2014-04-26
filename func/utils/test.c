#include <header.h>
#include <string.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int main()
{
    int a[4], i;
    char s[10], *p;
    for(i=0;i<9;i++)
    {
        s[i]=i+'a';
    }
    s[i]='\0';
    printf("\n %s", s);
    p = strrev(s);
    printf("\n Rev is %s", p);
    return 0;
}
