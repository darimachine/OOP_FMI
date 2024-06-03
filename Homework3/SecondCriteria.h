#pragma once
#include "Pair.hpp"
#include "CriteriaInterface.h"
class SecondCriteria :public CriteriaInterface
{

public:
	SecondCriteria(int* args, uint16_t N);

	Pair<bool, int> operator()(int x) const override;

};
