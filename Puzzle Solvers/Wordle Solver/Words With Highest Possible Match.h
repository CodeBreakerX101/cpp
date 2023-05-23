#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>


#include "Algorithms.h"
#include "Custom Algorithms.h"

namespace fs = std::filesystem;

class WordsWithHighestPossibleMatch : public Algorithms, public CustomAlgorithms
{

private:

	char* m_buffer = nullptr;
	int m_wordLength = 5;//default

	char* m_buffer_copy = nullptr;
	int m_buffer_copy_size = 0;

	bool m_error_occured = false;

	std::vector<int> m_charsFirstIndex;
	std::vector<int> m_everyCharsValue;

	std::vector < std::pair<char, int> > m_charAndItsValue;
	std::vector < std::pair<int, int> > m_wordsFirstIndexAndValue;

	// Global Variables for GetFirstIndexFromSortedBuffer()
	int m_constRight = 0;
	int m_previousRight = 0;
	int runTimes = 0;
	bool firstTime = false;

public:

	WordsWithHighestPossibleMatch(char* buffer, int wordLength);
	~WordsWithHighestPossibleMatch();

	void Run(std::vector<int>& wordsIndex);

private:

	void CopyTheBufferWithNoSpaces(char* buffer, char* buffer_copy, std::vector<int>& wordsIndex);

	void SortTheBufferCopy(char* m_buffer_copy, int file_size);

	void GetFirstIndexFromSortedBuffer(char* sortedBuffer, int left, int right, std::vector<int>& charsFirstIndex);

	void GetEveryCharsValue(std::vector<int>& charsFirstIndex, int buffer_copy_size, std::vector<int>& everyCharsValue);

	void AssignCharInCharAndItsValue(std::vector<std::pair<char, int>>& charAndItsValue);

	void GetCharAndItsValue(char* sortedBuffer, int file_size, std::vector<int>& charsFirstIndex, std::vector<std::pair<char, int>>& charAndItsValue);

	void GetTheWordsFirstIndexAndItsValue(char* m_buffer, std::vector<int>& charsFirstIndex, std::vector<std::pair<char, int>>& charAndItsValue, std::vector<std::pair<int, int>>& wordsFirstIndexAndValue);

	void SortWordsByValueInDescendingOrder(std::vector<std::pair<int, int>>& wordsFirstIndexAndValue);

	void GetWordsIndex(std::vector<std::pair<int, int>>& wordsFirstIndexAndValue, std::vector<int>& wordsIndex);

	void ClearData();



	void ShowBuffer(char* buffer, int bufferSize);

	void ShowIndexData(char* buffer, std::vector<int>& charsFirstIndex, int wordLength);


};

/*	// EXPLANATION OF THE CODE//
*
	//// Sort Words by the character which has appeared most times in the whole file \\\\\

	1.	Copy main buffer into a new buffer with no spaces;
	2.	Sort the new buffer
	3.	Get the character and it's value( example:- if 74 'S' is available in the file, then value == 74),
		std::vector<map<char,int>> charAndValue;

	4.	Get value of every CHAR of a WORD, add those value and it'll be the WORD's value; example:- if in a word ->
		"LIGHT" character 'L' has appeared 15 times, 'I' 10 times, 'G' 5 times, 'H' 6 times and
		'T' 12 times then the total value of this word is 15 + 10 + 5 + 6 + 12 = 38;
	5.	Sort the words by value in descending order;
	6.	save the new buffer in new file;

*/
