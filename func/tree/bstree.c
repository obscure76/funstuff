#include <lheader.h>

void insert(node ** curr, int data, int level)
{
    node *temp;
    if(*curr==NULL)
    {
        temp = (node *)malloc(sizeof(node));
        temp->data=data;
        temp->level=level;
        temp->left=NULL;
        temp->right=NULL;
        *curr=temp;
        return;
    } else if ((*curr)->data>data){
        insert(&((*curr)->left), data, level+1);
    } else if ((*curr)->data<data) {
        insert(&((*curr)->right), data, level+1);
    }
}

int delete(node **curr, int data)
{
    node *temp;
    if(*curr==NULL)
        return 0;
    temp = *curr;
    if(temp->data==data)
    {
        //Root is to be deleted

        return 0;
    }
}

void bfs(node *head)
{

}
void printpr(node *head)
{
    if(!head)
    {
        return;
    } 
    if(head->left)
        printpr(head->left);
    printf("   %d %d", head->data, head->level);
    if(head->right)
        printpr(head->right);
}
void printi(node *head)
{
    if(!head)
    {
        return;
    } 
    printf("   %d %d", head->data, head->level);
    if(head->left)
        printi(head->left);
    if(head->right)
        printi(head->right);
}
void printpo(node *head)
{
    if(!head)
    {
        return;
    } 
    if(head->left)
        printpo(head->left);
    if(head->right)
        printpo(head->right);
    printf("   %d %d", head->data, head->level);
}

int main()
{
    node *head=NULL;
    int i,k=5;
    for(i=0;i<5;i++)
    {
        insert(&head, i+k, 0);
        insert(&head, i*k, 0);
        insert(&head, i-k, 0);
        insert(&head, i*(-k), 0);
    }
    printpr(head);
    printf("\n\n");
    printi(head);
    printf("\n\n");
    printpo(head);
    return 0;
}
