#include<iostream>
using namespace std;

struct my_node{
    int a;
    int b;
    char c;
    union{
        char d;
        int e;
    };
};
template <class T>
int mysizeOf(T x = 0){
    
    return (char *)(&x + 1) - (char *)&x;
}

int main()
{
    char a;
    struct my_node n;
    cout<<mysizeOf(n);
    return 0;
}

