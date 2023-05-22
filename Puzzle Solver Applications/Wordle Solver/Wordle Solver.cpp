
#include "Wordle Solver.h"


bool startingNewWordle = true;
const int Error_occured = -1;

WordleSolver::WordleSolver(std::string inputAddress)
{		

	//Opening Input File
	if (!FilesOperations::OpenFile(input_WordleFile, inputAddress, inputMode))
	{
		m_errorMsg = FilesOperations::ErrorMessage(); // Show Error Message and Return -1
		m_ErrorOccured = true;
		return;
	}
	m_buffer_size = FilesOperations::FileSize(input_WordleFile);
	m_buffer = new char[m_buffer_size];

	if (!FilesOperations::ReadDataFromFile(m_buffer, m_buffer_size, input_WordleFile))
	{
		m_errorMsg = FilesOperations::ErrorMessage();
		m_ErrorOccured = true;
		return;
	}

	//Creating Objects
	m_CunnecessaryWordsRemover = new RemoveUnnecessaryWords(m_buffer, m_buffer_size, m_wordLength);
	m_CshuffleWordsByHighestPossibleMatch = new WordsWithHighestPossibleMatch(m_buffer, m_wordLength);


	//Assigning Classes Objects To Member Variables
	
	

}
//Asterisk('*') is used to positions Green and Yellow letters; like:- yellowLetters = "**I*T, greenLetters = "R**G*"
int WordleSolver::Run(std::string& blackLetters, std::string& yellowLetters, std::string& greenLetters)
{
	
	static int timer = 0;

	std::string greenLettersOnly = GetInputLetters(greenLetters); // Ignoring '*' and resurrecting letters only
	std::string yellowLettersOnly = GetInputLetters(yellowLetters);

	RemoveDuplicateLetters(blackLetters, greenLettersOnly);
	RemoveDuplicateLetters(blackLetters, yellowLettersOnly);	
	RemoveDuplicateLetters(blackLetters, m_allInputLetters);

	timer++;
	//Load variable wordsIndex with only nessesary words indexes
	if (m_wordsIndex.empty()) // The code inside this if condition will only run on the first call
	{
		if (isLetterAvailable(greenLetters))
		{
			m_CunnecessaryWordsRemover->AddTheWordsIndexThatContain_GreenChar(greenLetters, m_wordsIndex);
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatDoNotContain_YellowChar(yellowLetters, m_wordsIndex);
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatContain_BlackChars(blackLetters, m_wordsIndex);
		}
		else if (isLetterAvailable(yellowLetters))
		{
			m_CunnecessaryWordsRemover->AddTheWordsIndexthatContain_YellowChar(yellowLetters, m_wordsIndex);
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatContain_BlackChars(blackLetters, m_wordsIndex);
		}
		else
			m_CunnecessaryWordsRemover->AddTheWordsIndexThatDoNotContain_BlackChars(blackLetters, m_wordsIndex);

		if (m_wordsIndex.empty())
			return Error_occured;

		// Shuffle words in the order of highest matching possible
		m_CshuffleWordsByHighestPossibleMatch->Run(m_wordsIndex);

		//Divide words in the repeating and non-repeating letter wise
		WordsWithRepeatingAndNonRepeatingLetters::AddTheWordsIndexes(m_buffer, m_wordsIndex, m_nonRepeatingLetterWordsIndex,
			m_repeatingLetterWordsIndex, m_wordLength);
	}
	else // 
	{

		if (m_wordsIndex.empty())
			return Error_occured;

		// Remove unnecessary words indexes from variable wordsIndex
		if (isLetterAvailable(greenLetters))
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatDoNotContain_GreenChar(greenLetters, m_wordsIndex);
		if (isLetterAvailable(yellowLetters))
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatDoNotContain_YellowChar(yellowLetters, m_wordsIndex);
		if (isLetterAvailable(blackLetters))
			m_CunnecessaryWordsRemover->RemoveTheWordsIndexThatContain_BlackChars(blackLetters, m_wordsIndex);

		// Shuffle words in the order of highest matching possible
		m_CshuffleWordsByHighestPossibleMatch->Run(m_wordsIndex);

		//Divide words in the repeating and non-repeating letter wise
		WordsWithRepeatingAndNonRepeatingLetters::RemoveTheWordsIndexes(m_buffer, m_wordsIndex, m_nonRepeatingLetterWordsIndex,
			m_repeatingLetterWordsIndex, m_wordLength);

	}
	
	//Save all user input letters
	m_allInputLetters += greenLettersOnly;
	m_allInputLetters += yellowLettersOnly;
	m_allInputLetters += blackLetters;

	return 0;

}

std::string WordleSolver::GetInputLetters(std::string& inputLetters)
{
	std::string letters;
	std::vector<int> charPositions;

	CustomAlgorithms::GetTheCharIndex(inputLetters, charPositions);

	for (int i = 0; i < charPositions.size(); i++)
	{
		letters += inputLetters[i];
	}
	return letters;
}

void WordleSolver::RemoveDuplicateLetters(std::string& blackLetters, std::string& searchingIn)
{
	if (blackLetters.empty() || searchingIn.empty())
		return;

	std::vector<int> lettersIndex;

	//Get the duplicate black letters index; erasing letters from front here can cause skipping the next letter
	for (int i = 0; i < blackLetters.size(); i++)
	{
		std::string::iterator it = std::find(searchingIn.begin(), searchingIn.end(), blackLetters[i]);

		if (it != searchingIn.end()) //if true then letter is available
		{
			lettersIndex.push_back(i);
		}
	}
	if (lettersIndex.empty())
		return;

	std::sort(lettersIndex.begin(), lettersIndex.end());

	//Delete duplicate black letters( from last index to first )
	for (int i = lettersIndex.size() - 1; i >= 0; i--)
	{
		blackLetters.erase(blackLetters.begin() + lettersIndex[i], blackLetters.begin() + lettersIndex[i] + 1);
	}
}

