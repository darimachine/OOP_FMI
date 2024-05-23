#include "MinimumOfPartialFunction.h"



MinimumOfPartialFunction::MinimumOfPartialFunction(const PartialFunctionContainer& _funcs)
	:funcs(_funcs)
{

}

bool MinimumOfPartialFunction::isDefined(int x) const
{
	int size = funcs.getSize();
	for (int i = 0; i < size; i++)
	{
		if (!funcs.getFunc(i)->isDefined(x))
		{
			return false;
		}
	}
	return true;
}

int MinimumOfPartialFunction::operator()(int x) const
{
	if (!isDefined(x))
	{
		throw std::exception("Not Defined");
	}
	int size = funcs.getSize();
	int min = funcs.getFunc(0)->operator()(x);
	for (int i = 1; i < size; i++)
	{
		int value = funcs.getFunc(i)->operator()(x);
		if (value < min)
		{
			min = value;
		}
	}
	return min;
}

PartialFunction* MinimumOfPartialFunction::clone() const
{
    return new MinimumOfPartialFunction(*this);
}
