#include "ModifiableIntegersFunction.h"

#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
constexpr int START = INT16_MIN;
constexpr int END = INT16_MAX;

void ModifiableIntegersFunction::free()
{
	for (int i = 0; i < rangeSize; i++)
	{
		delete range[i];
		
	}
	delete[] range;
	
	delete[] cache;
	
	
}
void ModifiableIntegersFunction::copyFrom(const ModifiableIntegersFunction& other)
{
	operation = other.operation;
	left = other.left;
	right = other.right;
	func = other.func;
	range = new int16_t *[MAX_SIZE] {nullptr};
	rangeSize = other.rangeSize;
	for (size_t i = 0; i < rangeSize; i++)
	{		
		if (other.range[i])
		{
			range[i] = new int16_t(*other.range[i]);
		}
		else {
			range[i] = nullptr;
		}
		
	}
	cache = new bool[MAX_SIZE] {false};
	for (int i = 0; i < MAX_SIZE; i++)
	{
		cache[i] = other.cache[i];
	}
	isSurjective = other.isSurjective;
	isInjective = other.isInjective;
	composeCounter = other.composeCounter;
}

// Initializes a function with specified operation and operand functions.
ModifiableIntegersFunction::ModifiableIntegersFunction(OperationType op, const ModifiableIntegersFunction* l, const ModifiableIntegersFunction* r)
	: operation(op), left(l), right(r), func(l->func) {
	range = new int16_t * [MAX_SIZE] {nullptr};
	cache = new bool[MAX_SIZE] {false};
	writeAllPosibleInputsInArray();
}

// Initializes a function with specified operation, operand functions, and a custom function.
ModifiableIntegersFunction::ModifiableIntegersFunction(OperationType op, const ModifiableIntegersFunction* l, const ModifiableIntegersFunction* r, const Function& f)
	:operation(op),left(l),right(r),func(f)
{
	range = new int16_t * [MAX_SIZE] {nullptr};
	cache = new bool[MAX_SIZE] {false};
	writeAllPosibleInputsInArray();
}
// Default constructor using an identity function.
ModifiableIntegersFunction::ModifiableIntegersFunction() :ModifiableIntegersFunction([](int16_t x)->int16_t {return x; })
{}

// Initializes the function with a specified function pointer.
ModifiableIntegersFunction::ModifiableIntegersFunction(const Function& f):func(f)
{
	range = new int16_t*[MAX_SIZE] {nullptr};
	cache = new bool[MAX_SIZE] {false};
	writeAllPosibleInputsInArray();
}
//Copy-Constructor
ModifiableIntegersFunction::ModifiableIntegersFunction(const ModifiableIntegersFunction& other)
{
	copyFrom(other);
	
}
// Op =
ModifiableIntegersFunction& ModifiableIntegersFunction::operator=(const ModifiableIntegersFunction& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
	
}

// Adds a specific output for a given input, updating injectivity and surjectivity status.
void ModifiableIntegersFunction::addSpecificNumber(int16_t dom, int16_t ran)
{
	int index = dom + END + 1;
	
	if (range[index])
	{
		*range[index] = ran;
	}
	else {
		range[index] = new int16_t(ran);
	}
	injectiveCheck(ran); // Update injectivity status
	surjectiveCheck(); // Update surjectivity status
}

// Excludes a specific input point by setting its output to undefined.
void ModifiableIntegersFunction::excludePoint(int16_t num)
{
	delete range[num -START];
	range[num-START] = nullptr;
}

// Returns true if the function is injective.
bool ModifiableIntegersFunction::getInjective() const
{
	return isInjective;
}

// Returns true if the function is surjective.
bool ModifiableIntegersFunction::getSurjective() const
{
	return isSurjective;
}

// Returns true if the function is bijective (both injective and surjective).
bool ModifiableIntegersFunction::getBijective() const
{
	return isInjective && isSurjective;
}

