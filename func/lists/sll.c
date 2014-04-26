#include <lheader.h>

int insert(snode **head, int data)
{
    snode *temp, *curr;
    temp = malloc(sizeof(snode));
    temp->data = data;
    curr = *head;
    if(*head == NULL)
    {
        temp->next = NULL;
       *head = temp;
    } else {
        if(curr->data > data)
        {
            /* insert to the head of the list */
            temp->next=*head;
            *head = temp;
            return 0;
        }
        while(curr->next && curr->next->data < data)
        {
            curr=curr->next;
        }
        /* insert at the curr position of head */
        temp->next = curr->next;
        curr->next =  temp;
    }
    return 0;
}

int delete(snode **head, int data)
{
    snode *curr, *del;
    curr = *head;
    if(!*head)
        return 0;
    if(curr->data == data)
    {
        /* delete the head */
        del = curr;
        *head = curr->next;
        free(del);
        del = NULL;
        return 0;
    }
    while(curr->next && curr->next->data != data)
    {
        curr = curr->next;
    }
    if(curr && curr->next)
    {
        del = curr->next;
        curr->next = curr->next->next;
        free(del);
        del = NULL;
    }
    return 0;
}

snode* search(snode *head, int data)
{
    if(!head)
        return NULL;
    while(head)
    {
        if(head->data == data)
        {
            printf("\nData found");
            return NULL;
        }
    }
    return NULL;
}

void printsll(snode *head)
{
    if(!head)
        return;
    while(head)
    {
        printf("\n %d \t", head->data);
        head=head->next;
    }
}

int main()
{
    snode *sllhead = NULL;
    int i;

    for(i=0;i<10;i++)
    {
        insert(&sllhead, 10-i);
    }
    
    printsll(sllhead);

    printf("\n printed list");
delete(&sllhead, 5);
    delete(&sllhead, 11);
    /*
    
    delete(&sllhead, 0);*/
    
    printsll(sllhead);

    search(sllhead, 6);
    return 0;
}
