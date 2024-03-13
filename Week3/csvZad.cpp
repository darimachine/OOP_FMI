#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;

namespace Constants {
	constexpr int MAX_ROWS = 300;
	constexpr int MAX_FIELD_SIZE = 50;
	constexpr int MAX_COLUMNS = 10;
	constexpr int MAX_LETTERS = 1024;
	constexpr char SEP = ',';
}
typedef char Field[Constants::MAX_FIELD_SIZE];

struct Row {
	Field fields[Constants::MAX_COLUMNS];
};
struct CsvTable {
	unsigned rowCount = 0;
	unsigned colCount = 0;
	Row rows[Constants::MAX_ROWS];
};
unsigned parseRow(const char* row, Row& toReturn)
{
	std::stringstream ss(row);
	int currentColumn = 0;
	while (!ss.eof())
	{
		char currentWord[1024];
		ss.getline(toReturn.fields[currentColumn++], 1024, Constants::SEP);
	}
	return currentColumn;
}
void readRow(std::ifstream& in,CsvTable& csv)
{
	char buffer[1024];
	int currentColumn = 0;
	while (!in.eof())
	{
		Row row;
		in.getline(buffer, 1024);
		csv.colCount = parseRow(buffer, row);
		csv.rows[csv.rowCount++] = row;
	}

}
CsvTable readCsv(const char* filename)
{
	CsvTable csv;
	std::ifstream in(filename);
	if (!in.is_open())
	{
		cout << "Error while opening"<<endl;
		return csv;
	}
	readRow(in, csv);
	in.close();
	return csv;
}
void printCsv(const CsvTable& table)
{
	for (int i = 0; i < table.rowCount; i++)
	{
		for (int j = 0; j < table.colCount; j++)
		{
			cout << table.rows[i].fields[j] << " ";
		}
		cout << endl;
	}
}
void printRow(const Row& row,int columnCount)
{
	for (int i = 0; i < columnCount; i++)
	{
		cout<< row.fields[i] << " ";
	}
}
void printInfoForStudent(const CsvTable& table, const char* fn)
{
	for (int i = 0; i < table.rowCount; i++)
	{
		if (strcmp(table.rows[i].fields[2], fn) == 0)
		{
			printRow(table.rows[i], table.colCount);
			break;
		}
	}
	cout << endl;
}
void modifyColumn(CsvTable& table,const char* columnName,const char* values,const char SEP)
{
	int colIndex = -1;
	for (int i = 0; i < table.colCount; i++)
	{
		if(strcmp(table.rows[0].fields[i], columnName) == 0) 
		{
			colIndex = i;
			break;
		}
	}
	if (colIndex == -1) {
		return;
	}
	std::stringstream stringValues(values);
	int rowIndex = 1;
	while (!stringValues.eof())
	{
		char currentValue[1024];
		stringValues.getline(currentValue, 1024, SEP);
		strcpy(table.rows[rowIndex++].fields[colIndex],currentValue);
		if (rowIndex >= table.rowCount - 1) {
			break;
		}
	}
	
}
void changeEmail(CsvTable& table, const char* fn, const char* major, const char* email)
{
	
	for (int i = 0; i < table.rowCount; i++)
	{
		if (strcmp(table.rows[i].fields[2], fn) == 0
			&& strcmp(table.rows[i].fields[3], major) == 0)
		{
			strcpy(table.rows[i].fields[4], email);
			break;
		}
	}
}
void writeRow(std::ofstream& out, const Row& row,int columnCount)
{
	for (int i = 0; i < columnCount; i++)
	{
		if (i == columnCount - 1) {
			out << row.fields[i];
			continue;
		}
		out << row.fields[i] << ',';
	}
}
void writeTable(const char* filename,const CsvTable& table)
{
	std::ofstream out(filename);
	if (!out.is_open())
	{
		cout << "Error while wrting";
		return;
	}
	for (int i = 0; i < table.rowCount; i++)
	{
		writeRow(out, table.rows[i], table.colCount);
		out << endl;
	}
	out.close();
}
int main()
{
	CsvTable table;
	
	table = readCsv("uni.csv");
	printCsv(table);
	cout << endl;
	printInfoForStudent(table, "2MI1313");
	cout << endl;
	
	modifyColumn(table, "Ime", "Misho;Petur", ';');
	changeEmail(table, "8MI0600316", "SI", "serhihey@gmail.com");
	printCsv(table);
	writeTable("resultUni.csv", table);

}