// Plots the function within a specified domain and range, ensuring graphical dimensions.
void plotFunction(ModifiableIntegersFunction& func, int x1, int x2, int y1, int y2)
{
	if ((x2 - x1 != 20) || (y2 - y1 != 20)) {
		std::cout << "x2 - x1 and y2 - y1 must both be 20" << std::endl;
		return;
	}

	const int width = 41;  // width of the plot area
	const int height = 21; // height of the plot area
	char grid[height][width + 1]; // +1 for null terminator

	// Initialize grid with spaces
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grid[i][j] = ' ';
		}
		grid[i][width] = '\0'; // Null-terminate each row for easy printing
	}

	// Scaling factors
	double scaleX = (x2 - x1) / (double)(width - 1);
	double scaleY = (y2 - y1) / (double)(height - 1);

	// Number of columns to shift the function to the left

	// Plot the function more densely
	for (double i = 0; i < width; i += 0.5) {  // Smaller increment
		int valueX = x1 + (int)(i * scaleX);
		int16_t y = func(valueX); // Evaluate function at x
		int j = (int)((y - y1) / scaleY);

		if (j >= 0 && j < height) {
			grid[height - j - 1][(int)(i)] = 'x'; // Use '#' for denser plotting
		}
	}

	// Plot the x-axis and y-axis
	int yAxisPosition = (0 - y1) / scaleY; // y-axis position
	int xAxisPosition = (-x1) / scaleX;   // x-axis position

	for (int i = 0; i < height; i++) {
		grid[i][xAxisPosition] = '|'; // Plot the y-axis
	}
	for (int j = 0; j < width; j++) {
		grid[yAxisPosition][j] = '-'; // Plot the x-axis
	}
	grid[yAxisPosition][xAxisPosition] = '+'; // Mark the origin

	// Output the grid
	for (int i = 0; i < height; i++) {
		std::cout << grid[i] << std::endl;
	}
}


// Overloads the '^' operator to apply function composition 'k' times. 
// If 'k' is less than or equal to 1, it simply returns a copy of the current function.
ModifiableIntegersFunction ModifiableIntegersFunction::operator^(int k)
{
	if (k <= 1) {
		return ModifiableIntegersFunction(*this);
	}
	 // FOR NRVO IF IS WORKING IT WILL CAUSE PROBLEMS NOW IT WILL NOT!!!!
	ModifiableIntegersFunction result(*this);
	result.rangeSize = 0;
	
	result.composeCounter = k;
	result.writeAllPosibleInputsInArray();
	
	 // Set the composition counter to 'k' for repeated application.
	
	return result;
}



// Creates an inverse of the function 'f1'. Requires the function to be bijective to succeed.
ModifiableIntegersFunction inverse(const ModifiableIntegersFunction& f1)
{
	//BIJECTIVE CHECK UNCOMENT TO WORK
	/*if (!f1.getBijective())
	{
		throw std::exception("Function is not bijective cannot take inverse");
	}*/

	int index = 0;
	ModifiableIntegersFunction result = f1;

	for (int16_t i = START; i < END; i++) {
		if (f1.range[index] != nullptr) {
			int16_t funcValue = *f1.range[index];
			int invIndex = funcValue - START;
			if (result.range[invIndex])
			{
				*result.range[invIndex] = i;
			}
			else {
				result.range[invIndex] = new int16_t(i);
			}
			
		}
		index++;
	}
	return result;
}

// Recalculates the function value for the input 'x'. This method re-evaluates the function 
// regardless of caching, which allows re-computation in case of state changes affecting the function.
int16_t ModifiableIntegersFunction::call(int16_t x) const
{
	if (isUndefinedAt(x))
	{
	
		throw std::runtime_error("function not defined for this point");
	}

	switch (operation) {

	case OperationType::None:
		return *(range[x + END + 1]);  // Directly use the stored function

	case OperationType::Add:
	{
		int result = x;
		for (int i = 0; i < composeCounter; i++)
		{
			result = (*left)(result) + (*right)(result);
		}
		return result;

	}
	case OperationType::Subtract:
	{
		int result = x;
		for (int i = 0; i < composeCounter; i++)
		{
			result = (*left)(result) - (*right)(result);
		}
		return result;
	}
	default:
		throw std::runtime_error("Unsupported operation");
	}
}

// Retrieves the function value for the input 'x' from the cache, throwing an exception if undefined.
int16_t ModifiableIntegersFunction::operator()(int16_t x) const
{
	
	if (isUndefinedAt(x))
	{	
		throw std::runtime_error("function not defined for this point");
	}
	return *(range[x - START]);
	
}

// Serializes the function's state to a binary file.
void ModifiableIntegersFunction::serialize(const char* filename) const
{
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		throw std::exception("File could't open");
	}
	file.write((const char*)&isInjective, sizeof(isInjective));
	file.write((const char*)&isSurjective, sizeof(isSurjective));
	for (int i = 0; i < MAX_SIZE; i++)
	{
		file.write((const char*)&cache[i], sizeof(bool));
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		file.write((const char*)range[i], sizeof(int16_t));
	}
	
	file.close();
}

void ModifiableIntegersFunction::deserialize(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		throw std::exception("File could't open");
	}
	file.read((char*)&isInjective, sizeof(isInjective));
	file.read((char*)&isSurjective, sizeof(isSurjective));
	
	
	for (int i = 0; i < MAX_SIZE; i++)
	{
		file.read((char*)&cache[i], sizeof(bool));
	}
	for (int i = 0; i < MAX_SIZE; i++)
	{
		file.read((char*)range[i], sizeof(int16_t));
	}
	
	file.close();
}

