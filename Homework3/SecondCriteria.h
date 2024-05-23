#pragma once
#include "Pair.hpp"
//constexpr int MAX_SIZE = 32;
class SecondCriteria
{
	int args[MAX_SIZE];
	uint16_t N;
	int findIndex(int x) const;
public:
	SecondCriteria(int* args, uint16_t N);

	Pair<bool, int> operator()(int x) const;

};
