#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

template <typename T>
class matrix
{
    public:
    T **matr;
    int rows, cols;
    
    matrix(int srows, int scols)
    {
        rows = srows;
        cols = scols;
        matr = allocate_matrix();
        cout<<rows<<' '<<cols<<endl;
    }
   
    ~matrix()
    {
        delete_matrix();
    }
    T** allocate_matrix()
    {
        T** temp;
        temp = new T* [rows];
        for(int i=0; i<rows; i++)
        {
            temp[i] = new T[cols];
        }
        return temp;
    }
    
    void init_matrix();
    void print_matrix();
    void delete_matrix();

};

template <typename T>
void matrix<T>::delete_matrix()
{
    for(int i=0;i<rows;i++)
    {
        delete matr[i];
    }
    delete matr;
}

template <typename T>
void matrix<T>::print_matrix()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<matr[i][j]<<' ';
        }
        cout<<endl;
    }
}

template <typename T>
void matrix<T>::init_matrix()
{
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            matr[i][j] = 0;
        }
     }
}

int main()
{
    matrix<double> *myMatrix;
    myMatrix  = new matrix<double>(9,4);
    myMatrix->init_matrix();
    myMatrix->print_matrix();
    return 0;
}


