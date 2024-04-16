// Domashno_2_ZAD_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Multiset.h"

using std::cout;
using std::endl;
int main()
{
    //Multiset::MainMenu();
    Multiset a(7 , 3);
    
    a.add(0);
    a.add(1);
    a.add(2);
    a.add(1);
    a.add(7);
    a.printBits();
    Multiset b(9, 6);
    b.add(0);
    b.add(1);
    b.add(1);
    b.add(1);
    b.add(7);
    b.add(9);
    cout << endl;
    b.printBits();
    cout << endl;
    Multiset c = complement(b);
    c.printBits();

   /* Multiset obj = intersect(a,b);
    cout << obj;
    cout << endl;
    Multiset c = difference(a, b);
    cout << c;*/
    
    /*deSerialize("proba.dat", b);
    cout << b;
    cout << endl;*/

    /*cout << a;
    cout << endl;
    cout << a.getNumberOccurencie(13);
    cout << endl;
    std::cout << a.isContains(0);
    cout << endl;
    a.printBits();*/
}
