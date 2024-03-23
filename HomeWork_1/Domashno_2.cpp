
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

using std::cout;
using std::endl;
using std::cin;

namespace Constants {
	constexpr int MAX_NAME_LENGTH = 64;
	constexpr int MAX_BYTES = 256;
	constexpr int MAX_SONGS = 30;
}

typedef unsigned char byte;

// Enum for different music genres
enum class Genres :byte {
	Rock = 1 << 0,// 00000001
	Pop = 1<<1, // 00000010
	HipHop = 1<<2, // 00000100
	Electronic = 1<<3, // 00001000
	Jazz = 1<<4, // 00010000
	None = 0
};

class Time {
    unsigned hours=0;
    unsigned minutes=0;
    unsigned seconds=0;
public:

	Time() = default;
	Time(unsigned hours,unsigned minutes,unsigned seconds);
	unsigned getHours() const;
	unsigned getMinutes() const;
	unsigned getSeconds() const;
	void setHours(unsigned hour);
	void setMinutes(unsigned minute);
	void setSeconds(unsigned second);
    unsigned getTimeInSeconds() const;
	void printTime() const;
	int compare(const Time& other) const;
};
//Constructor
Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
{
	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);
}
// Getter methods for Time class
unsigned Time::getHours() const {
	return hours;
}

unsigned Time::getMinutes() const {
	return minutes;
}

unsigned Time::getSeconds() const {
	return seconds;
}

// Setter methods for Time class
void Time::setHours(unsigned hour)
{
	if (hours > 23)
	{
		hours = 0;
	}
	else {
		hours = hour;
	}
}

void Time::setMinutes(unsigned minute)
{
	if (minute > 59)
	{
		minutes = 0;
	}
	else {
		minutes = minute;
	}
}

void Time::setSeconds(unsigned second)
{
	if (second > 59)
	{
		seconds = 0;
	}
	else {
		seconds = second;
	}
}
// Get total time in seconds
unsigned Time::getTimeInSeconds() const {
	return (hours * 3600) + (minutes * 60) + seconds;
}

// Print time in HH:MM:SS format
void Time::printTime() const {
	if (hours < 10)
	{
		cout << '0' << hours;
	}
	else {
		cout << hours;
	}
	cout << ":";
	if (minutes < 10)
	{
		cout << '0' << minutes;
	}
	else {
		cout << minutes;
	}
	cout << ":";
	if (seconds < 10)
	{
		cout << '0' << seconds;
	}
	else {
		cout << seconds;
	}
}

// Compare two Time objects
int Time::compare(const Time& other) const {
	if (this->getTimeInSeconds() > other.getTimeInSeconds()) {
		return 1;
	}
	else if (this->getTimeInSeconds() < other.getTimeInSeconds()) {
		return -1;
	}
	else {
		return 0;
	}
}
class Song {
	char name[Constants::MAX_NAME_LENGTH]="";
	Time duration;
	byte genre=0;
	byte melody[Constants::MAX_BYTES];
	unsigned melodyLength = 0;
	unsigned totalGenres = 0;
public:
	Song() = default;
	Song(const char* name, const Time& time, const char* textGenre, const char* filename);
	const char* getName() const;
	const byte getGenre() const;
	const Time getTime() const;
	const byte* getData() const;
	unsigned getDataLength() const;
	void changeDataForRythym(int index);
	void mixSong(const Song& other);
	void printSong() const;
	void printGenre() const;
	void printBits();
private:
	void makeBitsOne(byte& currentByte, unsigned index, int shiftedAmount);
	const char* getGenreByByte(byte b) const;
	void readDataFromFile(const char* filename);
	void setGenre(const char* text);

};

// Constructor for Song class
Song::Song(const char* name, const Time& time, const char* textGenre, const char* filename)
{
	strcpy(this->name, name);
	this->duration = time;
	setGenre(textGenre);
	readDataFromFile(filename);
}

// Getter methods for Song class
const char* Song::getName() const {
	return name;
}

const byte Song::getGenre() const {
	return genre;
}

const Time Song::getTime() const {
	return duration;
}

const byte* Song::getData() const {
	return melody;
}

unsigned Song::getDataLength() const {
	return melodyLength;
}

