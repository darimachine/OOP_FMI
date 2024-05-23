#include "Factory.h"


void save()
{
	char filename[] = "first.dat";
	std::ofstream ofs(filename, std::ios::binary);
	uint16_t N = 7;
	uint16_t T = 0;
	int args[MAX_SIZE] =	{ 0,1,2,3,5,6,7 };
	int result[MAX_SIZE] = { 0,3,3,3,4,4,0 };
	ofs.write((const char*)&N, sizeof(N));
	ofs.write((const char*)&T, sizeof(T));
	ofs.write((const char*)args, sizeof(int) * N);
	ofs.write((const char*)result, sizeof(int) * N);
	ofs.close();
}
void save2()
{
	char filename[] = "second.dat";
	std::ofstream ofs(filename, std::ios::binary);
	uint16_t N = 2;
	uint16_t T = 1;
	int args[MAX_SIZE] = { 3,5};
	//int result[32] = { 0,3,3,3,4,4,0 };
	ofs.write((const char*)&N, sizeof(N));
	ofs.write((const char*)&T, sizeof(T));
	ofs.write((const char*)args, sizeof(int) * N);
	//ofs.write((const char*)result, sizeof(N) * N);
	ofs.close();
}
void save3()
{
	char filename[] = "third.dat";
	std::ofstream ofs(filename, std::ios::binary);
	uint16_t N = 4;
	uint16_t T = 2;
	int args[MAX_SIZE] = { 0,5,6,7 };
	ofs.write((const char*)&N, sizeof(N));
	ofs.write((const char*)&T, sizeof(T));
	ofs.write((const char*)args, sizeof(int) * N);

	ofs.close();
}
void saveFuncDAT()
{
	char filename[] = "func.dat";
	std::ofstream ofs(filename, std::ios::binary);
	uint16_t N = 3;
	uint16_t T = 3;
	char filename1[] = "first.dat";
	int filename1Size = std::strlen(filename1)+1;
	
	char filename2[] = "second.dat";
	int filename2Size = std::strlen(filename2)+1;

	char filename3[] = "third.dat";

	int filename3Size = std::strlen(filename3)+1;
	ofs.write((const char*)&N, sizeof(N));
	ofs.write((const char*)&T, sizeof(T));
	ofs.write((const char*)filename1, filename1Size);
	ofs.write((const char*)filename2, filename2Size);
	ofs.write((const char*)filename3, filename3Size);

	ofs.close();
}
PartialFunction* factory()
{
	save();
	
	char filename[] = "first.dat";
	std::ifstream ifs(filename, std::ios::binary);
	uint16_t N, T;

	ifs.read((char*)&N, sizeof(N));
	ifs.read((char*)&T, sizeof(T));
	switch (T)
	{
	case 0: {
		int args[MAX_SIZE];
		int result[MAX_SIZE];
		ifs.read((char*)args, sizeof(int) * N);
		ifs.read((char*)result, sizeof(int) * N);
		FirstCriteria func(args, result, N);
		return new PartialFunctionByCriteria<FirstCriteria>(func);
	}
	}
	return nullptr;
}
PartialFunction* factory2()
{
	save2();

	char filename[] = "second.dat";
	std::ifstream ifs(filename, std::ios::binary);
	uint16_t N, T;

	ifs.read((char*)&N, sizeof(N));
	ifs.read((char*)&T, sizeof(T));
	switch (T)
	{
	case 1: {
		int args[MAX_SIZE];
		ifs.read((char*)args, sizeof(int) * N);
		
		SecondCriteria func(args, N);
		return new PartialFunctionByCriteria<SecondCriteria>(func);
	}
	}
	return nullptr;
}

PartialFunction* Factory::secondCriteriaFactory(std::ifstream& ifs, uint16_t N)
{
	int args[MAX_SIZE];
	ifs.read((char*)args, sizeof(int) * N);
	SecondCriteria func(args, N);
	return new PartialFunctionByCriteria<SecondCriteria>(func);
	
}

PartialFunction* Factory::thirdCriteriaFactory(std::ifstream& ifs, uint16_t N)
{
	int args[MAX_SIZE];
	ifs.read((char*)args, sizeof(int) * N);
	ThirdCriteria func(args, N);
	return new PartialFunctionByCriteria<ThirdCriteria>(func);
}

PartialFunction* Factory::firstCriteriaFactory(std::ifstream& ifs,uint16_t N)
{
	int args[MAX_SIZE];
	int result[MAX_SIZE];
	ifs.read((char*)args, sizeof(int) * N);
	ifs.read((char*)result, sizeof(int) * N);
	FirstCriteria func(args, result, N);
	return new PartialFunctionByCriteria<FirstCriteria>(func);
	
}

PartialFunction* Factory::factoryFunction(const char* filename)
{
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::exception("File Could Open");
		
	}
	uint16_t N, T;
	ifs.read((char*)&N, sizeof(N));
	if (N > 32|| N==0) {
		throw std::out_of_range("N incorrect");
	}

	ifs.read((char*)&T, sizeof(T));
	
	switch (T) {
		case 0: {
			return firstCriteriaFactory(ifs, N);
		}
		case 1: {
			return secondCriteriaFactory(ifs, N);
		}
		case 2: {
			return thirdCriteriaFactory(ifs, N);
		}
		case 3: {
			PartialFunctionContainer container;
			for (int i = 0; i < N; i++)
			{
				MyString filename;
				char ch;
				while (ifs.read((char *)&ch,1) && ch!='\0')
				{
					filename += ch;
				}
				container.addFunction(factoryFunction(filename.c_str()));
			}
			return new MaximumOfPartialFunction(container);
		}
		case 4: {
			PartialFunctionContainer container;
			for (int i = 0; i < N; i++)
			{
				MyString filename;
				char ch;
				while (ifs.read((char*)&ch, 1) && ch != '\0')
				{
					filename += ch;
				}
				container.addFunction(factoryFunction(filename.c_str()));
			}
			return new MinimumOfPartialFunction(container);
		}
		default: {
			throw std::out_of_range("Invalid T");
		}
	}
	return nullptr;
}


