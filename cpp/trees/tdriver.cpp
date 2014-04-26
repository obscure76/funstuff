#include<theader.h>

int main()
{
    tree my_tree;
    for(int i=0;i<5;i++)
    {
        my_tree.tinsert(i+10);
        my_tree.tinsert(i-3);
        my_tree.tinsert(i*2);
        my_tree.tinsert(i/2);
    }
    cout<<"\n In Order Traversal:\n";
    my_tree.pinorder();
    cout<<"\n Level Order Traversal:\n";
    my_tree.lorder();

    my_tree.tdelete(10);
    
    cout<<"\n Level Order Traversal after deletion of 10:\n";
    my_tree.lorder();
    cout<<"\n\n\n";
    my_tree.ppreorder();
    return 0;
}
