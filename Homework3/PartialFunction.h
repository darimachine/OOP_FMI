#pragma once
#include "Pair.hpp"

class PartialFunction
{
public:
	virtual bool isDefined(int x) const = 0;
	virtual int operator()(int x) const = 0;
	virtual PartialFunction* clone() const=0;


	virtual ~PartialFunction() = default;
};

