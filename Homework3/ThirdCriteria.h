#pragma once
#include "Pair.hpp"
#include "CriteriaInterface.h"
class ThirdCriteria : public CriteriaInterface
{
public:
	ThirdCriteria(int * args,uint16_t N);

	Pair<bool, int> operator()(int x) const override ;
};

