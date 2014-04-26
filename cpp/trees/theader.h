#include <iostream>
using namespace std;

typedef struct node_
{
    int data;
    struct node_ *left;
    struct node_ *right;
} node;

typedef struct qnode_
{
    node * tnode;
    struct qnode_ * next;
} qnode;


class tree
{
    node* root;
    qnode *qhead, *qtail;
    public:
    tree()
    {
       root = NULL;
       qhead = NULL;
       qtail = NULL;
    }
    bool rinsert(node **, int );
    bool rdelete(node **, int , node *);
    void rinorder(node *);
    void rpreorder(node *);
    void rlorder(node *, int);
    bool nrenqueue(qnode **, qnode **, node *);
    int rheight(node *);
    node* find_node(node *, int , node **);
    node* nrdequeue(qnode **, qnode **);
    node* find_succ(node *, node **);
   
    bool tinsert(int );
    bool tdelete(int );
    int theight();
    bool tenqueue(node *);
    void ppreorder();
    void pinorder();
    void lorder();
    node * succ(int );
    node* tdequeue();
    node *ancestor(int , int );
};



