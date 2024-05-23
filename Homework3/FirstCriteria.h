#pragma once
#include "Pair.hpp"

class FirstCriteria 
{
	int args[MAX_SIZE];
	int res[MAX_SIZE];
	int N;
	int findIndex(int x) const;
public:
	FirstCriteria(int* args, int* res, int N);

	Pair<bool, int> operator()(int x) const;
	
};

