#include "ThirdCriteria.h"

ThirdCriteria::ThirdCriteria(int* args, uint16_t N) : CriteriaInterface(args, N)
{

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
