#include "SecondCriteria.h"

int SecondCriteria::findIndex(int x) const
{

	for (int i = 0; i < N; i++)
	{
		if (x == args[i])
			return i;
	}
	return -1;
}

SecondCriteria::SecondCriteria(int* args, uint16_t N)
{
	this->N = N;
	for (int i = 0; i < N; i++)
	{
		this->args[i] = args[i];
	}
}

Pair<bool, int> SecondCriteria::operator()(int x) const
{

	Pair<bool, int> result;
	int index = findIndex(x);
	if (index != -1)
	{
		result.setFirst(false);
		//std::cout << "Undefined!!\n";
		return result;
	}
	result.setFirst(true);
	result.setSecond(x);
	return result;
}
