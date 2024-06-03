#include "MinimumOfPartialFunction.h"



MinimumOfPartialFunction::MinimumOfPartialFunction(const PartialFunctionContainer& _funcs)
	:BaseMinMax(_funcs)
{

}

int MinimumOfPartialFunction::operator()(int x) const
{
	if (!isDefined(x))
	{
		throw std::exception("Not Defined");
	}
	int size = functions.getSize();
	int min = functions.getFunc(0)->operator()(x);
	for (int i = 1; i < size; i++)
	{
		int value = functions.getFunc(i)->operator()(x);
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
