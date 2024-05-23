#pragma once
#include <iostream>
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
class MinimumOfPartialFunction : public PartialFunction
{
	PartialFunctionContainer funcs;


public:
	MinimumOfPartialFunction(const PartialFunctionContainer& _funcs);

	// Inherited via PartialFunction
	bool isDefined(int x) const override;
	int operator()(int x) const override;
	PartialFunction* clone() const override;
};

