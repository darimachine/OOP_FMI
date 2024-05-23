#include "ThirdCriteria.h"

int ThirdCriteria::findIndex(int x) const
{
	for (int i = 0; i < N; i++)
	{
		if (args[i] == x) {
			return i;
		}
	}
    return -1;
}

ThirdCriteria::ThirdCriteria(int* args, uint16_t N)
{
	this->N = N;
	for (int i = 0; i < N; i++)
	{
		this->args[i] = args[i];
	}
}

Pair<bool, int> ThirdCriteria::operator()(int x) const
{
	Pair<bool, int> result;
	result.setFirst(true);
	int index = findIndex(x);
	if (index != -1)
	{
		result.setSecond(1);
		return result;
	}
	result.setSecond(0);
	return result;
}
