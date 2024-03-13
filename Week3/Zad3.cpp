#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

void writeTofile(const char * filename)
{
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open())
	{
		cout << "Error";
		return;
	}
	int arr[10] = { 1,2,3,4,55,6,7,8,9,10 };
	char stringa[] = "abc";
	ofs.write((const char*)arr, sizeof(arr));
	ofs.write((const char*)&stringa, sizeof(stringa));
	ofs.close();
}
void printBitesWhoAreNotInTheFile(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open())
	{
		cout << "Error";
		return;
	}
	bool arr[255];
	while (!in.eof())
	{
		char ch;
		in.read((char*)&ch, sizeof(ch));
		arr[(int)ch] = false;
	}
	for (int i = 0; i < 256; i++)
	{
		if (arr[i]) {
			cout << i<<endl;
		}
	}
}
int main(){
	writeTofile("bytes.dat");
	printBitesWhoAreNotInTheFile("bytes.dat");
}
