#include "FirstCriteria.h"

FirstCriteria::FirstCriteria(int* args, int* res, uint16_t N) : CriteriaInterface(args, N)
{
	for (int i = 0; i < N; i++)
	{
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
