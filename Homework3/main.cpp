// Domashno3_OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PartialFunction.h"
#include "Factory.h"
#include "UserInterface.h"
#include "PartialFunctionByCriteria.h"
#include "UniquePointer.hpp"
using std::cout;
using std::endl;
//Proba with function;
typedef Pair<bool, int>(*FuncType)(int);
Pair<bool, int> f(int x)
{
    Pair<bool, int> result;
    if (x == 3 || x == 6) {
        result.setFirst(false);
        return result;
        
    }
    result.setSecond(x + 3);
    return result;
}
int main()
{
    PartialFunctionByCriteria<FuncType> func(f);
    cout << func(5)<<endl;
    while (true)
    {
        UniquePointer<PartialFunction> function = Factory::factoryFunction("func.dat");
    }
   
  
    save();// saves firstCriteria for TESTING!!!
    save2();// saves twoCriteria for TESTING!!!
    save3(); // saves thirdCriteria for TESTING!!!
    saveFuncDAT();
    //saveFunc2DAT(); // saves func.dat for TESTING!!!!!!
    //saveFunc2222();
    MainMenu();
    
    
    /*PartialFunction* p = Factory::factoryFunction("func.dat");
    for (int i = 0; i < 10; i++)
    {
        if (p->isDefined(i))
        {
            cout <<"f(" << i <<")" << "=" << (*p)(i) << endl;
        }
        else {
            cout << "f(" << i << ")" << "=" << "Undefined" << endl;
        }
        
    }
    delete p;*/
    
}
