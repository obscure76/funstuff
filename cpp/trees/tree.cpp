#include<theader.h>

/* Insertion */
bool tree::rinsert(node **curr, int data)
{
    node *temp;
    temp = *curr;
    if(!temp)
    {
        temp = new(node);
        temp->data = data;
        temp->left = temp->right = NULL;
        *curr = temp;
        return true;
    }
    if(temp->data > data)
    {
        return rinsert(&(temp->left), data);
    } else {
        return rinsert(&(temp->right), data);
    }
}

bool tree::tinsert(int data)
{
    return rinsert(&root, data);
}

/* Traversals */
void tree::rinorder(node *curr)
{
    if(!curr)
        return;
    rinorder(curr->left);
    cout<<"\t"<<curr->data;
    rinorder(curr->right);
}

void tree::pinorder()
{
    rinorder(root);
}

/* Traversals */
void tree::rpreorder(node *curr)
{
    if(!curr)
        return;
    cout<<"\t"<<curr->data;
    rpreorder(curr->left);
    rpreorder(curr->right);
}

void tree::ppreorder()
{
    rpreorder(root);
}


bool tree::nrenqueue(qnode ** head, qnode **tail, node *tnode)
{
    qnode *temp;
    temp= new(qnode);
    temp->tnode=tnode;

    if(!*head)
    {
        temp->next=NULL;
        *head = temp;
        *tail = temp;
    } else {
        temp->next=NULL;
        (*tail)->next = temp;
        *tail = temp;
    }
    return true;
}

bool tree::tenqueue(node *tnode)
{
    nrenqueue(&qhead, &qtail, tnode);
}

node* tree::nrdequeue(qnode **head, qnode **tail)
{
    node *data;
    qnode *temp;
    if(!*head)
        return NULL;
    temp = *head;
    data = temp->tnode;
    *head = (temp->next);
    delete(temp);
    temp = NULL;
    if(!*head)
        *tail = NULL;
    return data;
}

node* tree::tdequeue()
{
    return nrdequeue(&qhead, &qtail);
}

int tree::rheight(node *curr)
{
    int l, r;
    if(!curr)
        return 0;
    if(!curr->left && !curr->right)
        return 1;
    if(!curr->left && curr->right)
        return(1+rheight(curr->right));
    if(curr->left && !curr->right)
        return(1+rheight(curr->left));
    l = rheight(curr->left);
    r = rheight(curr->right);
    if(l>r)
        return 1+l;
    else
        return 1+r;
}

int tree::theight()
{
    return rheight(root);
}
        
void tree::rlorder(node *curr, int level)
{
    if(!curr)
        return;
    if(level==1)
        cout<<curr->data<<'\t';
    else if(level > 1)
    {
        rlorder(curr->left, level-1);
        rlorder(curr->right, level-1);
    }
}

void tree::lorder()
{
    int height = theight();

    for(int i=1;i<=height;i++)
    {
        rlorder(root, i);
        cout<<endl;
    }
}

node * tree::find_node(node *curr, int data, node **nparent)
{
    if(!curr)
    {
        cout<<"\n Could not find the element"<<data;
        return NULL;
    }
    if(curr->data > data)
        return find_node(curr->left, data, &curr);
    if(curr->data < data)
        return find_node(curr->right, data, &curr);
    return curr;
}

node * tree::find_succ(node *curr, node **parent)
{
    while(curr->left)
    {
        *parent = curr;
        curr = curr->left;
    }
    return curr;
}

bool tree::rdelete(node **curr, int data, node *nparent)
{
    node *sparent;
    node *succ, *temp;
    sparent = *curr;
    temp = *curr;
    
    if(!temp)
        return false;
    
    if(!temp->left && !temp->right)
    {
        delete(temp);
        temp = NULL;
        *curr = NULL;
        return true;
    }

    if(temp->left && !temp->right)
    {
        if(nparent)
        {
            if(nparent->left->data == temp->data)
            {
                nparent->left = temp->left;
            } else {
                nparent->right = temp->left;
            }
            *curr = NULL;
        } else {
            *curr = temp->left;
        } 

         delete(temp);
        temp = NULL;
        return true;
    }

    if(!temp->left && temp->right)
    {
        if(nparent)
        {
            if(nparent->left->data == temp->data)
            {
                nparent->left = temp->right;
            } else {
                nparent->right = temp->right;
            }
            *curr = NULL;
        } else {
            *curr = temp->right;
        } 

        delete(temp);
        temp = NULL;
        return true;
    }
    succ = find_succ(temp->right, &sparent);
    if(sparent->left->data == succ->data)
    {
        temp->data = succ->data;
        sparent->left = succ->right;
        delete(succ);
        succ = NULL;
    } else {
        temp->data = succ->data;
        sparent->right = succ->right;
        delete(succ);
        succ = NULL;
    }
    return true;
}

bool tree::tdelete(int data)
{
    node *temp = NULL, *nparent = NULL;
    temp = find_node(root, data, &nparent);
    if(temp)
    {
        cout<<"\n Found the node "<<temp->data;
        return rdelete(&temp, data, nparent);
    }
    else
        return false;
} 
