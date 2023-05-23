#pragma once

#include <iostream>
#include <filesystem>
#include <fstream>

#include "Algorithms.h"
#include "Custom Algorithms.h"


class WordsWithRepeatingAndNonRepeatingLetters : Algorithms, CustomAlgorithms
{
private:


public:

	void FindBySearchingInWholeBuffer(char* buffer, int file_size, std::vector<int>& UnrepeatedLetterWordsIndex,
		std::vector<int>& repeatingLetterWordsIndex, int wordleLength);

	void AddTheWordsIndexes(char* buffer, std::vector< int >& wordsIndex, std::vector<int>& unrepeatedLetterWordsIndex,
		std::vector<int>& repeatingLetterWordsIndex, int wordleLength);

	void RemoveTheWordsIndexes(char* buffer, std::vector< int >& wordsIndex,
		std::vector<int>& unrepeatedLetterWordsIndex, std::vector<int>& repeatingLetterWordsIndex, int wordLength);


private:

	void ClearVectorData(std::vector<int>& data);

	void AddNecessaryIndex(std::vector<int>& unrepeatedLetterWordsIndex, std::vector<int>& necessaryIndex);

};



