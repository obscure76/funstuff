#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <chplot.h>
using namespace std;

int get_random(int min, int max)
{
    return min + (rand() % (int)(max - min + 1));
}
    

template<typename T>
void swapi(T& x, T& y)
{
      T tmp = x;
      x = y;
      y = tmp;
}

int main()
{
    int i=9, j =6;
    int numpoints = 36;
    array double x[numpoints], y[numpoints];
    cout<<"before";
    cout<<i<<j<<endl;
    swapi(i,j);
    cout<<"after";
    cout<<i<<j<<endl;
    lindata(0, 360, x, 36);
    y = sin(x*M_PI/180);
    plotxy(x, y, "Ch plot", "xlabel", "ylabel");
    return 0;
}
