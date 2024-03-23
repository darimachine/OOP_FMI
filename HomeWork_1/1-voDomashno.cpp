#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning (disable: 4996)

using std::cout;
using std::endl;
using std::cin;

namespace GlobalConstants {
	// Constants for various limits
	constexpr int MAX_FILE_LENGTH = 1024;
	constexpr int MAX_FIELD_SIZE = 100;
	constexpr int MAX_COLUMNS = 30;
	constexpr int MAX_ROWS = 300;
	constexpr int MAX_BUFFER_SIZE = 2048;
	constexpr int MAX_CHARACTER_NUMBER = 5;
	// HTML tags
	constexpr char TABLE_TAG[] = "<table";
	constexpr char TABLE_TAG_CLOSE[] = "</table";
	constexpr char TH_TAG[] = "<th";
	constexpr char TD_TAG[] = "<td";
	constexpr char TR_TAG[] = "<tr";
	constexpr char TR_TAG_CLOSE[] = "</tr";
}

// Function to leave empty spaces
void leaveEmptySpaces(int length) 
{
	for (int i = 0; i < length; i++)
	{
		cout << " ";
	}
}
// Function to convert a character to an unsigned integer
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
// Function to check if a character is a digit
bool isDigit(char ch) 
{
	return ch >= '0' && ch <= '9';
}
// Function to check if a text contains another text
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
// Function to check if a text is a substring of another text
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
// Function to check if a character is a space
bool isSpace(const char ch) 
{
	return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}

// Function to shift text in a character array
void shiftText(char* text, int start, int lengthToReplace, int& textLength) 
{

	for (int i = start + 1; i + lengthToReplace < textLength; i++)
	{
		text[i] = text[i + lengthToReplace];
	}
	textLength -= lengthToReplace;
	text[textLength] = '\0';
}
// Function to trim spaces inside a text
void trimTextInside(char* text)
{
	int length = strlen(text);
	for (int i = 0; i < length - 1; i++)
	{
		if (text[i] == ' ' && text[i + 1] == ' ')
		{
			shiftText(text, i, 1, length);
			i--;
		}
	}
}
// Function to trim spaces around a text also with given character as well
void trimText(char* text, const char ch = ' ') 
{
	int length = strlen(text);
	int end = strlen(text) - 1; // for indexOutOFRange
	int start = 0;

	while (start < length && (isSpace(text[start]) || text[start] == ch))
	{
		start++;
	}
	while (end > start && (isSpace(text[end]) || text[end] == ch))
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

// Function to extract a number from a text
void getNumber(char* dest, const char* text, int lengthToRead, int indexToStart)
{
	for (int i = 0; i < lengthToRead; i++)
	{
		dest[i] = text[indexToStart++];
	}
	dest[lengthToRead] = '\0';
}
// Function to convert HTML entities to characters
void convertEntitiesToChar(char* text) 
{
	int length = strlen(text);
	for (int i = 0; i < length; i++)
	{
		if (text[i] == '&' && text[i + 1] == '#' && isDigit(text[i + 2]))
		{
			int startIndex = i + 2; // starting from number skiping &#
			int endIndex = startIndex;
			while (endIndex < length && isDigit(text[endIndex])) // finding number Length
			{
				endIndex++;
			}
			int numberLength = endIndex - startIndex;
			int lengthToReplace = endIndex - i; // how many characters i must replace
			char numberInChar[GlobalConstants::MAX_CHARACTER_NUMBER];
			getNumber(numberInChar, text, numberLength, startIndex);
			int number = charToInt(numberInChar); // make char to number
			char asciiLetter = (char)number;
			text[i] = asciiLetter;
			shiftText(text, i, lengthToReplace - 1, length); // I added the ascii letter thats why i need to shift after it and decreese lengthToReplace with -1 {&#97} => {a#97} length to shift is 3 and start +1

		}
	}
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

	void editRow();
	void removeRow();
	void addRow();
	bool readHtml(const char* filename);
	void print() const;
	unsigned getMaxLengthOfCol(int colIndex) const;
	void save(const char* filename) const;
	
private:

	void saveChar(std::ifstream& file, char& currentCh, char* cell, int& cellIndex) const;
	char* readCharByChar(std::ifstream& file) const;
	void emptyRow(int index);
	void removeWholeEmptyColumn();
	void shiftColsLeft(int index);
	int getColumnWithEmptyString() const;
	void shiftRowsDown(int index);
	void shiftRowsUp(int index);
	void initCollLenghtArray(int* array) const;
	bool isValidRow(int row) const;
	bool isValidCol(int col) const;
};

// Function to edit a row in the HTML table
void HtmlTable::editRow()
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

// Function to remove a row from the HTML table
void HtmlTable::removeRow()
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

// Function to add a row to the HTML table
void HtmlTable::addRow()
{

	int rowNumber = 0;
	cout << "Enter Row Index To Insert" << endl;
	cin >> rowNumber;
	rowNumber--;

	//IF YOU WANT TO ADD CUSTOM COLUMNS REMOVE COMMENTED CODE BELOW
	unsigned columnsToAdd;
	cout << "Enter how many columns do you want to add"<<endl;
	cin >> columnsToAdd;
	if (columnsToAdd > colCount) {
	colCount = columnsToAdd;
	}

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
			trimText(value, '#'); // reusing my function for #
		}


		strcpy(cell.cell, value);
		row.field[i] = cell;
	}
	shiftRowsDown(rowNumber);
	rows[rowNumber] = row;
	rowCount++;
	cout << "Added Succesfully" << endl;

}
// Function to read an HTML file and populate the table
bool HtmlTable::readHtml(const char* filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		cout << "File Error";
		return false;
	}
	char tagName[GlobalConstants::MAX_BUFFER_SIZE];
	file.getline(tagName, GlobalConstants::MAX_BUFFER_SIZE, '>'); // always table
	trimText(tagName);
	if (strcmp(tagName, GlobalConstants::TABLE_TAG) != 0)
	{
		cout << "Incorrect information in table (IT MUST START WITH <TABLE>" << endl;
		return false;
	}

	int currentColCount = 0;
	while (!file.eof())
	{
		file.getline(tagName, 1024, '>');
		trimText(tagName);

		if (isSubstring(tagName, GlobalConstants::TR_TAG_CLOSE))
		{
			this->rowCount++;
			if (currentColCount > this->colCount)
			{
				this->colCount = currentColCount;
			}
			currentColCount = 0;

		}
		else if (isSubstring(tagName, GlobalConstants::TH_TAG) || isSubstring(tagName, GlobalConstants::TD_TAG))
		{
			char* currentCell;
			currentColCount++;
			currentCell = readCharByChar(file);
			trimText(currentCell);
			convertEntitiesToChar(currentCell);
			strcpy(rows[rowCount].field[currentColCount - 1].cell, currentCell);
			if (strcmp(tagName, GlobalConstants::TH_TAG) == 0) {
				rows[rowCount].field[currentColCount - 1].isTh = true;
			}


		}
		else if (isSubstring(tagName, "</table")) {
			break;
		}

	}
	return true;
}

