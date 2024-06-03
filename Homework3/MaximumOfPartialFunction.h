#pragma once
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
#include "BaseMinMax.h"
//class PartialFunctionContainer;

class MaximumOfPartialFunction : public BaseMinMax
{
	
	// Inherited via PartialFunction
public:
	MaximumOfPartialFunction(const PartialFunctionContainer& _funcs);
	int operator()(int x) const override;

	// Inherited via PartialFunction
	PartialFunction* clone() const override;
};

