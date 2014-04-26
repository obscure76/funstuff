#include <iostream>
using namespace std;
#ifndef ARRAY_H
#define ARRAY_H
 
#include <assert.h> // for assert()
 
template <typename T>
class Array
{
private:
    int m_nLength;
    T *m_ptData;
 
public:
    Array()
    {
        m_nLength = 0;
        m_ptData = 0;
    }
 
    Array(int nLength)
    {
        m_ptData= new T[nLength];
        m_nLength = nLength;
    }
 
    ~Array()
    {
        delete[] m_ptData;
    }
 
    void Erase()
    {
        delete[] m_ptData;
        // We need to make sure we set m_pnData to 0 here, otherwise it will
        // be left pointing at deallocated memory!
        m_ptData= 0;
        m_nLength = 0;
    }
 
    T& operator[](int nIndex)
    {
        assert(nIndex >= 0 && nIndex < m_nLength);
        return m_ptData[nIndex];
    }
 
    // The length of the array is always an integer
    // It does not depend on the data type of the array
    int GetLength(); // templated GetLength() function defined below
};
 
template <typename T>
int Array<T>::GetLength() { return m_nLength; }
 
#endif

template <class T>
T Average(T *atArray, int nNumValues)
{
    T tSum = 0;
    for (int nCount=0; nCount < nNumValues; nCount++)
        tSum += atArray[nCount];
 
    tSum /= nNumValues;
    return tSum;
}

class Cents
{
private:
    int m_nCents;
public:
    Cents(int nCents)
        : m_nCents(nCents)
    {
    }
 
    friend ostream& operator<< (ostream &out, const Cents &cCents)
    {
        out << cCents.m_nCents << " cents ";
        return out;
    }
    void operator+=(Cents cCents)
    {
        m_nCents += cCents.m_nCents;
    }
 
    void operator/=(int nValue)
    {
        m_nCents /= nValue;
    }
    
};

int main()
{
        double dnArray[] = { 3.12, 3.45, 9.23, 6.34 };
        Cents cArray[] = { Cents(5), Cents(10), Cents(15), Cents(14) };
        Array<int> anArray(12);
        Array<double> adArray(12);
 
        for (int nCount = 0; nCount < 12; nCount++)
        {
                anArray[nCount] = nCount;
                adArray[nCount] = nCount + 0.5;
        }
 
        for (int nCount = 11; nCount >= 0; nCount--)
               cout << anArray[nCount] << "\t" << adArray[nCount] << endl;
 
    return 0;
        cout << Average(dnArray, 4) << std::endl;
        cout << Average(cArray, 4) << std::endl;
return 0;
}
