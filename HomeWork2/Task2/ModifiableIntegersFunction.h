#pragma once
#include <iostream>
#include <limits>

typedef int16_t(*Function)(int16_t);

//Operands for functions
enum class OperationType {
	None,       
	Add,        
	Subtract,   
};

class ModifiableIntegersFunction
{
private:
	Function func; // Pointer to a function

	OperationType operation =OperationType::None;   // Type of operation to apply in function composition
	const ModifiableIntegersFunction* left;  // Pointer to the left operand function
	const ModifiableIntegersFunction* right;  // Pointer to the right operand function
	
	
	static const long MAX_SIZE = UINT16_MAX + 1; // Maximum size for the range array

	int16_t** range; // Array of pointers to hold function outputs for caching
	int rangeSize = 0; // Actual size of the range array used

	bool* cache; // Array used for injectivity and surjectivity checks
	bool isInjective = true; // Flag to indicate if the function is injective
	bool isSurjective = true; // Flag to indicate if the function is surjective

	//for ^ operator which return new function!!!
	int composeCounter = 1; // Counter to handle the power of function composition (^ operator)

	void free();
	void copyFrom(const ModifiableIntegersFunction& other);

	
public:
	// Constructors
	ModifiableIntegersFunction(); // Default constructor
	ModifiableIntegersFunction(OperationType op, const ModifiableIntegersFunction* l, const ModifiableIntegersFunction* r,const Function& f);
	ModifiableIntegersFunction(OperationType op, const ModifiableIntegersFunction* l, const ModifiableIntegersFunction* r);
	ModifiableIntegersFunction(const Function& f);
	
	//Copy-Constructor
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);

	// Methods to modify function behavior
	void addSpecificNumber(int16_t dom, int16_t ran); // Add specific output for a given input
	void excludePoint(int16_t num); // Mark specific input as undefined

	// Checkers for function properties (Getters)
	bool getInjective() const;
	bool getSurjective() const;
	bool getBijective() const;
	bool isUndefinedAt(int num) const;

	
	// Creates an inverse of the given function (Uncomment bijective check)
	friend ModifiableIntegersFunction inverse(const ModifiableIntegersFunction& f1);
		
	ModifiableIntegersFunction operator^(int k); // Applies the function to itself k times(CHANGES composeCounter)
	int16_t call(int16_t x) const; // Calculates the value for the given x
	int16_t operator()(int16_t x) const; // return cached value for the given x
	//file
	void serialize(const char* filename) const;
	void deserialize(const char* filename);

	~ModifiableIntegersFunction();
private:

	void injectiveCheck(int16_t number); // Updates injectivity status based on a specific number's occurrence

	void surjectiveCheck(); // Updates surjectivity status based on the range covered by the function
	void writeAllPosibleInputsInArray(); // Precomputes all possible inputs to populate the range array
	
};

// Plots the function on a specified 2D grid
void plotFunction(ModifiableIntegersFunction& func, int x1, int x2, int y1, int y2);

// Returns a new function representing the addition/subtraction of f1 and f2
ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& f1, const ModifiableIntegersFunction& f2);


bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs); // Checks if two functions are parallel(have outputs differing by a constant offset)