bool WordleSolver::isLetterAvailable(std::string& letters)
{	
	for (char c : letters)
	{
		if (c != '*')
			return true;
	}
	return false;
}

bool WordleSolver::isDataEmpty(std::vector<int>& data)
{

	if (data.empty())
		return true;

	return false;
}

int WordleSolver::NumberOfRepeatedLettersInUserInput(std::string& inputCharacters)
{
	int repeatedLetters = 0;
	int fromNextLetter = 1;
	for (int i = 0; i < inputCharacters.size(); i++)
	{
		auto it = std::find(inputCharacters.begin() + i + fromNextLetter, inputCharacters.end(), inputCharacters[i]);

		if (it != inputCharacters.end())
		{
			repeatedLetters++;
		}
	}
	return repeatedLetters;
}

void WordleSolver::FindDuplicateLetters(std::string& inputCharacters, std::vector<int>& duplicateLetters)
{

	int fromNextLetter = 1;
	for (int i = 0; i < inputCharacters.size(); i++)
	{
		auto it = std::find(inputCharacters.begin() + i + fromNextLetter, inputCharacters.end(), inputCharacters[i]);

		if (it != inputCharacters.end())
		{
			auto ifLetterAlreadyPresentInVar = std::find(duplicateLetters.begin(), duplicateLetters.end(), inputCharacters[i]);

			if (ifLetterAlreadyPresentInVar == duplicateLetters.end()) //if the character not found
				duplicateLetters.push_back(i);

			//Insert the second duplicate character
			int foundPos = ifLetterAlreadyPresentInVar - duplicateLetters.begin();
			duplicateLetters.push_back(foundPos);

		}
	}
}

bool WordleSolver::ShouldRestart(int whichFunctionToCall)
{
	if (whichFunctionToCall == 0)
	{
		std::cout << "Restarting to solve a new Wordle\n\n";
		return true;
	}

	return false;
}

std::string WordleSolver::GetWordsFromIndex(std::vector<int>& nonRepeatingLetterWordsIndex, 
	std::vector<int>& repeatingLetterWordsIndex, int numberOfWordsToCopy)
{		

	std::string allWords;
	int numberOfRepeatingWordsToShow = 0;
	int numberOfNonRepeatingWordsToShow = 0;

	if (nonRepeatingLetterWordsIndex.empty() && repeatingLetterWordsIndex.empty())
		return allWords = "No words available";

	if (nonRepeatingLetterWordsIndex.size() < numberOfWordsToCopy)
	{
		numberOfRepeatingWordsToShow = numberOfWordsToCopy - nonRepeatingLetterWordsIndex.size();
		numberOfNonRepeatingWordsToShow = nonRepeatingLetterWordsIndex.size();
	}
	else
		numberOfNonRepeatingWordsToShow = numberOfWordsToCopy;

	for (int i = 0; i < numberOfNonRepeatingWordsToShow; i++)
	{
		for (int firstPos = nonRepeatingLetterWordsIndex[i]; firstPos < nonRepeatingLetterWordsIndex[i] + m_wordLength; firstPos++)
			allWords += m_buffer[firstPos];
		
		allWords += ' ';
	}


	if (repeatingLetterWordsIndex.size() < numberOfRepeatingWordsToShow)
		numberOfRepeatingWordsToShow = repeatingLetterWordsIndex.size();

	//Show Repeating Letter words if (NonRepeatingLetterWordsIndex.size() < numberOfWordsToShow) or NonRepeatingLetterWordsIndex.empty()
	for (int i = 0; i < numberOfRepeatingWordsToShow; i++)
	{
		for (int firstPos = repeatingLetterWordsIndex[i]; firstPos < repeatingLetterWordsIndex[i] + m_wordLength; firstPos++)
			allWords += m_buffer[firstPos];

		allWords += ' ';
	}

	
	return allWords;
}

void WordleSolver::ClearData()
{

	m_wordsIndex.clear();
	m_nonRepeatingLetterWordsIndex.clear();
	m_repeatingLetterWordsIndex.clear();

	m_WouldYouLikeToShowWords = false;
	m_showDataOntheScreen = NULL;

	m_totalLetters = 0;
	m_numberOfNewGreenLettersEntered = 0;
	m_allGreenLettersPos.clear();

}

WordleSolver::~WordleSolver()
{
	ClearData();

	//Delete class objects
	delete m_CunnecessaryWordsRemover;
	delete m_CshuffleWordsByHighestPossibleMatch;
}

/*
	Open file

	Read Data From File Into a Buffer

	choose black green yellow(int whichFunc) : User Input

	call the black, green or yellow function; unnecessary words are removed

	Remove unncessary words (black, yellow, green); char* buffer

	Words By Most Available char

	Sort the words By Value In Descending Order

	Find noRepeating letter words( FindUniqueCharacter() ); char* UniqueBuffer


	Sort By Value In Descending Order( WholeBuffer, file_size)

	WriteInFile(UniqueBuffer) Only Unique Data

	WriteInFile(Buffer) Whole Data

*/


