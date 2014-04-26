#include <stdio.h>
int b[9][9];
int r[9][9];
int c[9][9];

void fill_all(int (*puz)[9])
{
    int i,j, mark=0;
    int k,l, block, m;
    int r1[9][9], c1[9][9], b1[9][9];
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            r1[i][j]=puz[i][j];
            c1[i][j]=puz[j][i];
        }
    }


    block = 0;
    for(i=0;i<9;i+=3)
    {
        for(j=0;j<9;j+=3)
        {
            m=0;
        
            for(k=i;k<i+3;k++)
            {
                for(l=j;l<j+3;l++)
                {
                    b1[block][m++]=puz[k][l];
                }
            }
            block++;
        }
    }
    for(i=0;i<9;i++)
    {
        k=0;
        for(block=1;block<10;block++)
        {
            for(j=0;j<9;j++)
            {
                if(r1[i][j]==block)
                    mark = 1;
            }
            if(mark!=1)
            {
                r[i][k++]=block;
            }
                mark=0;
        }
    }

    for(i=0;i<9;i++)
    {
        k=0;mark=0;
        for(block=1;block<10;block++)
        {
            for(j=0;j<9;j++)
            {
                if(c1[i][j]==block)
                    mark = 1;
            }
            if(mark!=1)
            {
                c[i][k++]=block;
            }
                mark=0;
        }
    }
    
    for(i=0;i<9;i++)
    {
        k=0;mark=0;
        for(block=1;block<10;block++)
        {
            for(j=0;j<9;j++)
            {
                if(b1[i][j]==block)
                {
                    mark = 1;
                }
            }
            if(mark!=1)
            {
                b[i][k++]=block;
            }
            mark=0;
        }
    }
    
    /*Skip Zeros  r and c*/
    
    for(i=0;i<9;i++)
    {
        k=0;l=0;m=0;
        for(j=0;j<9;j++)
        {
            if (r[i][j]>0) 
            {
                r[i][k]=r[i][j];
                k++;
            }
            if(c[i][j]>0)
            {
                c[i][l]=c[i][j];
                l++;
            }
            if(b[i][j]>0)
            {
                b[i][m]=b[i][j];
                m++;
            }
        }
        for(block=k;block<9;block++)
        {
            r[i][block]=0;
        }
        for(block=l;block<9;block++)
        {
            c[i][block]=0;
        }
        for(block=m;block<9;block++)
        {
            b[i][block]=0;
        }
    }
}

int check_avail(int row, int col, int *val)
{
    int temp1[9], temp2[9]; 
    int i,j,k=0, block;

    block = 3*(row/3)+col/3;
    if(b[block][0]>0 && b[block][1]==0)
    {
        *val=b[block][0];
        return 1;
    }
    if(r[row][0]>0 && r[row][1]==0)
    {
        *val=r[row][0];
        return 1;
    }
    if(c[col][0]>0 && c[col][1]==0)
    {
        *val=c[col][0];
        return 1;
    }

    for(i=0;i<9;i++)
    {
        temp1[i]=temp2[i]=0;
    }
    for(i=0,j=0;i<9&&j<9;)
    {
        if(r[row][i]==c[col][j])
        {
            temp1[k]=r[row][i];
            i++;j++;k++;
        } else if(r[row][i]>c[col][j]) {
            j++;
        } else {
            i++;
        }
    }
    block = 3*((row)/3)+(col)/3;
    k=0;
    for(i=0,j=0;i<9&&j<9;)
    {
        if(b[block][j]>0 && temp1[i]>0 && temp1[i]==b[block][j])
        {
            temp2[k]=temp1[i];
            i++;j++;k++;
        } else if(temp1[i]>b[block][j]) {
            j++;
        } else {
            i++;
        }
    }
    if(k==1)
    {
        *val = temp2[0];
        return 1;
    } else {
        return 0;
    }
}

void update_all(int row, int col, int val)
{
    int i,j=0, block;

    for(i=0;i<9;i++)
    {
        if(r[row][i]==val)
        {
            break;
        }
    }
    for(;i<8;i++)
    {
        r[row][i]=r[row][i+1];
    }

    for(i=0;i<9;i++)
    {
        if(c[col][i]==val)
        {
            break;
        }
    }
    for(;i<8;i++)
    {
        c[col][i]=c[col][i+1];
    }
    block = 3*((row)/3)+(col)/3;
    j=0;
    for(i=0;i<9;i++)
    {
        if(b[block][i]==val)
        {
             break;
        }
    }
    for(;i<8;i++)
    {
        b[block][i]=b[block][i+1];
    }
}

int main()
{
    int puz[9][9] = {{3,0,0,0,0,0,9,0,0},
                     {2,6,0,3,0,0,0,0,0},
                     {0,0,4,0,7,0,0,3,2},
                     {0,2,5,0,1,0,0,6,0},
                     {7,3,9,0,0,0,2,5,1},
                     {0,1,0,0,2,0,3,4,0},
                     {8,9,0,0,5,0,6,0,0},
                     {0,0,0,0,0,8,0,1,3},
                     {0,0,2,0,0,0,0,0,8}};
    int count=0, i, j, res, val, moves=0;
    fill_all(puz);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(puz[i][j]>0)
                count++;
        }
    }

    printf("\n\n init count %d\n\n", count);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", puz[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");
        printf("\n");
        /*
        printf("\n block\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", b[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");
        printf("\n row\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", r[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");
        printf("\n col\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", c[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */
    while(count<81 && moves<50)
    {
        moves++;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(puz[i][j]==0)
                {
                    res = check_avail(i, j, &val);
                    if (res ==1)
                    {
                        puz[i][j]=val;
                        update_all(i, j, val);
                        count++;
                    }
                }
            }
        }
    }
    
    /* 
        printf("\n block\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", b[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");
        
        printf("\n row\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", r[i][j]);
        }
        printf("\n");
    }
        printf("\n");
        printf("\n");
        printf("\n col\n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", c[i][j]);
        }
        printf("\n");
    }*/
    printf("\n\n puzzle \n");
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            printf("%d   ", puz[i][j]);
        }
        printf("\n");
    }
    return 0;
}

