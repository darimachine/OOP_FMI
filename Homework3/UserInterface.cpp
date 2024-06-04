#include <iostream>
#include "PartialFunction.h"
#include "Factory.h"
#include "UniquePointer.hpp"
using std::cout;
using std::endl;
using std::cin;
void MainMenu()
{
	cout << "Option 1): Enter: a , Enter: b, Prints every number from function within this Interval\n";
	cout << "Option 2): Generate every number until you type Exit\n";
	int choice;

	while (true)
	{
		cin >> choice;
		if (choice == 1 || choice == 2) {
			break;
		}
		else {
			cout << "Incorrect Choice choose again\n";
		}
	}
	UniquePointer<PartialFunction> function = Factory::factoryFunction("func.dat");
	//PartialFunction* p = Factory::factoryFunction("func.dat");


	if (choice == 1)
	{
		int a, b;
		cout << "Enter a\n";
		cin >> a;
		cout << "Enter b\n";
		cin >> b;
		if (a > b) {
			std::swap(a, b);
		}
		for (int i = a; i <= b; i++)
		{
			if (function->isDefined(i))
			{
				cout << "f(" << i << ")" << "=" << (*function)(i) << endl;
			}
			else {
				cout << "f(" << i << ")" << "=" << "Undefined" << endl;
			}

		}
	}
	else {
		while (true)
		{
			cout << "Enter X(int), (Or type exit to stop the program):\n";
			MyString x;
			cin >> x;
			if (x == "exit")
			{
				break;
			}
			int value = atoi(x.c_str());
			if (function->isDefined(value))
			{
				cout << "f(" << value << ")" << "=" << (*function)(value) << endl;
			}
			else {
				cout << "f(" << value << ")" << "=" << "Undefined" << endl;
			}
		}
	}
	
}