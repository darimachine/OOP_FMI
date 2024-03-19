#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning (disable: 4996)
using std::cout;
using std::endl;
using std::cin;

namespace GlobalConstants {
	constexpr int MAX_FILE_LENGTH = 1024;
	constexpr int MAX_FIELD_SIZE = 100;
	constexpr int MAX_COLUMNS = 30;
	constexpr int MAX_ROWS = 300;
	constexpr int MAX_BUFFER_SIZE = 5000;
}


unsigned charToInt(char* text)
{
	unsigned result = 0;
	while (*text)
	{
		result = (*text - '0') + (10 * result);
		text++;
	}
	return result;
}
bool isDigit(char ch) 
{
	return ch >= '0' && ch <= '9';
}
bool isContains(const char* text, const char* text2)
{
	int text2Length = strlen(text2);
	int text2Index = 0;
	while (*text)
	{
		if (*text == text2[text2Index])
		{
			text2Index++;
		}
		else {
			text2Index = 0;
		}
		if (text2Index == text2Length)
		{
			return true;
		}
		text++;
	}
	return false;
}
bool isSubstring(const char* text, const char* subText) {
	while (*text)
	{
		if (isContains(text, subText))
		{
			return true;
		}
		text++;
	}
	return false;
}
struct Cell {
	char cell[GlobalConstants::MAX_FIELD_SIZE] = "";
	bool isTh = false;
};
struct Row {
	Cell field[GlobalConstants::MAX_COLUMNS];
};

class HtmlTable {
	Row rows[GlobalConstants::MAX_ROWS];
	unsigned colCount = 0;
	unsigned rowCount = 0;

public:

	void editRow()
	{
		int rowNumber, colNumber;
		char value[GlobalConstants::MAX_FIELD_SIZE];
		cout << "Enter rowNumber: " << endl;
		cin >> rowNumber;
		rowNumber--;
		if (!isValidRow(rowNumber))
		{
			cout << "Invalid Row" << endl;
			return;
		}
		cout << "Enter colNumber: " << endl;
		cin >> colNumber;
		colNumber--;
		if (!isValidCol(colNumber))
		{
			cout << "Invalid Col" << endl;
			return;
		}
		cout << "Enter newValue:  (For <th> cover your value from both sides with (#) => #<value>#) " << endl;
		cin.ignore();
		cin.getline(value, GlobalConstants::MAX_FIELD_SIZE);
		if (value[0] == '#' && value[strlen(value) - 1] == '#')
		{
			rows[rowNumber].field[colNumber].isTh = true;
			trimText(value, '#'); // reusing my function for #
		}
		else {
			rows[rowNumber].field[colNumber].isTh = false;
			trimText(value);
		}
		convertEntitiesToChar(value);
		strcpy(rows[rowNumber].field[colNumber].cell, value);
		removeWholeEmptyColumn();
		cout << "Edited Succesfully" << endl;

	}
	
