#pragma once
#include "Pair.hpp"
class ThirdCriteria
{
	int args[MAX_SIZE];
	uint16_t N;
	int findIndex(int x) const;
public:
	ThirdCriteria(int * args,uint16_t N);

	Pair<bool, int> operator()(int x) const;
};

