#pragma once
#include "PartialFunction.h"
#include "PartialFunctionContainer.h"
#include "FirstCriteria.h"
#include "SecondCriteria.h"
#include "ThirdCriteria.h"
#include "PartialFunctionByCriteria.h"
#include "MaximumOfPartialFunction.h"
#include "MinimumOfPartialFunction.h"
#include <fstream>
#include "MyString.h"
//TESTING METHODS
void save();
void save2();
void save3();
void saveFuncDAT();
void saveFunc2Recursion();
void saveFunc2();
//реяр
PartialFunction* factory();
PartialFunction* factory2();
//FUNC
class Factory {

private:
	static PartialFunction* firstCriteriaFactory(std::ifstream& ifs, uint16_t N);
	static PartialFunction* secondCriteriaFactory(std::ifstream& ifs, uint16_t N);
	static PartialFunction* thirdCriteriaFactory(std::ifstream& ifs, uint16_t N);
public:
	static PartialFunction* factoryFunction(const char* filename);
};


//class Factory {
//public:
//	static PartialFunction* createFunction(const char* filename);
//	static PartialFunction* createFunctionFromType(int T,int N)
//};
