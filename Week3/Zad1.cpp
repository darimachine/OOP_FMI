#include <iostream>
#include <fstream>

#include <sstream>
using std::cout;
using std::cin;
using std::endl;
struct Row {
	int* cell;
};
struct Matrix {
	int colCount = 0;
	int rowCount = 0;
	Row* rows;
};


unsigned getColCount(const char* filename, const char delim)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error";
		return 0;
	}
	int counter = 0;
	while (!file.eof())
	{
		char ch = file.get();
		if (ch == delim) {
			counter++;
		}
		else if (ch == '|')
		{
			return counter;
		}
	}
	file.close();
	return counter;
}
unsigned getRowCount(const char* filename, const char delim)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error";
		return 0;
	}
	int counter = 0;
	while (!file.eof())
	{
		if (file.get() == delim) {
			counter++;
		}
	}
	file.close();
	return counter;
}
void initArray(Matrix& matrix)
{
	matrix.rows = new Row[matrix.rowCount];
	for (int i = 0; i < matrix.rowCount; i++)
	{
		matrix.rows[i].cell = new int[matrix.colCount];
	}

}
void freeArray(Matrix& matrix)
{
	for (int i = 0; i < matrix.rowCount; i++)
	{
		delete[] matrix.rows[i].cell;
	}
	delete[] matrix.rows;
}
void printArray(const Matrix& matrix)
{
	for (int i = 0; i < matrix.rowCount; i++)
	{
		for (int j = 0; j < matrix.colCount; j++)
		{
			cout << matrix.rows[i].cell[j] << " ";
		}
		cout << endl;
	}
}
void readArray(std::ifstream& file, Matrix& matrix)
{

	for (int i = 0; i < matrix.rowCount; i++)
	{
		for (int j = 0; j < matrix.colCount; j++)
		{
			file >> matrix.rows[i].cell[j];
			char ch;
			file >> ch;
		}
	}
}
bool isValid(const Matrix& matrix1, const Matrix& matrix2)
{
	if (matrix1.colCount != matrix2.rowCount) return false;
	return true;
}
Matrix multiplyMatrix(const Matrix& matrix1, const Matrix& matrix2)
{
	Matrix matrix3;
	matrix3.rowCount = matrix1.rowCount;
	matrix3.colCount = matrix2.colCount;
	initArray(matrix3);
	for (int i = 0; i < matrix1.rowCount; i++)
	{
		for (int j = 0; j < matrix2.colCount; j++)
		{
			int subMatrix = 0;
			for (int k = 0; k < matrix1.colCount; k++)
			{
				subMatrix += matrix1.rows[i].cell[k] * matrix2.rows[k].cell[j];
			}
			matrix3.rows[i].cell[j] = subMatrix;
		}

	}
	return matrix3;
}
void writeArrayToFile(const char* filename3,const Matrix& matrix)
{
	std::ofstream out(filename3);
	if (!out.is_open())
	{
		cout << "Error Writing";
		return;
	}
	for (int i = 0; i < matrix.rowCount; i++)
	{
		for (int j = 0; j < matrix.colCount; j++)
		{
			out << matrix.rows[i].cell[j];
			if (matrix.colCount > 1 && j < matrix.colCount - 1)
			{
				out << ',';
			}
			
		}
		out << '|';
	}
	out.close();
}
void multiplyMatrixAndSave(const char* filename1, const char* filename2, const char* filename3)
{
	Matrix matrix1;
	Matrix matrix2;
	Matrix matrix3;
	std::ifstream file1(filename1);
	std::ifstream file2(filename2);
	if (!file1.is_open() || !file2.is_open())
	{
		cout << "Error";
		return;
	}
	matrix1.rowCount = getRowCount(filename1, '|') + 1;
	matrix1.colCount = getColCount(filename1, ',') + 1;
	matrix2.rowCount = getRowCount(filename2, '|') + 1;
	matrix2.colCount = getColCount(filename2, ',') + 1;
	if (!isValid(matrix1, matrix2)) {
		cout << "Cannot Multiply" << endl;
		return;
	}
	initArray(matrix1);
	initArray(matrix2);
	readArray(file1, matrix1);
	readArray(file2, matrix2);
	printArray(matrix1);
	cout << endl;
	matrix3 = multiplyMatrix(matrix1,matrix2);
	printArray(matrix3);
	writeArrayToFile(filename3,matrix3);

	freeArray(matrix1);
	freeArray(matrix2);

}
int main()
{
	multiplyMatrixAndSave("matrica1.txt", "matrica2.txt", "matrica3.txt");
}
