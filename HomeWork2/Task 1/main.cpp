// MultiSet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MultiSet.h"
using std::cout;
using std::endl;
int main()
{
    MultiSet set(1024);
    
    set.add(5);
    set.add(10);
    set.add(128);
    
    set.add(5);
    set.add(10);
    set.add(5);
    
    MultiSet set2(1024);
    set2.add(10);
    set2.add(5);
    set2.add(5);
    set2.add(4);
    //set2.remove(4);
    set2.add(8);
    set2.add(128);

    set.print();
    cout << endl;
    set2.print();
    cout << endl;
    MultiSet set3= intersection(set, set2);
    /*set3.print();*/
    MultiSet unioset = unionSets(set, set2);
    unioset.print();
}

