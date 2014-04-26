#include <iostream>

class Cents
{
private:
    int m_nCents;
public:
    Cents(int nCents)
        : m_nCents(nCents)
    {
    }
 
    friend bool operator>(Cents &c1, Cents&c2)
    {
        return (c1.m_nCents > c2.m_nCents) ? true: false;
    }
};

int main()
{
    Cents c1(5),c2(9);
    if(c1>c2)
    {
        std::cout<<"C1 is greater";
    } else {
        std::cout<<"C2 is greater";
    }
}
