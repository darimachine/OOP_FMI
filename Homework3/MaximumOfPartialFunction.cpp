#include "MaximumOfPartialFunction.h"

MaximumOfPartialFunction::MaximumOfPartialFunction(const PartialFunctionContainer& funcs)
    :functions(funcs)
{
}

bool MaximumOfPartialFunction::isDefined(int x) const
{
    int functionSize = functions.getSize();
    for (int i = 0; i < functionSize; i++)
    {
        if (!functions.getFunc(i)->isDefined(x)) {
            return false;
        }
            
    }
    return true;
}

int MaximumOfPartialFunction::operator()(int x) const
{
    if (!isDefined(x))
    {
        throw std::exception("Error undefined");
    }
    int max = functions.getFunc(0)->operator()(x);
    int functionSize = functions.getSize();
    for (int i = 0; i < functionSize; i++)
    {
        int value= functions.getFunc(i)->operator()(x);
        if (value > max)
        {
            max = value;
        }
    }
    return max;
}

PartialFunction* MaximumOfPartialFunction::clone() const
{
    return new MaximumOfPartialFunction(*this);
}
