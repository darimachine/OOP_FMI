#include "CriteriaInterface.h"

int CriteriaInterface::findIndex(int x) const
{
	for (int i = 0; i < size; i++)
	{
		if (args[i] == x) {
			return i;
		}
	}
	return -1;
}

CriteriaInterface::CriteriaInterface(int* args, uint16_t size)
{
	this->size = size;
	for (int i = 0; i < size; i++)
	{
		this->args[i] = args[i];
	}
}
