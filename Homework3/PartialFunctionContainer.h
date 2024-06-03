#pragma once
#include "PartialFunction.h"
class PartialFunctionContainer
{
	PartialFunction** funcs;
	unsigned size = 0;
	unsigned capacity;

	void free();
	void copyFrom(const PartialFunctionContainer& other);
	void moveFrom(PartialFunctionContainer&& other);

	void resize(unsigned newCap);
	void upSizeIfNeed();
public:
	PartialFunctionContainer();
	
	PartialFunctionContainer(const PartialFunctionContainer& other);
	PartialFunctionContainer(PartialFunctionContainer&& other) noexcept;

	PartialFunctionContainer& operator=(const PartialFunctionContainer& other);
	PartialFunctionContainer& operator=(PartialFunctionContainer&& other) noexcept;

	void addFunction(PartialFunction* func);
	void addFunction(const PartialFunction& func);
	
	//get
	unsigned getSize() const;
	const PartialFunction* getFunc(unsigned index) const;

	~PartialFunctionContainer();



};

