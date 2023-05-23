#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>


#include "Algorithms.h"
#include "Custom Algorithms.h"

namespace fs = std::filesystem;

class RemoveUnnecessaryWords : CustomAlgorithms
{

private:

	char* m_buffer = nullptr;
	int m_buffer_size = 0;

	int m_wordLength = 5;

	std::string m_allInputCharacters = "";



public:


	RemoveUnnecessaryWords(char* buffer, int buffer_size, int wordLength);
	~RemoveUnnecessaryWords();
	//Add Indexes From Buffer
	
	void AddTheWordsIndexThatDoNotContain_BlackChars(std::string& inputBlacksLetter, std::vector<int>& blackCharIndex);
	void AddTheWordsIndexthatContain_YellowChar(std::string& inputYellowChar, std::vector<int>& yellowCharIndex);
	void AddTheWordsIndexThatContain_GreenChar(std::string& inputGreenChar, std::vector<int>& greenCharIndex);

	//Remove Indexes
	void RemoveTheWordsIndexThatContain_BlackChars(std::string& inputBlacksLetter, std::vector<int>& blackCharIndex);
	void RemoveTheWordsIndexThatDoNotContain_YellowChar(std::string& inputYellowChar, std::vector<int>& yellowCharIndex);
	void RemoveTheWordsIndexThatDoNotContain_GreenChar(std::string& inputGreenChar, std::vector<int>& greenCharIndex);

private:

	void SaveBlackInputChar(std::string& allInputChars, std::string& inputChars);
	
	void RemoveReEnteredBlackChars(std::string& allInputChars, std::string& inputChars);

	void ClearVectorData(std::vector<int>& data);

	void AddNecessaryIndex(std::vector<int>& necessaryIndex, std::vector<int>& wordsIndex);


};





