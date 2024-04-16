#pragma once
#include <iostream>
#include <limits>

struct KeyCheck {
	int key;
	bool isAvaible = false;
};
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
	static const int MAX_VALUES = INT16_MAX;
	int posibleNumbers[MAX_VALUES];
	int posibleNumberSize = 0;
	MapNumber* specialNumbers = nullptr;
	unsigned specialNumbersLength = 0;
	unsigned capacity = 2;

	int repeatCount = 0;
	void free();
	void copyFrom(const ModifiableIntegersFunction& other);
public:

	static int16_t addHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
	static int16_t subtractHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
	static int16_t compositeHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
	ModifiableIntegersFunction() : func([](int16_t x) { return x; }) {};
	ModifiableIntegersFunction(Function f);
	ModifiableIntegersFunction(Function f,int repeat);
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	void addSpecialNumber(int16_t key, int16_t value);
	void excludePoint(int16_t key);
	int callFunction(int16_t number) const;
	friend ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2);
	friend ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2);
	ModifiableIntegersFunction operator()(const ModifiableIntegersFunction& func) const;
	int16_t operator()(int16_t x) const;
	int16_t inverse(int x) const;
	ModifiableIntegersFunction operator^(int k) const;
	bool isUndefinedAt(int16_t x) const;
	~ModifiableIntegersFunction();

private:
	
	void resize();
	void writeAllPosibleInputsInArray();
	KeyCheck containsKeyAndReturnIndex(int16_t key) const;
	KeyCheck containsValueAndReturnIndex(int16_t value) const;
	

};
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs) ;
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs); //parallel


