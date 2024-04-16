#include "Multiset.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
constexpr int MAX_BITS = 8;
void Multiset::free()
{
    delete[] data;
}
void Multiset::copyFrom(const Multiset& other)
{
    N = other.N;
    dataLength = other.dataLength;
    k = other.k;
    data = new byte[dataLength + 1];
    for (int i = 0; i < dataLength; i++)
    {
        data[i] = other.data[i];
    }
}
Multiset::Multiset(int n, int k)
{
    if (!isValidK(k)) {
        throw std::exception("Invalid K or N");
    }
    dataLength = getTotalBucketCount(n, k);
    data = new byte[dataLength + 1]{ 0 }; // for '\0';
    data[dataLength] = '\0';
    N = n;
    this->k = k;

}

Multiset::Multiset(const Multiset& other)
{
    copyFrom(other);
}

Multiset& Multiset::operator=(const Multiset& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

int Multiset::getN() const
{
    return N;
}

int Multiset::getK() const
{
    return k;
}

void Multiset::printBits() const
{
    for (int i = 0; i < dataLength; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if ( ((N + 1) * k) <= (i * 8 + j))
            {
                cout << "x"; // Print UnUsed Bits
            }
            else if (data[i] & 1 << j) {
                cout << "1";
            }
            else {
                cout << "0";
            }
        }
        cout << "  [" << i << "]";
        cout << endl;
    }
}
bool Multiset::isContains(int num) const
{
    if (!isValidNumber(num))
    {
        cout << "Invalid Number\n";
        return false;
    }
    int numberOccurencie = getNumberOccurencie(num);
    return numberOccurencie != 0;
  
}
int Multiset::getNumberOccurencie(int num) const
{
    if (!isValidNumber(num))
    {
        cout << "Invalid Number\n";
        return 0;
    }
    int index = getDataIndex(num);
    int shift = getShiftAmount(num);

    int maskNumberCount = 0;
    for (int i = 0; i < k; i++)
    {
        if (data[index] & 1 << shift)
        {
            maskNumberCount |= 1 << i;
        }
        shift++;
        if (shift > 7)
        {
            shift = 0;
            index++;
        }
    }
    return maskNumberCount;
}

bool Multiset::isBucketFull(int num) const
{
    int numberOcurrenrie = getNumberOccurencie(num);
    return numberOcurrenrie == k;
}

void Multiset::add(int num)
{
    if (!isValidNumber(num))
    {
        cout << "Invalid Number\n";
        return;
    }
    int index = getDataIndex(num);
    int shift = getShiftAmount(num);
    if (isBucketFull(num))
    {
        cout << "You cannot add more\n";
        return;
    }

    for (int i = 0; i < k; i++)
    {
        int mask = 1 << shift;
        if (data[index] & mask)
        {
            data[index] &= ~(mask);
        }
        else {
            data[index] |= mask;
            break;
        }
        shift++;
        if (shift > 7)
        {
            shift = 0;
            index++;
        }
    }
}


int Multiset::getTotalBucketCount(int n,int k) const
{
    //1 - /8 +1
    //2 - /4 +1
    //3 - /2 
    //4 - /2 + 1
    //5 - (n*K) / 8 + 1
    return ((n+1)*k)%8 ==0 ?(((n+1)*k)/8): (((n + 1) * k) / 8) + 1; // n+1 for the 0 in the beggining (n+1)*k -> total bits used
}

int Multiset::getDataIndex(int num) const
{
    return (num*k)/8;
}

int Multiset::getShiftAmount(int num) const
{
    return (num*k)%8;
}

bool Multiset::isValidK(int k) const
{
    return k>=1 && k<=8;
}

bool Multiset::isValidNumber(int num) const
{
    if (num<0 || num>N) {
        return false;
    }
    return true;
}
void serialize(const char* filename, const Multiset& obj)
{

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::exception("File Cannot be Open");
    }
    file.write((const char*)&obj.N, sizeof(obj.N));
    file.write((const char*)&obj.k, sizeof(obj.k));
    file.write((const char*)&obj.dataLength, sizeof(obj.dataLength));
    for (int i = 0; i < obj.dataLength; i++)
    {
        file.write((const char*)&obj.data[i], sizeof(obj.data[i]));
    }
}

void deSerialize(const char* filename, Multiset& obj)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::exception("File Cannot be Open");
    }
    file.read((char*)&obj.N, sizeof(obj.N));
    file.read((char*)&obj.k, sizeof(obj.k));
    file.read((char*)&obj.dataLength, sizeof(obj.dataLength));
    delete[] obj.data;
    obj.data = new byte[obj.dataLength + 1];
    for (int i = 0; i < obj.dataLength; i++)
    {
        file.read((char*)&obj.data[i], sizeof(obj.data[i]));
    }
    file.close();
}

std::ostream& operator<<(std::ostream& os, const Multiset& obj)
{
    cout << "{ ";
    for (int i = 0; i <= obj.N; i++)
    {
        if (obj.isContains(i)) {
            int numberOccurencie = obj.getNumberOccurencie(i);
            for (int j = 0; j < numberOccurencie; j++)
            {
                cout << i << " ";
            }
        }
    }
    cout << "}\n";
    return os;
}
Multiset intersect(const Multiset& set1, const Multiset& set2)
{
    int minN = std::min(set1.getN(), set2.getN());
    int minK = std::min(set1.getK(), set2.getK());
    Multiset newSet(minN, minK);

    for (int i = 0; i <= minN; i++)
    {
        if (set1.isContains(i) && set2.isContains(i)) {
            int minOccurenrie = std::min(set1.getNumberOccurencie(i), set2.getNumberOccurencie(i));
            for (int j = 0; j < minOccurenrie; j++)
            {
                newSet.add(i);
            }
        }
    }
    return newSet;
}

Multiset difference(const Multiset& set1, const Multiset& set2)
{
    int maxN = std::max(set1.getN(), set2.getN());
    int minN = std::min(set1.getN(), set2.getN());
    int maxK = std::max(set1.getK(), set2.getK());
    Multiset result(set1.getN(), set1.getK());
    const Multiset higherNCount = set1.getN()>set2.getN() ? set1 : set2;
    int i = 0;
    for (; i <= set1.getN(); i++)
    {
        if (set1.isContains(i) || set2.isContains(i))
        {
            int numberOccuriencieSet1 = set1.getNumberOccurencie(i);
            int numberOccuriencieSet2 = set2.getNumberOccurencie(i);
            int difference = std::abs(numberOccuriencieSet1 - numberOccuriencieSet2);
            for (int j = 0; j < difference; j++)
            {
                result.add(i);
            }
        }
    }
   /* for (; i <= maxN; i++)
    {
        if (higherNCount.isContains(i))
        {
            int numberOccuriencie = higherNCount.getNumberOccurencie(i);
            for (int j = 0; j < numberOccuriencie; j++)
            {
                result.add(i);
            }
        }
    }*/
    return result;
}
Multiset complement(const Multiset& set)
{
    Multiset result(set.N, set.k);
    for (int i = 0; i < set.dataLength; i++)
    {
        result.data[i] = ~(set.data[i]);
    }
    return result;
}

Multiset::~Multiset()
{
    free();
}
