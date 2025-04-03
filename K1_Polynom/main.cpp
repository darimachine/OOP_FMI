

#include "Polynom.h"
int main()
{
	double arr[3] = { 2,6,1 }; // 2 + 6x^1 + 1x^2
	Polynom p1(arr, 3);

	double arr2[2] = { 2,6 }; // 2 + 6x^1 + 1x^2
	Polynom p2(arr2, 2);
	p2.load("file.txt");
	p2.print();
	cout << endl;
	p1.add(p2);
	p1.print();
}