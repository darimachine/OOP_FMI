// Domashno_2_ZAD_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ModifiableIntegersFunction.h"
using std::cout;
using std::endl;

int main()
{
    
    try {
       
        ModifiableIntegersFunction a([](int16_t x)->int16_t {return 2*x+3; });
        
        a.addSpecialNumber(3, 10);
        //a.excludePoint(4);
        //a.excludePoint(4);
        ModifiableIntegersFunction b([](int16_t x)->int16_t {return 2*x + 5; });
        cout << a.callFunction(3);
        cout << endl;
        cout << a.inverse(13);
        cout << endl;
        cout << (a || b);
        cout << endl;
        ModifiableIntegersFunction c = a - b;
        cout << c.callFunction(13);
        cout << endl;
        cout<<(a ^ 3)(9); // operator ^
        cout << endl;
      
        //ModifiableIntegersFunction k = a(b);
        cout << endl;
        //cout << k.callFunction(4);
        cout << endl;
        cout << c.callFunction(4);
        cout << endl;
        cout << INT16_MAX;
    }
    catch (const std::exception& er)
    {
        cout<<er.what();
    }
    catch (...)
    {
        cout << "Unexpected Error";
    }

  
    //std::cout << "Hello World!\n";
}

