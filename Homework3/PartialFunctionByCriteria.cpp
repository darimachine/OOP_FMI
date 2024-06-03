#include "PartialFunctionByCriteria.h"
#include "FirstCriteria.h"
#include "SecondCriteria.h"
#include "ThirdCriteria.h"

template<class T>
bool PartialFunctionByCriteria<T>::isDefined(int x) const
{
	Pair<bool, int> result = func(x);
	return  result.getFirst();
}

template<class T>
int PartialFunctionByCriteria<T>::operator()(int x) const
{
	Pair<bool, int> pair = func(x);
	if (pair.getFirst())
	{
		return pair.getSecond();
	}
	else {
		throw std::exception("Undefined");
	}

}

template<class T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& func) :
	func(func)
{
}

template<class T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}

//Template specialization FOR only which functions can ACCEEPT
typedef Pair<bool, int>(*FuncType)(int);
template PartialFunctionByCriteria<FuncType>;
template PartialFunctionByCriteria<FirstCriteria>;//0
template PartialFunctionByCriteria<SecondCriteria>;//1
template PartialFunctionByCriteria<ThirdCriteria>;//2

