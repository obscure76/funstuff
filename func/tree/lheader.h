#include <stdio.h>
#include <stdlib.h>


typedef struct nodes_
{
    int data;
    struct nodes_ * next;
}snode;

typedef struct nodeq_
{
    int data;
    struct nodeq_ * next;
}qnode;

typedef struct node_
{
    int data;
    int level;
    struct node_ *left;
    struct node_ *right;
}node;

void sinsert(snode **curr, int data);
void qinsert(qnode **head, qnode **tail, int data);
