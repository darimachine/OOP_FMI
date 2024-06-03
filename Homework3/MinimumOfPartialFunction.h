#pragma once
#include <iostream>
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
#include "BaseMinMax.h"
class MinimumOfPartialFunction : public BaseMinMax{
	
public:
	MinimumOfPartialFunction(const PartialFunctionContainer& _funcs);
	int operator()(int x) const override;
	PartialFunction* clone() const override;
};

