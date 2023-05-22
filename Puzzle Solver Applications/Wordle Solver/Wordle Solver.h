#pragma once

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Files Operations.h"
#include "Remove Unnecessary Words.h"
#include "Words With Highest Possible Match.h"
#include "Words With Repeating And Non Repeating Letters.h"


class WordleSolver : FilesOperations, WordsWithRepeatingAndNonRepeatingLetters, CustomAlgorithms
{

public:

	std::vector<int> m_wordsIndex;
	std::vector<int> m_nonRepeatingLetterWordsIndex;
	std::vector<int> m_repeatingLetterWordsIndex;

	bool m_ErrorOccured = false;
	std::string m_errorMsg;


private:
	

	RemoveUnnecessaryWords* m_CunnecessaryWordsRemover = nullptr;
	WordsWithHighestPossibleMatch* m_CshuffleWordsByHighestPossibleMatch = nullptr;

	std::fstream input_WordleFile, output_WordleFile;
		
	std::string error_message, error_in = "Error in ";


	std::ios::openmode outputMode = std::ios::out | std::ios::trunc;
	std::ios::openmode inputMode = std::ios::in;
	std::ios::openmode input_outputMode = outputMode | inputMode;

	char* m_buffer = nullptr;
	int m_buffer_size = 0;
	int m_wordLength = 5;

	int m_whichFunctionToCall = 0;
	int blackChar_option = 1;
	int yellowChar_option = 2;
	int greenChar_option = 3;


	bool m_WouldYouLikeToShowWords = false;
	char m_showDataOntheScreen = NULL;

	// 
	std::vector<int> m_allGreenLettersPos;
	int m_totalLetters = 0;
	int m_numberOfNewGreenLettersEntered = 0;

	std::string m_allInputLetters;
	std::string headLine_noRepeatingWords = "Unrepeated Letter Words shuffled in order of highest possible match\n\n";
	std::string headLine_AllWords = "All words are shuffled in order of highest possible match\n\n";

public:

	WordleSolver(std::string inputAddress);	
	~WordleSolver();

	int Run(std::string& blackLetters, std::string& YellowLetters, std::string& greenLetters);

	std::string GetInputLetters(std::string& inputLetters);
	
	void RemoveDuplicateLetters(std::string& blackLetters, std::string& searchingIn);


	bool isLetterAvailable(std::string& letters);

	std::string GetWordsFromIndex(std::vector<int>& nonRepeatingLetterWordsIndex, std::vector<int>& repeatingLetterWordsIndex, 
		const int numberOfWordsToCopy = 20);

private:
	

	bool isDataEmpty(std::vector<int>& data);

	int NumberOfRepeatedLettersInUserInput(std::string& inputCharacters);

	void FindDuplicateLetters(std::string& inputCharacters, std::vector<int>& duplicateLetters);

	bool ShouldRestart(int whichFunctionToCall);	


	void ClearData();

	

	

};


