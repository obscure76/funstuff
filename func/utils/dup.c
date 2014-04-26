#include<header.h>

void remove_dup(char *str)
{
    int j=0,i;
    char *p;
    p = str;
    for(i=1;i<18;i++)
    {
        if(str[i]!=str[i-1])
            p[++j]=str[i];
    }
    p[++j]=str[i];
}

void recursive_remove_dup(char *str, char *temp, char prev)
{
        if(str[0]=='\0')
        {
            temp[0]='\0';
            return;
        }

        if(str[0]!=prev)
        {
            temp[0]=str[0];
            temp++;
        }
        recursive_remove_dup(str+1, temp, str[0]);
}

int interleave(char *str1, char *str2, char *str3)
{
    int i=0,j=0,k=0;
    while(str3[k])
    {
        if(str3[k]==str1[i] && str3[k]==str2[j])
        {
            k++;i++;j++;
        } else if(str3[k]==str1[i]) {
            k++;i++;
        } else if(str3[k]==str2[j]) {
            k++;j++;
        } else {
            k++;
        }
    }
    if(str1[i]=='\0' && str2[j]=='\0')
    {
        printf("\n Yes");
    }
}

int main()
{
    char a[20];
    char b[20];
    char *s1="XXY", *s2="XXZ";
    char *s3="XXZXXXY";
    int i;
    for(i=0;i<17;i+=2)
    {
        a[i]='a'+i;
        a[i+1]='a'+i;
    }
    a[i]='\0';
    printf("\n%s",a);
    //remove_dup(a);
    recursive_remove_dup(a, b, '\0');
    for(i=0;b[i];i+=2)
    {
        b[i]+=9;
        b[i+1]+=9;
    }
    printf("\n%s",b);
    interleave(s1, s2, s3);
    return 0;
}
