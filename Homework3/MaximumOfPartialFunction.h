#pragma once
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
//class PartialFunctionContainer;

class MaximumOfPartialFunction : public PartialFunction
{
	PartialFunctionContainer functions;
	// Inherited via PartialFunction
public:
	MaximumOfPartialFunction(const PartialFunctionContainer& funcs);
	bool isDefined(int x) const override;
	int operator()(int x) const override;

	// Inherited via PartialFunction
	PartialFunction* clone() const override;
};