ModifiableIntegersFunction::~ModifiableIntegersFunction()
{
	free();
}

// Checks if adding a specific number affects the injectivity of the function.
void ModifiableIntegersFunction::injectiveCheck(int16_t number)
{
	if (cache[number - START])
	{
		isInjective = false;
	}
	cache[number - START] = true;
}

// Checks the entire domain to determine if the function is surjective.
void ModifiableIntegersFunction::surjectiveCheck()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (!cache[i]) {
			isSurjective = false;
		}
	}
}

// Writes all possible outputs of the function into the `range` array based on the current operation.
void ModifiableIntegersFunction::writeAllPosibleInputsInArray()
{
	
	switch (operation)
	{
		case OperationType::None:
			for (int i = START; i <= END; i++)
			{
				int16_t number = func(i);
				for (int j = 0; j < composeCounter-1; j++) // for COMPOSOSED FUNCTIONS... TO BE CORRECYTLY IMPLEMENTED RANGE ARRAY!!!!!
				{
					number = func(number);
				}
				if (range[rangeSize])
				{
					*range[rangeSize++] = number;
				}
				else {
					range[rangeSize++] = new int16_t(number);
				}
				injectiveCheck(number);
			}
			break;
		case OperationType::Add:
			for (int i = START; i <= END; i++)
			{
				try {

					int16_t number = (*left)(i) + (*right)(i);
					for (int j = 0; j < composeCounter - 1; j++)
					{
						number = (*left)(number) + (*right)(number);
					}
				
					if (range[rangeSize])
					{
						*range[rangeSize++] = number;
					}
					else {
						
						range[rangeSize++] = new int16_t(number);
					}
				
					injectiveCheck(number);
				}
				catch (std::runtime_error& er)
				{
					delete range[rangeSize];
					range[rangeSize++] = nullptr;
				}
				
			}
			break;
		case OperationType::Subtract:
			
			for (int i = START; i <= END; i++)
			{
				try {
					int16_t number = (*left)(i) - (*right)(i);
					for (int j = 0; j < composeCounter - 1; j++)
					{
						number = (*left)(number) - (*right)(number);
					}
					if (range[rangeSize])
					{
						*range[rangeSize++] = number;
					}
					else {
						range[rangeSize++] = new int16_t(number);
					}
					injectiveCheck(number);
				}
				catch (std::runtime_error& er)
				{
					delete range[rangeSize];
					range[rangeSize++] = nullptr;
				}
				
			}
			break;
		default:
			break;
	}
	surjectiveCheck(); // Update the surjectivity status after modifying the function's range

	
}

// Checks if the function is undefined at a specific input.
bool ModifiableIntegersFunction::isUndefinedAt(int num) const
{
	return !range[num + END + 1];
}

// Overloads the addition operator to create a new function that represents the sum of two functions.
ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2)
{
	return ModifiableIntegersFunction(OperationType::Add,&f1,&f2);
}

// Overloads the subtraction operator to create a new function that represents the difference between two functions.
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2)
{
	return ModifiableIntegersFunction(OperationType::Subtract,&f1,&f2);
}

// Overloads the less-than operator to compare two functions based on their outputs.
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	for (int16_t i = START; i < END; i++)
	{
		int lhsResult = lhs.isUndefinedAt(i) ? INT16_MIN : lhs(i);
		int rhsResult = rhs.isUndefinedAt(i) ? INT16_MIN : rhs(i);
		if (lhsResult > rhsResult)
		{
			return false;
		}
	}
	return true;
}

// Overloads the greater-than operator to compare two functions based on their outputs.
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	for (int16_t i = START; i < END; i++)
	{
		int lhsResult = lhs.isUndefinedAt(i) ? INT16_MIN : lhs(i);
		int rhsResult = rhs.isUndefinedAt(i) ? INT16_MIN : rhs(i);
		if (lhsResult < rhsResult)
		{
			return false;
		}
	}
	return true;
}

// Overloads the equality operator to determine if two functions are identical.
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{

	for (int16_t i = START; i < END; i++)
	{
		int lhsResult = lhs.isUndefinedAt(i) ? INT16_MIN : lhs(i);
		int rhsResult = rhs.isUndefinedAt(i) ? INT16_MIN : rhs(i);
		if (lhsResult != rhsResult)
		{
			return false;
		}
	}
	return true;
}

// Overloads the not-equal operator to determine if two functions are not identical.
bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	return !(lhs==rhs);
}

// Overloads the logical OR operator to check if two functions are parallel.
bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs)
{
	int startDifference = lhs(START) - rhs(START);
	for (int i = START+1; i < END; i++)
	{
		int currentDifference = lhs(i) - rhs(i);
		if (std::abs(startDifference - currentDifference) > 0)
		{
			return false;
		}
	}
	return true;
}
