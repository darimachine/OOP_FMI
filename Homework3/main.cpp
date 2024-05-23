// Domashno3_OOP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PartialFunction.h"
#include "Factory.h"
#include "UserInterface.h"
using std::cout;
using std::endl;
int main()
{
    /*PartialFunctionByCriteria<int (*)(int)> app([](int x) {return x + 3; });
    std::cout << app(4);*/
    save();// saves firstCriteria for TESTING!!!
    save2();// saves twoCriteria for TESTING!!!
    save3(); // saves thirdCriteria for TESTING!!!
    saveFuncDAT(); // saves func.dat for TESTING!!!!!!
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
    /*PartialFunctionContainer container;
    container.addFunction(factory());
    container.addFunction(factory2());
    container.addFunction(factory());
    PartialFunction* f= factory();
    PartialFunction** g = new PartialFunction * [3];
    g[0] = factory();
    g[1] = factory2();
    g[2] = factory();
    MaximumOfPartialFunction maxFuncs(container);
    std::cout<<maxFuncs(6)<<endl;
    cout << maxFuncs(5)<<endl;
    cout<<container.getFunc(1)->operator()(0)<<endl;
    for (int i = 0; i < container.getSize(); i++)
    {
        std::cout << container.getFunc(i)->operator()(6);
    }*/
    
    //FuncWrapper obj([](int x)->int {return x + 5; }, 8, 3, 2);
    //PartialFunctionByCriteria<FuncWrapper> proba = obj;
    //Pair<bool,int> p = proba(5);
   
    //std::cout<<proba(5).getSecond()<<std::endl;
    //std::cout << obj(8);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
