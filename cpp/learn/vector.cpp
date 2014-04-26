#include <vector>
#include <iostream>
using namespace std;

struct temp
{
    int data;
};

int main()
{
 
    vector<int> vect;
    for (int nCount=0; nCount < 6; nCount++)
        vect.push_back(10 - nCount); // insert at end of array
 
    for (int nIndex=0; nIndex < vect.size(); nIndex++)
        cout << vect[nIndex] << " ";
    cout << endl;
}
