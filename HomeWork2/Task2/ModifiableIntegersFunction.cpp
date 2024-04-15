#include "ModifiableIntegersFunction.h"
using std::cout;
using std::endl;
void ModifiableIntegersFunction::free()
{
	delete[] specialNumbers;
}
void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	
	func = other.func;
	specialNumbersLength = other.specialNumbersLength;
	capacity = other.capacity;
	specialNumbers = new MapNumber[capacity];
	for (int i = 0; i < specialNumbersLength; i++)
	{
		specialNumbers[i] = other.specialNumbers[i];
	}

}
int16_t ModifiableIntegersFunction::addHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2)
{
	
	if (f1.isUndefinedAt(x) || f2.isUndefinedAt(x))
	{
		throw std::exception("Its Undefined");
	}
	return f1.func(x) + f2.func(x);
}
int16_t ModifiableIntegersFunction::subtractHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2)
{
	if (f1.isUndefinedAt(x) || f2.isUndefinedAt(x))
	{
		throw std::exception("Its Undefined");

	}
	return f1.func(x)-f2.func(x);
}
int16_t ModifiableIntegersFunction::compositeHelper(int16_t x, const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2)
{
	
	if (f1.isUndefinedAt(x) || f2.isUndefinedAt(x))
	{
		throw std::exception("Undefined at", x);
	}
	return f1.func(f2.func(x));
}
ModifiableIntegersFunction::ModifiableIntegersFunction(int16_t(*_func)(int16_t num)): func(_func)
{
	specialNumbers = new MapNumber[capacity];
	
}

ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
}

ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

void ModifiableIntegersFunction::addSpecialNumber(int16_t key, int16_t value)
{
	int keyIndex = containsKeyAndReturnIndex(key);
	if (keyIndex != -1)
	{
		specialNumbers[keyIndex].key = key;
		specialNumbers[keyIndex].value = value;
	}
	else {
		if (specialNumbersLength == capacity)
		{
			resize();
		}
		specialNumbers[specialNumbersLength].key = key;
		specialNumbers[specialNumbersLength].value = value;
		specialNumbersLength++;
	}
}

void ModifiableIntegersFunction::excludePoint(int16_t number)
{
	int index = containsKeyAndReturnIndex(number);
	if(index!=-1)
	{
		specialNumbers[index].isUndefined = true;
	}
	else {
		if (specialNumbersLength == capacity)
		{
			resize();
		}
		specialNumbers[specialNumbersLength].isUndefined = true;
		specialNumbers[specialNumbersLength].key = number;
		specialNumbers[specialNumbersLength].value = 0;
		specialNumbersLength++;
	}

}

int ModifiableIntegersFunction::callFunction(int16_t number) const
{
	int index = containsKeyAndReturnIndex(number);
	if (index != -1)
	{
		if (specialNumbers[index].isUndefined)
		{
			throw std::exception("Function is Undefined for this input\n");
		}
		return specialNumbers[index].value;
		
	}
	return func(number);
}



ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

void ModifiableIntegersFunction::resize()
{
	
	MapNumber* newMap = new MapNumber[capacity*=2];
	for (int i = 0; i < specialNumbersLength; i++)
	{
		newMap[i] = specialNumbers[i];
	}
	delete[] specialNumbers;
	specialNumbers = newMap;

}

int ModifiableIntegersFunction::containsKeyAndReturnIndex(int16_t key) const
{
	for (int i = 0; i < specialNumbersLength; i++)
	{
		if (specialNumbers[i].key == key) {
			return i;
		}
	}
	return -1;
}

bool ModifiableIntegersFunction::isUndefinedAt(int16_t x) const
{
	int index = containsKeyAndReturnIndex(x);
	if (index != -1)
	{
		return specialNumbers[index].isUndefined;
	}
	return false;
	
}

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2)
{
	static ModifiableIntegersFunction f1 = func1;
	static ModifiableIntegersFunction f2 = func2;
	
	/*ModifiableIntegersFunction result([](int16_t x)->int16_t {
		return f1.callFunction(x) + f2.callFunction(x); 
		});*/
	ModifiableIntegersFunction result([](int16_t x)->int16_t {
		return ModifiableIntegersFunction::addHelper(x, f1, f2); });
	

	return result;
}

ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& func1, const ModifiableIntegersFunction& func2)
{
	static ModifiableIntegersFunction f1 = func1;
	static ModifiableIntegersFunction f2 = func2;

	/*ModifiableIntegersFunction result([](int16_t x)->int16_t {
		return f1.callFunction(x) - f2.callFunction(x);
		});*/
	ModifiableIntegersFunction result([](int16_t x)->int16_t {
		return ModifiableIntegersFunction::subtractHelper(x, f1, f2); });


	return result;
}
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = INT16_MIN; i < INT16_MAX; i++)
	{
		
		int lhsResult = lhs.isUndefinedAt(i)?INT16_MIN:lhs.callFunction(i);
		int rhsResult= rhs.isUndefinedAt(i)?INT16_MIN:rhs.callFunction(i);
		if (lhsResult >= rhsResult)
		{
			return false;
		}
		
	}
	return true;
}
ModifiableIntegersFunction ModifiableIntegersFunction::operator()(const ModifiableIntegersFunction& func1) const
{
	static ModifiableIntegersFunction f1 = *this;
	static ModifiableIntegersFunction f2 = func1;
	ModifiableIntegersFunction result([](int16_t x)->int16_t {

		return compositeHelper(x,f1,f2);
		});
	return result;
}
