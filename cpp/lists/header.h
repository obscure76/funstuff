#include <iostream>
using namespace std;

typedef struct list_element_
{
    int data;
    struct list_element_ * next;
} list_element;
typedef list_element* leptr;

void swap(leptr , leptr );
void merge(leptr*, leptr*);
leptr traverse(leptr head);
void msort(leptr *);
void qusort(leptr *);
void join(leptr , leptr, leptr );


class llist
{
    private:
        list_element *head;
    public:
        llist()
        {
            head = NULL;
        }
        bool lappend(int data);
        void lprint(void);
        bool ldelete(int data);
        void modify_list();
        void mersort();
        void quisort();
};
