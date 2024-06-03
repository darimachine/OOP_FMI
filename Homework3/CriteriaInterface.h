#pragma once
#include <iostream>
#include "Pair.hpp"
constexpr int MAX_SIZE = 32;
class CriteriaInterface
{
protected:
	int args[MAX_SIZE];
	uint16_t size;
	int findIndex(int x) const;
public:
	CriteriaInterface(int* args, uint16_t size);

	virtual Pair<bool, int> operator()(int x) const = 0;
};

