#pragma once

typedef char byte;
class MultiSet {
	byte* data = nullptr;
	unsigned dataLength=0;
	const unsigned elementsInBucket = 4;
	unsigned N = 0;
	void free();

	void copyFrom(const MultiSet& other);

public:
	MultiSet() = default;
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	MultiSet(int n);
	void add(int num);
	void print() const;
	void remove(int num);




	int getNumberOccurencie(int num) const;

	friend MultiSet intersection(const MultiSet& set1,const MultiSet& set2);

	friend MultiSet unionSets(const MultiSet& set1, const MultiSet& set2);

	~MultiSet();
private:
	bool isContains(int num) const;
	int getBucketIndex(int num) const;
	bool isOneOccurence(int index,int shiftAmount) const;
	bool isTwoOccurence(int index, int shiftAmount) const;
	bool isThreeOcurrence(int index, int shiftAmount) const;
};