// Modify song data to add rhythm
void Song::changeDataForRythym(int index) // index is k
{
	int shiftedAmount = -1;
	int bitsLength = 8 * melodyLength;
	if (index > bitsLength || index == 0)
	{
		cout << "Incorect Index" << endl;
		return;
	}
	for (int i = melodyLength - 1; i >= 0; i--)
	{
		makeBitsOne(melody[i], index, shiftedAmount);
		shiftedAmount -= 8;
	}
}
// Mix two songs together
void Song::mixSong(const Song& other)
{
	int byteLengthToMix = std::min(melodyLength, other.melodyLength);
	for (int i = 0; i < byteLengthToMix; i++)
	{
		melody[i] = melody[i] ^ other.melody[i];
	}
}

// Print details of the song
void Song::printSong() const
{
	cout << this->name << ", ";
	duration.printTime();
	cout << ", ";
	printGenre();
}

// Print genres of the song
void Song::printGenre() const {
	unsigned currentPrintedGenres = 0;
	for (int i = 0; i < 8; i++)
	{
		byte index = 1 << i;
		if (genre & index)
		{
			currentPrintedGenres++;
			cout << getGenreByByte(index);

			if (totalGenres != currentPrintedGenres) {
				cout << "&";
			}
		}
	}
	if (currentPrintedGenres == 0) {
		cout << "None";
	}
}

// Print binary representation of the song data
void Song::printBits() {
	for (int k = 0; k < melodyLength; k++)
	{
		for (int i = 7; i >= 0; i--) {
			if ((melody[k] & (1 << i)) == 0)
			{
				cout << '0';
			}
			else {
				cout << '1';
			}

		}
		if (k + 1 != melodyLength)
			cout << " ";
	}
}

// Set specific bits of a byte to 1
void Song::makeBitsOne(byte& currentByte, unsigned index, int shiftedAmount)
{
	while (shiftedAmount < 8)
	{
		if (shiftedAmount > -1)
		{
			currentByte = currentByte | (1 << shiftedAmount);
		}
		shiftedAmount += index;

	}
}

// Get genre name based on byte representation
const char* Song::getGenreByByte(byte b) const
{
	switch (b)
	{
	case 1 << 0: {
		return "Rock";
	}
	case 1 << 1: {
		return "Pop";
	}
	case 1 << 2: {
		return "HipHop";
	}
	case 1 << 3: {
		return "Electronic";
	}
	case 1 << 4: {
		return "Jazz";
	}
	default: {
		return "None";
	}

	}
}

// Read song data from file
void Song::readDataFromFile(const char* filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		cout << "Error Opening File";
		return;
	}
	while (!file.eof())
	{
		file.read((char*)&melody[melodyLength++], sizeof(byte));

	}
	melody[--melodyLength] = '\0';
	file.close();
}

// Set genre of the song
void Song::setGenre(const char* text)
{

	while (*text)
	{
		switch (*text)
		{
		case 'r': {
			genre = genre | (byte)Genres::Rock;
			totalGenres++;
			break;
		}
		case 'p': {
			genre = genre | (byte)Genres::Pop;
			totalGenres++;
			break;
		}
		case 'h': {
			genre = genre | (byte)Genres::HipHop;
			totalGenres++;
			break;
		}
		case 'e': {
			genre = genre | (byte)Genres::Electronic;
			totalGenres++;
			break;
		}
		case 'j': {
			genre = genre | (byte)Genres::Jazz;
			totalGenres++;
			break;
		}
		}
		text++;
	}
}

class Playlist {
	Song songs[Constants::MAX_SONGS] = {};
	unsigned songCount = 0;
public:
	void add(const Song& song);
	void add(const char* name, const Time& time, const char* textGenre, const char* filename);
	void print() const;
	Song& find(const char* name);
	Playlist findGenre(const char genre) const;
	void sortByName();
	void sortByDuration();
	void mix(const char* song1, const char* song2);
	void save(const char * songName, const char* filename);
private:
	void selectionSort(bool (*criteria) (const Song&, const Song&));
	byte getCurrentGenre(const char genre) const;
};

// Add a song to the playlist
void Playlist::add(const Song& song)
{
	songs[songCount++] = song;
}

