#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;

void writeTofile(const char* filename)
{
	std::ofstream out(filename, std::ios::binary);
	int arr[10] = { 2,3,5,8,12,14,16,17,20,23 };
	if (!out.is_open())
	{
		cout << "Error";
		return;
	}
	out.write((const char*)arr, sizeof(arr));
	out.close();
}
int getFileSize(std::ifstream& in)
{
	int currentPos = in.tellg();
	in.seekg(0, std::ios::end);
	int size = in.tellg();
	in.seekg(currentPos);
	return size;
}
void printArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "////////////" << endl;
}
bool isPrimeNumber(int number)
{
	int length = sqrt(number);
	for (int i = 2; i <= length; i++)
	{
		if (number % i == 0) return false;
	}
	return true;
}
struct Numbers {
	int* arr;
	int arraySize = 0;
};
void freeArray(Numbers& number)
{
	delete[] number.arr;
}
Numbers readFromFile(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open())
	{
		cout << "Error";
		return {};
	}
	int sizeOfFile = getFileSize(in);
	int arraySize = sizeOfFile / 4;
	Numbers number;
	number.arraySize = arraySize;
	number.arr = new int[arraySize];
	in.read((char*)number.arr, sizeOfFile);
	printArray(number.arr, arraySize);
	
	in.close();
	return number;
}
void writePrimeSustavNumbers()
{
	Numbers number = readFromFile("numbers.dat");
	std::ofstream outPrime("prime.dat", std::ios::binary);
	std::ofstream outComplex("complex.dat", std::ios::binary);
	if (!outPrime.is_open() || !outComplex.is_open())
	{
		cout << "Error";
		return;
	}
	for (int i = 0; i < number.arraySize; i++)
	{
		if (isPrimeNumber(number.arr[i]))
		{
			outPrime.write((const char*)&number.arr[i], sizeof(number.arr[i]));
		}
		else {
			outComplex.write((const char*)&number.arr[i], sizeof(number.arr[i]));
		}
	}

	outPrime.close();
	outComplex.close();
	freeArray(number);

}
int main()
{
	writeTofile("numbers.dat");
	writePrimeSustavNumbers();
	Numbers prime = readFromFile("prime.dat");
	Numbers complex = readFromFile("complex.dat");
	
}
