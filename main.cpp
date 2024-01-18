#include <iostream>
#include "solucion.h"


int main()
{
    Set<int> myset;//basado en hash
    myset.insert(15);
    myset.insert(20);
    myset.insert(5);
    myset.insert(10);
    myset.insert(20);
    myset.insert(5);
    myset.insert(100);
    myset.insert(205);
    myset.insert(54);
    myset.display();//5,10,20,15
    cout<<myset.find(10)<<endl;
    cout<<myset.find(100)<<endl;
    Set<int> myset2;
    myset2.insert(5);myset2.insert(10);myset2.insert(8);myset2.insert(25);
    Set<int> myset3 = myset.Union(myset2);//O(n)
    myset3.display();//5,10,20,15,8,25
}
