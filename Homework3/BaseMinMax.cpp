#include "BaseMinMax.h"

BaseMinMax::BaseMinMax(const PartialFunctionContainer& funcs) : functions(funcs)
{
}

bool BaseMinMax::isDefined(int x) const
{
	int size = functions.getSize();
	for (int i = 0; i < size; i++)
	{
		if (!functions.getFunc(i)->isDefined(x))
		{
			return false;
		}
	}
	return true;
}

