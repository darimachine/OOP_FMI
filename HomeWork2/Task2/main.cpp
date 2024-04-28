// Domashno_2_ZAD2_Beter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ModifiableIntegersFunction.h"


using std::cout;
using std::endl;

int main() // everything works perfect!!!!!!
{
    try {
       
        
        ModifiableIntegersFunction a([](int16_t x)->int16_t {return x + 3; });
        ModifiableIntegersFunction b([](int16_t x)->int16_t {return x + 5; });

        ModifiableIntegersFunction c = a + b; // sum of two
        ModifiableIntegersFunction d = c + b; // chain sum
        cout << a(2) << endl;// test a
        cout << b(2) << endl;//test  b
        cout << c(2) << endl;//test c
        cout << d(2) << endl;// test d
        ModifiableIntegersFunction h = d ^ 3; // test ^       
        cout << h(2) << endl; // test
        ModifiableIntegersFunction f([](int16_t x)->int16_t {return x + 6; });
        plotFunction(f, -10, 10, -10, 10); // plot function
        cout << f(3) << endl;
        f.serialize("serhan.dat"); // saving RANGE OF f()
        ModifiableIntegersFunction myObj([](int16_t x)->int16_t {return x + 10; });
        cout << myObj(6) << endl; //printing regular RANGE
        myObj.deserialize("serhan.dat"); // Reading RANGE of f()
        cout << myObj(6) << endl; // printing Range From Readed FILE working!!!

        ModifiableIntegersFunction fInverse = inverse(f); // get inverse comment bijective check if you want to work on any function


        cout << f.getInjective() << endl; // check if is injective
        cout << f.getSurjective() << endl; // check if is surjective
        f.addSpecificNumber(3, 20); // you can add specificNumber
        cout << f.getInjective() << endl; // changed!!!
        f.excludePoint(5); // you can exlclude number
        cout << f(3) << endl;
        cout << fInverse(7); // print inverse
         cout << endl;
        cout << f(6) << endl;

        ModifiableIntegersFunction g([](int16_t x)->int16_t {return 2 * x + 5; });
         cout << (f || g) << endl; // check if they are paraller
         cout << (f < g) << endl; // all comparison operators
         cout << f(g(4)) << endl; //compose of MULTIPLE function

        ModifiableIntegersFunction k = f + g; // create their sum
        cout << k(2);
        cout << endl;
        ModifiableIntegersFunction compose = k ^ 3; // operator ^ will be called 3 times
        cout << compose(2);
        cout << endl;
        ModifiableIntegersFunction o = k + g; // sum of sums
        cout << o(2);
        
            
    }
    catch (std::runtime_error& er)
    {
        cout << er.what();
    }
    catch (std::exception& er)
    {
        cout << er.what();
    }
    
}