	void emptyRow(int index)
	{
		rows[index] = Row();
	}
	void removeRow()
	{
		int rowNumber = 0;
		cout << "Enter Row Index To Remove" << endl;
		cin >> rowNumber;
		rowNumber--;
		if (!isValidRow(rowNumber))
		{
			cout << "Invalid Row Index" << endl;
			return;
		}
		emptyRow(rowNumber);
		shiftRowsUp(rowNumber);
		rowCount--;
		removeWholeEmptyColumn();
		cout << "Deleted Sucesfully" << endl;
	}
	void addRow()
	{

		int rowNumber = 0;
		cout << "Enter Row Index To Insert" << endl;
		cin >> rowNumber;
		rowNumber--;
		//IF YOU WANT TO ADD CUSTOM COLUMNS REMOVE COMMENTED CODE BELOW
		/*unsigned columnsToAdd;
		cout << "Enter how many columns do you want to add"<<endl;
		cin >> columnsToAdd;
		if (columnsToAdd > colCount) {
			colCount = columnsToAdd;
		}*/
		if (!isValidRow(rowNumber))
		{
			cout << "Invalid Row Index" << endl;
			return;
		}
		Row row;
		cin.ignore(GlobalConstants::MAX_FIELD_SIZE, '\n');
		for (int i = 0; i < colCount; i++)
		{
			cout << "Enter Value (" << i + 1 << ") (For <th> cover your value from both sides with (#) => #<value>#) :" << endl;
			char value[GlobalConstants::MAX_FIELD_SIZE];

			cin.getline(value, GlobalConstants::MAX_FIELD_SIZE);
			trimText(value);
			convertEntitiesToChar(value);
			Cell cell;
			if (value[0] == '#' && value[strlen(value) - 1] == '#')
			{
				cell.isTh = true;
				trimText(value,'#'); // reusing my function for #
			}
		
			
			strcpy(cell.cell, value);
			row.field[i] = cell;
		}
		shiftRowsDown(rowNumber);
		rows[rowNumber] = row;
		rowCount++;
		cout << "Added Succesfully" << endl;

	}
	void saveChar(std::ifstream& file, char& currentCh, char* cell, int& cellIndex) const
	{
		while (true)
		{
			currentCh = file.get();
			if (currentCh == '<')
			{
				return;
			}
			else {
				cell[cellIndex++] = currentCh;
			}
		}
	}
	char* readCharByChar(std::ifstream& file) const
	{
		char cell[GlobalConstants::MAX_BUFFER_SIZE];
		int cellIndex = 0;
		char currentCh;
		char currentCh2;
		while (true)
		{
			saveChar(file, currentCh, cell, cellIndex);
			currentCh2 = file.get();
			if (currentCh2 == '/')
			{
				char temp[1024];
				file.getline(temp, 1024, '>');
				break;
			}
			else {
				cell[cellIndex++] = currentCh;
				cell[cellIndex++] = currentCh2;
			}

		}
		cell[cellIndex] = '\0';
		//cout << cell;
		return cell;
	}
	bool readHtml(const char* filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			cout << "File Error";
			return false;
		}
		char buffer[GlobalConstants::MAX_BUFFER_SIZE];

		file.getline(buffer, GlobalConstants::MAX_BUFFER_SIZE, '>'); // always table
		trimText(buffer);
		if (strcmp(buffer, "<table") != 0)
		{
			cout << "Incorrect information in table (IT MUST START WITH <TABLE>" << endl;
			return false;
		}

