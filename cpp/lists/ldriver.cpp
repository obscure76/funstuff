#include<header.h>

int main()
{
    llist my_list;
    for(int i=10;i>0;i--)
    {
        my_list.lappend(i);
    }
    my_list.lprint();
    my_list.quisort();
    cout<<"\nAfter quick sort \n";
    my_list.lprint();
    return 0;
}
