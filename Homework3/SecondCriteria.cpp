#include "SecondCriteria.h"


SecondCriteria::SecondCriteria(int* args, uint16_t N) : CriteriaInterface(args, N)
{
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
