#pragma once
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
class BaseMinMax : public PartialFunction
{
protected:
	PartialFunctionContainer functions;

public:
	BaseMinMax(const PartialFunctionContainer& funcs);
	// Inherited via PartialFunction
	bool isDefined(int x) const override;



};

