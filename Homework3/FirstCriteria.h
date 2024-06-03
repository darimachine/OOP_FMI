#pragma once
#include "Pair.hpp"
#include "CriteriaInterface.h"
class FirstCriteria : public CriteriaInterface
{
	int res[MAX_SIZE];
public:
	FirstCriteria(int* args, int* res, uint16_t N);

	Pair<bool, int> operator()(int x) const override;
	
};

