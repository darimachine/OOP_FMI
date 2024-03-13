#include <iostream>
#include <cstring>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;
constexpr int MAX_NAME_LENGTH = 20;
enum class Major {
	SI,
	IS,
	KN,
	I,
	Unknown
};
struct Student {
	char name[MAX_NAME_LENGTH]="";
	unsigned fn;
	Major major = Major::Unknown;

};
constexpr int STUDENT_MAX_SIZE = 10;
struct StudentDatabase {
	unsigned studentCount = 0;
	Student students[STUDENT_MAX_SIZE];
};
enum class Criteria {
	sortByName,
	sortByFn,
	sortByMajor
};
const char* getMajor(Major mj)
{
	switch (mj)
	{
		case Major::SI: {
			return "SI";
			break;
		}
		case Major::IS: {
			return "IS";
			break;
		}
		case Major::KN: {
			return "KN";
			break;
		}
		case Major::I:
		{
			return "I";
			break;
		}
		default: {
			return "Unknown";
		}
	}
}
void printStudent(const Student& student)
{
	cout << "Name: " << student.name<<endl;
	cout << "Fn: " << student.fn << endl;
	cout << "Major: " << getMajor(student.major) << endl;;
}
void printStudentDatabase(const StudentDatabase& data)
{
	assert(data.studentCount < STUDENT_MAX_SIZE);
	cout << "TotalStudents: " << data.studentCount<<endl;
	for (int i = 0; i < data.studentCount; i++)
	{
		printStudent(data.students[i]);
	}
}
void SelectionSort(StudentDatabase& data,bool (*isLess) (const Student& s1,const Student& s2))
{
	for (int i = 0; i < data.studentCount-1; i++)
	{
		int minIndex = i;
		for (int j = i+1; j < data.studentCount; j++)
		{
			if (isLess(data.students[j],data.students[minIndex]))
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(data.students[minIndex], data.students[i]);
		}
	}
}
void sortBy(StudentDatabase& data, Criteria criteria)
{
	switch (criteria)
	{
		case Criteria::sortByName: {
			SelectionSort(data,[](const Student& s1, const Student& s2) {return strcmp(s1.name, s2.name) < 0; });
			break;
		}
		case Criteria::sortByFn: {
			SelectionSort(data, [](const Student& s1, const Student& s2) {return s1.fn<s2.fn; });
			break;
		}
		case Criteria::sortByMajor: {
			SelectionSort(data, [](const Student& s1, const Student& s2) {return s1.major< s2.major; });
			break;
		}
	}
}
int main()
{
	StudentDatabase data = {
		3,
		{
		{"Serhan",123,Major::SI},
		{"Ivan",942,Major::KN},
		{"Tosho",853,Major::IS}
		}
	};
	printStudentDatabase(data);
	cout << "------------------\n";
	Criteria cr = Criteria::sortByMajor;
	sortBy(data, cr);
	prin
