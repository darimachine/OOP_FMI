#pragma once
#include "PartialFunction.h"
#include "Pair.hpp"

template <class T>
class PartialFunctionByCriteria : public PartialFunction
{
	T func;

public:
	// Inherited via PartialFunction
	bool isDefined(int x) const override;
	int operator()(int x) const override;

	PartialFunctionByCriteria(const T& func);

	// Inherited via PartialFunction
	PartialFunction* clone() const override;
};

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
	std::cout << "Undefined";
	return -1;
	
}

template<class T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& func):
	func(func)
{
}

template<class T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}
