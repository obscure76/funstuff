#include <header.h>

list_element * traverse(list_element *curr)
{
    if(!curr)
        return NULL;
    while(curr->next)
        curr = curr->next;
    return curr;
}

void merge(leptr *l1, leptr *l2)
{
    leptr iter1, iter2, thead, temp, prev = NULL;
    iter1 = *l1;
    iter2 = *l2;
    while(iter1 && iter2)
    {
        if(iter1->data<iter2->data)
        {
            temp = iter1->next;
            if(!prev)
            {
                prev = iter1;
                thead = prev;
            } else {
                prev->next = iter1;
                prev=prev->next;
            }
            iter1 = temp;
        } else {
            temp = iter2->next;
            if(!prev)
            {
                prev = iter2;
                thead = prev;
            } else {
                prev->next = iter2;
                prev = prev->next;
            }
            iter2 = temp;
        }
    }

    while(iter1)
    {
        temp = iter1->next;
        prev->next = iter1;
        prev = prev->next;
        iter1=temp;
    }
    while(iter2)
    {
        temp = iter2->next;
        prev->next = iter2;
        prev = prev->next;
        iter2=temp;
    }
    *l1 = thead;
    return;
}

void msort(leptr *head)
{
    leptr iter1, iter2;
    iter1 = iter2 = *head;

    if(!iter1 || !iter1->next)
        return;
    
    //Find mid
    while(iter2)
    {
        if(iter2->next)
        {
            if(iter2->next->next)
            {
                iter2 = iter2->next->next;
                iter1 = iter1->next;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    //iter1 points to mid
    iter2 = iter1->next;
    iter1->next = NULL;
    msort(head);
    msort(&iter2);
    merge(head, &iter2);
}

void print_list(leptr temp)
{
    while(temp)
    {
        cout<<temp->data<<'\t';
        temp = temp->next;
    }
}

void join(leptr l1, leptr pivot, leptr l2)
{
    leptr iter;
    iter = l1;

    if(!l1 && !l2)
        return;
    if(!l1)
    {
        pivot->next = l2;
        return;
    } 
    iter = traverse(l1);
    iter->next = pivot;
    pivot->next = l2;
    return;
}


void qusort(leptr *head)
{
    leptr l1 =NULL, l2 = NULL, temp, pivot;
    leptr l1head =NULL,l2head = NULL;
    leptr prev = NULL;
    temp = *head;
    //Base case
    if(!temp || !(temp->next))
        return;
    while(temp->next)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    pivot = temp;
    temp = *head;
    while(temp)
    {
        if(temp->data < pivot->data)
        {
            if(!l1)
            {
                l1 = temp;
                l1head = temp;
            }
            else {
                l1->next = temp;
                l1 = l1->next;
            }
        } else {
            if(!l2)
            {
                l2 = temp;
                l2head = temp;
            }
            else {
                l2->next = temp;
                l2 = l2->next;
            }
        }
        temp = temp->next;
    }
    if(l1head)
    {
        l1->next = NULL;
        qusort(&l1head);
    }
    if(l2head)
    {
        l2->next = NULL;
        qusort(&l2head);
    }
    join(l1head, pivot, l2head);
    
    if(l1head)
    {
        *head = l1head;
    }
    else
    { 
        *head = pivot;
    }
}


bool llist::lappend(int data)
{
    list_element *temp;
    if(!head)
    {
        head = new(list_element);
        head->data = data;
        head->next = NULL;
        return true;
    }
    temp = head;
    while(temp->next)
        temp=temp->next;
    temp->next = new (list_element);
    temp->next->data = data;
    temp->next->next = NULL;
}

void llist::lprint(void)
{
    list_element *temp;
    temp = head;
    if(!head)
        return;
    while(temp)
    {
        cout<<temp->data<<"\t";
        temp = temp->next;
    }
}

bool llist::ldelete(int data)
{
    if(!head)
        return false;
}

void llist::modify_list()
{
    list_element *temp, *todel;
    temp = head;
    while(temp)
    {
        todel = temp;
        temp=temp->next;
        delete(todel);
        todel = NULL;
    }
    head = NULL;
}

void llist::mersort()
{
    msort(&head);
}

void llist::quisort()
{
    qusort(&head);
}

void test(list_element **curr)
{
    list_element *temp, *deltemp;
    temp = *curr;
    if(*curr)
        cout<<"super"<<endl;
    while(temp)
    {
        deltemp = temp;
        temp = temp->next;
        delete(deltemp);
        deltemp = NULL;
    }
    *curr = new(list_element);
    temp = *curr;
    temp->data = 100;
    temp->next = NULL;
}