		int currentColCount = 0;
		while (!file.eof())
		{
			file.getline(buffer, 1024, '>');
			trimText(buffer);
		
			if (isSubstring(buffer,"</tr"))
			{
				this->rowCount++;
				if (currentColCount > this->colCount)
				{
					this->colCount = currentColCount;
				}
				currentColCount = 0;

			}
			else if (isSubstring(buffer, "<th") || isSubstring(buffer, "<td"))
			{
				char* currentText;

				currentColCount++;
				currentText = readCharByChar(file);
				trimText(currentText);
				convertEntitiesToChar(currentText);
				strcpy(rows[rowCount].field[currentColCount - 1].cell, currentText);
				if (strcmp(buffer, "<th") == 0) {
					rows[rowCount].field[currentColCount - 1].isTh = true;
				}


			}
			else if (isSubstring(buffer, "</table")) {
				break;
			}

		}
		return true;
	}
	void leaveEmptySpaces(int length) const
	{
		for (int i = 0; i < length; i++)
		{
			cout << " ";
		}
	}
	void print() const
	{
		int* columnLenghts = new int[colCount];
		initCollLenghtArray(columnLenghts);
		for (int i = 0; i < rowCount; i++)
		{

			for (int j = 0; j < colCount; j++)
			{
				cout << "|";
				int currentWordLength = strlen(rows[i].field[j].cell);
				if (rows[i].field[j].isTh)
				{
					cout << '*';	
				}
				else {
					cout << " ";
				}
				cout << rows[i].field[j].cell;
				unsigned lengthOfCol = columnLenghts[j] - currentWordLength;
				leaveEmptySpaces(lengthOfCol);
				if (!rows[i].field[j].isTh)
				{
					cout << " ";
				}
				else {
					cout << "*";
				}
								
			}
			cout << '|';
			cout << endl;
		}
		
		delete[] columnLenghts;
	}
	unsigned getMaxLengthOfCol(int colIndex) const
	{
		int max = 0;
		for (int i = 0; i < rowCount; i++)
		{
			int currentLen = strlen(rows[i].field[colIndex].cell);
			if (currentLen > max) {
				max = currentLen;
			}
		}
		return max;
	}
	bool isSpace(const char ch) const
	{
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	void trimText(char* text, const char ch=' ') const
	{
		int length = strlen(text);
		int end = strlen(text) - 1; // for indexOutOFRange
		int start = 0;

		while (start < length && (isSpace(text[start]) || text[start] == ch))
		{
			start++;
		}
		while (end > start && (isSpace(text[end])|| text[end] == ch))
		{
			end--;
		}
		if (start > end)
		{
			text[0] = '\0';
			return;
		}
		int wordLength = (end - start) + 1;
		for (int i = 0; i < wordLength; i++)
		{
			text[i] = text[start++];
		}
		text[wordLength] = '\0';
		trimTextInside(text);
	}
	void trimTextInside(char* text) const
	{
		int length = strlen(text);
		for (int i = 0; i < length-1; i++)
		{
			if (text[i] == ' ' && text[i + 1] == ' ')
			{
				shiftText(text, i, 1, length);
				i--;
			}
		}
	}
	
	void shiftText(char* text, int start, int lengthToReplace, int& textLength) const
	{
		 
		for (int i = start+1; i + lengthToReplace < textLength; i++)
		{
			text[i] = text[i + lengthToReplace];
		}
		textLength -= lengthToReplace;
		text[textLength] = '\0';
	}
	void convertEntitiesToChar(char* text) const
	{
		int length = strlen(text);
		for (int i = 0; i < length; i++)
		{
			if (text[i] == '&' && text[i + 1] == '#' && isDigit(text[i + 2]))
			{
				int startIndex = i + 2; // number
				int endIndex = startIndex;
				while (endIndex < length && isDigit(text[endIndex]))
				{
					endIndex++;
				}
				int numberLength = endIndex - startIndex;
				int lengthToReplace = endIndex - i;
				char numberInChar[5] = { '\0' };
				strncpy(numberInChar, text + startIndex, numberLength);
				int number = charToInt(numberInChar); // make char to number
				char asciiLetter = (char)number;
				text[i] = asciiLetter;
				shiftText(text, i, lengthToReplace-1, length); // I added the ascii letter thats why i need to shift after it and decreese lengthToReplace with -1 {&#97} => {a#97} length to shift is 3 and start +1

			}
		}
	}
private:
	void removeWholeEmptyColumn() 
	{
		int emptyColumnIndex = getColumnWithEmptyString();
		if (emptyColumnIndex != -1)
		{
			shiftColsLeft(emptyColumnIndex);
			colCount--;
		}
	}
	void shiftColsLeft(int index)
	{
		for (int i = index; i < colCount-1; i++)
		{
			for (int j = i; j < rowCount; j++)
			{
				std::swap(rows[j].field[i], rows[j].field[i + 1]);
			}
		}
	}
	int getColumnWithEmptyString() const
	{
		for (int i = 0; i < colCount; i++)
		{
			if (getMaxLengthOfCol(i) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	void shiftRowsDown(int index)
	{
		for (int i = rowCount; i > index; i--)
		{
			std::swap(rows[i], rows[i - 1]);
		}
	}
	void shiftRowsUp(int index)
	{
		for (int i = index; i < rowCount - 1; i++)
		{
			std::swap(rows[i], rows[i + 1]);
		}
	}
	void initCollLenghtArray(int* array) const
	{
		for (int i = 0; i < colCount; i++)
		{
			array[i] = getMaxLengthOfCol(i);
		}
	}
	bool isValidRow(int row) const {
		return row >= 0 && row < rowCount;
	}
	bool isValidCol(int col) const {
		return col >= 0 && col < colCount;
	}
};

void StartUp()
{
	cout << "Enter Filename: " << endl;
	char filename[GlobalConstants::MAX_FILE_LENGTH];
	cin >> filename;
	HtmlTable table;
	bool isReaded = table.readHtml(filename);
	if (!isReaded) return;
	while (true)
	{
		cout << "1) Add Row" << endl;
		cout << "2) Remove Row" << endl;
		cout << "3) Edit Row" << endl;
		cout << "4) Print" << endl;
		cout << "9) Exit" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			table.addRow();
		}
		else if (choice == 2)
		{
			table.removeRow();
		}
		else if (choice == 3)
		{
			table.editRow();
		}
		else if (choice == 4)
		{
			table.print();
		}
		else if (choice == 9)
		{
			break;
		}
	}
}
int main()
{
	StartUp();
}