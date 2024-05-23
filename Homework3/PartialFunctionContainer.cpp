#include "PartialFunctionContainer.h"

void PartialFunctionContainer::free()
{
	for (int i = 0; i < size; i++)
	{
		delete funcs[i];
	}
	delete[] funcs;
}

void PartialFunctionContainer::copyFrom(const PartialFunctionContainer& other)
{
	capacity = other.capacity;
	size = other.size;
	funcs = new PartialFunction * [capacity];
	for (int i = 0; i < size; i++)
	{
		funcs[i] = other.funcs[i]->clone();
	}
}

void PartialFunctionContainer::moveFrom(PartialFunctionContainer&& other)
{
	funcs = other.funcs;
	funcs = nullptr;
	size = other.size;
	other.size = 0;
	capacity = other.capacity;
	other.capacity = 0;
}

void PartialFunctionContainer::resize(unsigned newCap)
{
}

void PartialFunctionContainer::upSizeIfNeed()
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}
}

PartialFunctionContainer::PartialFunctionContainer()
{
	capacity = 8;
	size = 0;
	funcs = new PartialFunction * [capacity];
}

PartialFunctionContainer::PartialFunctionContainer(const PartialFunctionContainer& other)
{
	copyFrom(other);
}

PartialFunctionContainer::PartialFunctionContainer(PartialFunctionContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

PartialFunctionContainer& PartialFunctionContainer::operator=(const PartialFunctionContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	
}

PartialFunctionContainer& PartialFunctionContainer::operator=(PartialFunctionContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
	
	
}

void PartialFunctionContainer::addFunction(PartialFunction* func)
{
	upSizeIfNeed();
	funcs[size++] = func;
}

void PartialFunctionContainer::addFunction(const PartialFunction& func)
{
	upSizeIfNeed();
	funcs[size++] = func.clone();
}

unsigned PartialFunctionContainer::getSize() const
{
	return size;
}

const PartialFunction* PartialFunctionContainer::getFunc(unsigned index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Index out range");
	}
	return funcs[index];
}

PartialFunctionContainer::~PartialFunctionContainer()
{
	free();
}
