#include<header.h>

int row[8], col[8];

void print()
{
    int i;
    for(i=0;i<8;i++)
    {
        printf("\n For row %d  the col %d ", i, col[i]);
    }
}

bool check(int index)
{
    int diff;
    int i;
    for (i = 0; i < index; i++) {
                
        diff = (col[i] - col[index]);
        if(diff<0)
            diff*=-1;    
        if (diff == 0 || diff == index - i) 
            return false;
            
    }
    return true;
}

void place_q(int total)
{
    int i;
    if(total==8)
    {   
        print();
        exit(0);
        return;
    }
    for(i=0;i<8;i++)
    {
        col[total]=i;
        if(check(total))
        {
            place_q(total+1);
        }
    }
}

int main()
{
    int i;

    for(i=0;i<8;i++)
    {
        row[i]=col[i]=-1;
    }
    place_q(0);
}

