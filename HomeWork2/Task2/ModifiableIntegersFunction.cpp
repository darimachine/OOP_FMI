#include "ModifiableIntegersFunction.h"
using std::cout;
using std::endl;

constexpr int START = -5000; // random value BECAUSE ITS OVERFLOWS IMPOSIBLE TO FIX
constexpr int END = 5000;
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
ModifiableIntegersFunction::ModifiableIntegersFunction(Function _func): func(_func)
{
	specialNumbers = new MapNumber[capacity];
	writeAllPosibleInputsInArray();
	
}

ModifiableIntegersFunction::ModifiableIntegersFunction(Function f, int _repeatCount):func(f),repeatCount(_repeatCount)
{}

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
	KeyCheck check = containsKeyAndReturnIndex(key);
	if (check.isAvaible)
	{
		specialNumbers[check.key].key = key;
		specialNumbers[check.key].value = value;
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
	KeyCheck check = containsKeyAndReturnIndex(number);
	if(check.isAvaible)
	{
		specialNumbers[check.key].isUndefined = true;
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
	KeyCheck check = containsKeyAndReturnIndex(number);
	if (check.isAvaible)
	{
		if (specialNumbers[check.key].isUndefined)
		{
			throw std::exception("Function is Undefined for this input\n");
		}
		return specialNumbers[check.key].value;
		
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

void ModifiableIntegersFunction::writeAllPosibleInputsInArray()
{

	for (int i = START; i <= END; i++)
	{
		posibleNumbers[posibleNumberSize++] = func(i);
	}
}
int16_t ModifiableIntegersFunction::inverse(int x) const
{
	KeyCheck check = containsValueAndReturnIndex(x);
	if (check.isAvaible)
	{
		return check.key;
	}
	
	for (int i = 0; i < posibleNumberSize; i++)
	{
		if (posibleNumbers[i]==x)
		{
			return i-END;
		}
	}
	return -1;
}
KeyCheck ModifiableIntegersFunction::containsKeyAndReturnIndex(int16_t key) const
{
	KeyCheck check;
	for (int i = 0; i < specialNumbersLength; i++)
	{
		if (specialNumbers[i].key == key) {
			check.key = i;
			check.isAvaible = true;
			return check;
		}
	}
	return check;
}

KeyCheck ModifiableIntegersFunction::containsValueAndReturnIndex(int16_t value) const
{
	KeyCheck valueCheck;
	for (int i = 0; i < specialNumbersLength; i++)
	{
		if (specialNumbers[i].value == value) {
			valueCheck.key = specialNumbers[i].key;
			valueCheck.isAvaible = true;
			return valueCheck;
		}
	}
	return valueCheck;
}


bool ModifiableIntegersFunction::isUndefinedAt(int16_t x) const
{
	KeyCheck check = containsKeyAndReturnIndex(x);
	if (check.isAvaible)
	{
		return specialNumbers[check.key].isUndefined;
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
		return ModifiableIntegersFunction::addHelper(x, f1, f2);
		});
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
	
	for (int16_t i = START; i <= END; i++)
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
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = START; i <= END; i++)
	{

		int lhsResult = lhs.isUndefinedAt(i) ? INT16_MIN : lhs.callFunction(i);
		int rhsResult = rhs.isUndefinedAt(i) ? INT16_MIN : rhs.callFunction(i);
		if (lhsResult <= rhsResult)
		{
			return false;
		}

	}
	return true;
	
}
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	for (int16_t i = START; i <= END; i++)
	{

		int lhsResult = lhs.isUndefinedAt(i) ? INT16_MIN : lhs.callFunction(i);
		int rhsResult = rhs.isUndefinedAt(i) ? INT16_MIN : rhs.callFunction(i);
		if (lhsResult != rhsResult)
		{
			return false;
		}

	}
	return true;
}
bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	
	int startDifference = lhs.callFunction(START) - rhs.callFunction(START);
	for (int i = START +1; i <= END; i++)
	{
		int currentDifference = lhs.callFunction(i) - rhs.callFunction(i);
		if (std::abs(startDifference - currentDifference) > 0.00001)
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

int16_t ModifiableIntegersFunction::operator()(int16_t x) const
{
	int result = x;
	for (int i = 0; i < repeatCount; i++)
	{
		result = func(result);
	}
	return result;
}



ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int k) const
{
	if (k <= 0)
	{
		throw std::logic_error("Invalid K");
	}
	return ModifiableIntegersFunction(func,k);
}
