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


