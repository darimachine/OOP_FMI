#include "Multiset.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
constexpr int MAX_FILE_SIZE = 1024;
void Multiset::MainMenu()
{
	try {
		int n, k;
		cout << "Type N:\n";
		cin >> n;
		cout << "Type K:\n";
		cin >> k;
		Multiset set(n, k);
		while (true)
		{
			cout << "1) - Add Number\n";
			cout << "2) - Check Specific Number Occurencie\n";
			cout << "3) - Print all numbers\n";
			cout << "4) - Print Represented as Bits\n";
			cout << "5) - Read From file\n";
			cout << "6) - Write to file\n";
			cout << "9) - Exit\n";
			cout << "For Testing Intersect/Addition/Difference etc... uncomment MAINMENU() function and type them in main() manually\n";
			int choice;
			cin >> choice;
			if (choice == 9)
			{
				break;
			}
			else if (choice == 1)
			{
				cout << "Type Number:\n";
				int number;
				cin >> number;
				set.add(number);
				
			}
			else if (choice == 2)
			{
				cout << "Type Number:\n";
				int number;
				cin >> number;
				cout<<set.getNumberOccurencie(number)<<endl;
			}
			else if (choice == 3)
			{
				cout << set;
			}
			else if (choice == 4)
			{
				set.printBits();
			}
			else if (choice == 5)
			{
				char filename[MAX_FILE_SIZE];
				cout << "Enter filename: \n";
				cin >> filename;
				deSerialize(filename, set);
			}
			else if (choice == 6)
			{
				char filename[MAX_FILE_SIZE];
				cout << "Enter filename: \n";
				cin >> filename;
				serialize(filename, set);
			}

			
		}
	}
	catch (const std::exception& er)
	{
		cout << er.what();
	}
	catch (...)
	{
		cout << "Error\n";
	}
	
}