void Playlist::add(const char* name, const Time& time, const char* textGenre, const char* filename)
{
	songs[songCount++] = Song(name, time, textGenre, filename);
}

// Print all songs in the playlist
void Playlist::print() const {
	for (int i = 0; i < songCount; i++)
	{
		songs[i].printSong();
		cout << endl;
	}
}

// Find a song by name in the playlist
Song& Playlist::find(const char* name)
{

	for (int i = 0; i < songCount; i++)
	{
		if (strcmp(songs[i].getName(), name) == 0) {

			return songs[i];
		}
	}
	cout << "Song with that name doesnt exists" << endl;

}

// Find songs of a particular genre in the playlist
Playlist Playlist::findGenre(const char genre) const
{
	Playlist currentPlaylist;
	byte currenGenre = getCurrentGenre(genre);
	for (int i = 0; i < songCount; i++)
	{
		if ((currenGenre & songs[i].getGenre()) != 0)
		{
			currentPlaylist.add(songs[i]);
		}
	}
	return currentPlaylist;

}

// Sort songs in the playlist by name
void Playlist::sortByName()
{
	selectionSort([](const Song& song1, const Song& song2) {return strcmp(song1.getName(), song2.getName()) < 0; });
}

// Sort songs in the playlist by duration
void Playlist::sortByDuration()
{
	selectionSort([](const Song& song1, const Song& song2) {return song1.getTime().compare(song2.getTime()) < 0; });
}

// Mix two songs in the playlist
void Playlist::mix(const char* song1, const char* song2)
{
	Song& song1Mix = find(song1);
	Song song2Mix = find(song2);
	song1Mix.mixSong(song2Mix);
	//song1Mix.printBits();
}

// Save a song from the playlist to a file
void Playlist::save(const char* songName, const char* filename)
{
	Song song = find(songName);
	std::ofstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		cout << "Error opening file\n";
		return;
	}
	file.write((const char*)song.getData(), song.getDataLength());
}

// Selection sort implementation for sorting songs
void Playlist::selectionSort(bool(*criteria)(const Song&, const Song&))
{
	for (int i = 0; i < songCount - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < songCount; j++)
		{
			if (criteria(songs[j], songs[minIndex]))
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			std::swap(songs[i], songs[minIndex]);
		}
	}
}

// Get byte representation of genre
byte Playlist::getCurrentGenre(const char genre) const
{
	byte currentBit = 0;
	switch (genre)
	{
	case 'r': {
		currentBit = currentBit | (byte)Genres::Rock;
		break;
	}
	case 'p': {
		currentBit = currentBit | (byte)Genres::Pop;
		break;
	}
	case 'h': {
		currentBit = currentBit | (byte)Genres::HipHop;
		break;
	}
	case 'e': {
		currentBit = currentBit | (byte)Genres::Electronic;
		break;
	}
	case 'j': {
		currentBit = currentBit | (byte)Genres::Jazz;
		break;
	}
	}
	return currentBit;
}

int main()
{

	Time time(0, 1, 55);
	Time time2(1, 2, 55);
	
	Playlist playlist;
	playlist.add("Song 2", time2, "rp", "song2.dat");
	playlist.add("Song 1", time, "p", "song1.dat");
	
	playlist.print();
	// Song 2, 00:01:55, Pop&Rock
	// Song 1, 00:01:05, Pop
	cout << endl;
	playlist.sortByName();
	playlist.print();
	// Song 1, 00:01:05, Pop
	// Song 2, 00:01:55, Pop&Rock

	Song song1 = playlist.find("Song 1");
	cout << endl;
	song1.printSong(); // Song 1, 00:01:05, Pop
	cout << endl << endl;
	Playlist newPlay = playlist.findGenre('r');
	newPlay.print();
	// Song 1, 00:01:05, Pop
	// Song 2, 00:01:55, Pop&Rock
	playlist.findGenre('r');
	cout << endl;
	playlist.print();
	cout << endl;
	// Song 2, 00:01:55, Pop&Rock

	playlist.mix("Song 1", "Song 2");
	playlist.save("Song 1", "song3.dat"); // съдържание на song3.dat: “S” //0000 0011
}