// Function to print the HTML table
void HtmlTable::print() const
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

// Function to get the maximum length of a column in the HTML table
unsigned HtmlTable::getMaxLengthOfCol(int colIndex) const
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

// Function to save the HTML table to a file
void HtmlTable::save(const char* filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		return;
	}
	file << "<table>\n";
	for (int i = 0; i < rowCount; i++)
	{
		file << "  <tr>\n";
		for (int j = 0; j < colCount; j++)
		{
			if (rows[i].field[j].isTh) {
				file << "    <th>" << rows[i].field[j].cell << "</th>\n";
			}
			else {
				file << "    <td>" << rows[i].field[j].cell << "</td>\n";
			}
		}
		file << "  </tr>\n";
	}
	file << "</table>";
	file.close();
}
// Function to save a character while reading HTML file until it reaches to '<' then stops
void HtmlTable::saveChar(std::ifstream& file, char& currentCh, char* cell, int& cellIndex) const
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

// Function to read characters from HTML file one by one
char* HtmlTable::readCharByChar(std::ifstream& file) const
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

// Function to empty a row in the HTML table
void HtmlTable::emptyRow(int index)
{
	rows[index] = Row();
}

// Function to remove entire empty columns from the HTML table
void HtmlTable::removeWholeEmptyColumn()
{
	for (int i = 0; i < colCount; i++)
	{
		int emptyColumnIndex = getColumnWithEmptyString();
		if (emptyColumnIndex != -1)
		{
			shiftColsLeft(emptyColumnIndex);
			colCount--;
		}
	}
}

// Function to shift columns to the left in the HTML table
void HtmlTable::shiftColsLeft(int index)
{
	for (int i = index; i < colCount - 1; i++)
	{
		for (int j = i; j < rowCount; j++)
		{
			std::swap(rows[j].field[i], rows[j].field[i + 1]);
		}
	}
}

// Function to get the index of a column with an empty string in the HTML table
int HtmlTable::getColumnWithEmptyString() const
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

// Function to shift rows down in the HTML table
void HtmlTable::shiftRowsDown(int index)
{
	for (int i = rowCount; i > index; i--)
	{
		std::swap(rows[i], rows[i - 1]);
	}
}

// Function to shift rows up in the HTML table
void HtmlTable::shiftRowsUp(int index)
{
	for (int i = index; i < rowCount - 1; i++)
	{
		std::swap(rows[i], rows[i + 1]);
	}
}
// Function to initialize an array with maximum lengths of each column
void HtmlTable::initCollLenghtArray(int* array) const
{
	for (int i = 0; i < colCount; i++)
	{
		array[i] = getMaxLengthOfCol(i);
	}
}

// Function to check if a row index is valid
bool HtmlTable::isValidRow(int row) const {
	return row >= 0 && row < rowCount;
}

// Function to check if a column index is valid
bool HtmlTable::isValidCol(int col) const {
	return col >= 0 && col < colCount;
}

// Function to start the program
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
		cout << "9) Exit And Save" << endl;
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
			table.save(filename); // must be filename
			break;
		}
	}
}
int main()
{
	StartUp();
}

