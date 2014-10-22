#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct Tnode
{
    int val;
    Tnode *left;
    Tnode *right;
    Tnode(int v) 
    {
        val = v;
        left = NULL;
        right = NULL;
    }
};


class Tree {
    private:
        Tnode *root;
    public:
        Tree()
        {
            root = NULL;
        }
        void insertInTree(int);
        bool deleteFromTree(int);
        void printTree();
};

void Tree::insertInTree(int val)
{
    Tnode *temp = root;
    if(!root)
    {
        root = new Tnode(val);
    } else {
        Tnode *parent = NULL;
        bool dir = 0;
        while(temp)
        {
            if(temp->val > val)
            {
                parent = temp;
                temp = temp->left;
                dir = 0;
            } else {
                parent = temp;
                temp = temp->right;
                dir = 1;
            }
            if(dir)
            {
                parent->right = new Tnode(val);
            } else {
                parent->left = new Tnode(val);
            }
        }
    }
    return;
}

void Tree::printTree(void)
{
    list<Tnode*> queue;
    queue.push_back(root);
    while(!queue.empty())
    {
        Tnode* temp = queue.front();
        queue.pop_front();
        cout<<temp->val<<" ";
        if(temp->left)
            queue.push_back(temp->left);
        if(temp->right)
            queue.push_back(temp->right);
    }

}

bool Tree::deleteFromTree(int val)
{
}

int main()
{
    Tree *t = new Tree();
    t->insertInTree(3);
    t->insertInTree(1);
    t->insertInTree(4);
    t->printTree();
    return 0;
}

