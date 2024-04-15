
#include <iostream>
#include "MultiSet.h"
using std::cout;
using std::endl;
#pragma warning(disable : 4996)
void MultiSet::free()
{
	delete[] data;
}

void MultiSet::copyFrom(const MultiSet& other)
{
	
	dataLength = other.dataLength;
	data = new byte[dataLength+1];
	for (int i = 0; i < dataLength; i++)
	{
		data[i] = other.data[i];
	}
	data[dataLength] = '\0';
	//strcpy(data, other.data);;
	N = other.N;
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (&other != this)
	{
		free();
		copyFrom(other);
	}
	return *this;
	
}

MultiSet::MultiSet(int n)
{
	dataLength = getBucketIndex(n)+1;
	data = new byte[dataLength]{0};
	N = n;
}

void MultiSet::add(int num)
{
	int index = getBucketIndex(num);
	int shiftAmount = (num % elementsInBucket) * 2;
	if (!isContains(num))
	{
		data[index] |= 1 << shiftAmount;
	}
	else if (isThreeOcurrence(index,shiftAmount)) // 11
	{
		cout<<"You reached maximum number\n";
	}
	else if (isOneOccurence(index,shiftAmount)) // 01
	{
		data[index] &= ~(1 << shiftAmount);
		data[index] |= 1 << shiftAmount + 1;
	}
	else if(isTwoOccurence(index,shiftAmount)) // 10
	{
		data[index] |= 1 << shiftAmount;
	}
}
void MultiSet::remove(int num)
{
	int index = getBucketIndex(num);
	int shiftAmount = (num % elementsInBucket) *2;
	if (!isContains(num))
	{
		cout << "There is no number to remove\n";
	}
	else if (isOneOccurence(index,shiftAmount)) // 01 
	{
		data[index] &= ~(1 << shiftAmount);
	}
	else if (isTwoOccurence(index, shiftAmount)) // 10
	{
		data[index] &= ~(1 << shiftAmount + 1);
		data[index] |= 1 << shiftAmount;
	}
	else if (isThreeOcurrence(index, shiftAmount)) // 11
	{
		data[index] &= ~(1 << shiftAmount);
	}

}
void MultiSet::print() const
{
	for (int i = 0; i < N; i++)
	{
		if (isContains(i)) {
			int occurencies = getNumberOccurencie(i);
			for (int j = 0; j < occurencies; j++)
			{
				cout << i<<" ,";
			}
		}
	}
}



MultiSet::~MultiSet()
{
	free();
}

bool MultiSet::isContains(int num) const
{
	int index = getBucketIndex(num);
	int shiftAmount = (num % elementsInBucket) * 2;
	if ((data[index] & 1 << shiftAmount) || (data[index] & 1 << shiftAmount + 1)) {
		return true;
	}
	return false;
}

int MultiSet::getBucketIndex(int num) const
{
	return (num / elementsInBucket);
}

bool MultiSet::isOneOccurence(int index, int shiftAmount) const // ako veche e dobaveno chislo i se sreshta 1 put
{
	return ((data[index] & 1 << shiftAmount) && !(data[index] & 1 << shiftAmount + 1));
}

bool MultiSet::isTwoOccurence(int index, int shiftAmount) const
{
	return (!(data[index] & 1 << shiftAmount) && (data[index] & 1 << shiftAmount + 1));
}

bool MultiSet::isThreeOcurrence(int index, int shiftAmount) const
{
	return (data[index] & 1 << shiftAmount) && (data[index] & 1 << shiftAmount + 1);
}

int MultiSet::getNumberOccurencie(int num) const
{
	int index = getBucketIndex(num);
	int shiftAmount = (num % elementsInBucket) * 2;
	byte mask = data[index] & 3 << shiftAmount;
	return (mask >> shiftAmount);
}

MultiSet intersection(const MultiSet& set1, const MultiSet& set2)
{
	int minN = std::min(set1.N, set2.N);
	int minDataLength = std::min(set1.dataLength, set2.dataLength);
	MultiSet set(minN);
	for (int i = 0; i < minDataLength; i++)
	{
		//if(isContains())
		if (set1.isContains(i) && set2.isContains(i))
		{
			int minOccurence = std::min(set1.getNumberOccurencie(i), set2.getNumberOccurencie(i));
			for (int j = 0; j < minOccurence; j++)
			{
				set.add(i);
			}
		}
		
	}
	return set;
}
MultiSet unionSets(const MultiSet& set1, const MultiSet& set2) {
	int maxN;
	MultiSet maxSet;
	if (set1.N > set2.N)
	{
		maxSet = set1;
		maxN = set1.N;
	}
	else {
		maxN = set2.N;
		maxSet = set2;
	}
	MultiSet setToReturn(maxN);
	int minN = std::min(set1.N, set2.N);
	 
	int i = 0;
	for (; i < minN; i++)
	{
		if (set1.isContains(i) || set2.isContains(i))
		{
			int maxOcurrencieBetweenSet = std::max(set1.getNumberOccurencie(i), set2.getNumberOccurencie(i));
			for (int j = 0; j < maxOcurrencieBetweenSet; j++)
			{
				setToReturn.add(i);
			}
		}
	}

	for ( i; i < maxN; i++)
	{
		if (maxSet.isContains(i)) {
			int maxOcurrencieBetweenSet = maxSet.getNumberOccurencie(i);
			for (int j = 0; j < maxOcurrencieBetweenSet; j++)
			{
				setToReturn.add(i);
			}
		}
	}

	return setToReturn;
}