#include <lheader.h>

void push(snode **curr, int data)
{
    snode *temp;
    temp=(snode*) malloc(sizeof(snode));
    temp->data=data;
    if(*curr==NULL)
    {
        temp->next=NULL;
        *curr=temp;
    } else {
        temp->next=*curr;
        *curr=temp;
    }
}
 
int pop(snode **curr)
{
    snode *temp;
    int data;
    if(*curr==NULL)
        return 0;
    temp = *curr;
    *curr=temp->next;
    data = temp->data;
    free(temp);
    temp=NULL;
    return data;
}

void enqueue(qnode **head, qnode **tail, int data)
{
    qnode *temp;
    temp=(qnode*) malloc(sizeof(qnode));
    temp->data=data;
    if(*head==NULL)
    {
        temp->next=NULL;
        *head=temp;
        *tail=temp;
    } else {
        temp->next=NULL;
        (*tail)->next=temp;
        *tail=temp;
    }
}

int dequeue(snode **curr, snode *tail)
{
    snode *temp;
    int data;
    if(!*curr)
        return -1;
    temp = *curr;
    data = temp->data;
    *curr = temp->next;
    free(temp);
    temp = NULL;
    return data;
}

void prints(snode* top)
{
    while(top)
    {
        printf("\t %d", top->data);
        top=top->next;
    }
}

void printq(qnode* top)
{
    while(top)
    {
        printf("\t %d", top->data);
        top=top->next;
    }
}

int main()
{
    snode *top = NULL;
    qnode *qhead = NULL, *qtail = NULL;
    int i;
    for(i=0;i<10;i++)
    {
        push(&top, i);
        enqueue(&qhead, &qtail, i);
    }
    prints(top);
    printf("\n\n");
    printq(qhead);
    return 0;
}
