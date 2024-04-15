#pragma once
#include <iostream>
#include <limits>
typedef int16_t(*Function)(int16_t);
class ModifiableIntegersFunction
{
private:
	struct MapNumber {
		int key;
		int value;
		bool isUndefined = false;
	};
	Function func;
	static const int MAX_VALUES = INT16_MAX * 2 + 1;
	
	MapNumber* specialNumbers = nullptr;
	unsigned specialNumbersLength = 0;
	unsigned capacity = 2;
	void free();
	void copyFrom(const ModifiableIntegersFunction& other);
public:
	static int16_t addHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
	static int16_t subtractHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
	static int16_t compositeHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);

	ModifiableIntegersFunction(int16_t(*_func)(int16_t num));
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	void addSpecialNumber(int16_t key, int16_t value);
	void excludePoint(int16_t key);
	int callFunction(int16_t number) const;
	friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2);
	friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2);
	ModifiableIntegersFunction operator()(const ModifiableIntegersFunction& func) const;
	bool isUndefinedAt(int16_t x) const;
	~ModifiableIntegersFunction();

private:
	
	void resize();
	int containsKeyAndReturnIndex(int16_t key) const;
	

};
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

