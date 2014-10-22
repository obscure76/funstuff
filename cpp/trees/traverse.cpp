#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <map>
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
map<int, list<int> > vmap;

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
        void printTreeLevel();
        void printInOrder();
        void printTreeVertical();
};


void verticalOrder(Tnode *node, int level)
{
   cout<<node->val;
   if(node->left)
       verticalOrder(node->left, level-1);
   if(vmap.find(level) != vmap.end())
   {
       //Level already present in map; enqueue
        list<int> l = vmap.find(level)->second;
        l.push_back(node->val);
   } else {
       cout<<"Level" <<level<<" ";
       list<int> l;
       l.push_back(node->val);
       vmap[level] = l;
   }
   if(node->right)
       verticalOrder(node->right, level+1);
}

void Tree::printTreeVertical()
{
    verticalOrder(root, 0);
    cout<<"\n\n Vertical Order\n\n";
    for(map<int, list<int> >::iterator it= vmap.begin(); it!=vmap.end(); it++)
    {
        list<int> l = it->second;
        cout<<"Level" << it->first<<" ";
        for(list<int>::iterator lit =  l.begin(); lit!=l.end();lit++) {
            cout<<*lit<<" ";
        }
        cout<<endl;
    }
}

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
        }
        if(dir)
        {
            parent->right = new Tnode(val);
        } else {
            parent->left = new Tnode(val);
        }
    }
    return;
}

void inorder(Tnode * node)
{
    if(!node)
        return;
    inorder(node->left);
    cout<<node->val;
    inorder(node->right);
}

void Tree::printInOrder()
{
    inorder(root);
}
void Tree::printTreeLevel(void)
{
    list<Tnode*> queue;
    queue.push_back(root);
    queue.push_back(new Tnode(-99));
    while(!queue.empty())
    {
        Tnode* temp = queue.front();
        queue.pop_front();
        if(temp->val == -99 and !queue.empty())
        {
            queue.push_back(temp);
            cout<<"\n";
            continue;
        } else if(queue.empty()){
            cout<<"\n";
            return;
        }
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
    t->insertInTree(5);
    t->insertInTree(3);
    t->insertInTree(1);
    t->insertInTree(4);
    t->insertInTree(3);
    t->insertInTree(6);
    t->insertInTree(9);
    t->printTreeLevel();
    t->printInOrder();
    t->printTreeVertical();
    return 0;
}

