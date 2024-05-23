#include "FirstCriteria.h"

int FirstCriteria::findIndex(int x) const
{
	for (int i = 0; i < N; i++)
	{
		if (x == args[i])
			return i;
	}
	return -1;
}

FirstCriteria::FirstCriteria(int* args, int* res, int N)
{
	this->N = N;
	for (int i = 0; i < N; i++)
	{
		this->args[i] = args[i];
		this->res[i] = res[i];
	}
}

Pair<bool, int> FirstCriteria::operator()(int x) const
{
	Pair<bool, int> result;
	int index = findIndex(x);
	if (index == -1)
	{
		result.setFirst(false);
		return result;
	}
	result.setFirst(true);
	result.setSecond(res[index]);
	return result;

}
