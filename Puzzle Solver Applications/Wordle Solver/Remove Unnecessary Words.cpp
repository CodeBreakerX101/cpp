
#include "Remove Unnecessary Words.h"

RemoveUnnecessaryWords::RemoveUnnecessaryWords(char* buffer, int buffer_size, int wordLength)
{
	this->m_buffer = buffer;
	this->m_buffer_size = buffer_size;
	this->m_wordLength = wordLength;
}




//	Non black letters words will be taken.

void RemoveUnnecessaryWords::AddTheWordsIndexThatDoNotContain_BlackChars(std::string& blackLetters, std::vector<int>& blackCharIndex)
{

	if (blackLetters.empty())
		return;
	

	for (int i = 0; i < m_buffer_size; i++)
	{
		bool character_available = false;

		if (m_buffer[i] == 32)
			continue;

		for (int j = i; j < i + m_wordLength; j++)
		{
			for (int matching = 0; matching < blackLetters.size(); matching++)
			{
				if ((m_buffer[j] == blackLetters[matching]))
				{
					character_available = true;
					break;
				}
			}
			if (character_available)
				break;
		}

		if (!character_available)
			blackCharIndex.push_back(i);

		i += m_wordLength;
	}
}


//	Only the indexes of necessary words will be taken.
void RemoveUnnecessaryWords::AddTheWordsIndexthatContain_YellowChar(std::string& yellowLetters, std::vector<int>& YellowCharIndex)
{

	std::vector<int> charIndex;
	GetTheCharIndex(yellowLetters, charIndex);

	if (charIndex.empty())
		return;

	for (int i = 0; i < charIndex.size(); i++)
		m_allInputCharacters += yellowLetters[charIndex[i]];

	int words_last_char = 4;

	for (int i = 0; i < m_buffer_size; i++)
	{
		bool character_available = false;

		if (m_buffer[i] == ' ')
			continue;

		for (int characterPos = 0; characterPos < charIndex.size(); characterPos++)
		{
			for (int j = i; j <= i + words_last_char + 1; j++)
			{
				if (j == i + charIndex[characterPos] && m_buffer[j] == yellowLetters[charIndex[characterPos]])
				{
					character_available = false;
					break;
				}
				else if (m_buffer[j] == yellowLetters[charIndex[characterPos]])
				{
					character_available = true;
				}
			}

			if (!character_available || characterPos >= charIndex.size() - 1)
				break;
			else
				character_available = false;
		}

		if (character_available)
			YellowCharIndex.push_back(i);

		i += words_last_char;
	}

}

//	Only the indexes of necessary words will be taken.
void RemoveUnnecessaryWords::AddTheWordsIndexThatContain_GreenChar(std::string& greenLetters, std::vector<int>& GreenCharIndex)
{
	std::vector<int> charIndex;

	// greenLetters == **L*A, task is to get the chars index only
	CustomAlgorithms::GetTheCharIndex(greenLetters, charIndex);

	if (charIndex.empty())
		return;


	for (int i = 0; i < charIndex.size(); i++)
		m_allInputCharacters += greenLetters[charIndex[i]];

	int words_last_char = m_wordLength - 1;

	for (int i = 0; i < m_buffer_size; i++)
	{
		bool character_available = false;

		if (m_buffer[i] == ' ')
			continue;

		int k = 0;

		for (; k < charIndex.size(); k++)
		{
			if (m_buffer[i + charIndex[k]] != greenLetters[charIndex[k]])
				break;
		}

		if (k > (charIndex.size() - 1))
			GreenCharIndex.push_back(i);

		i += words_last_char;
	}
}

void RemoveUnnecessaryWords::RemoveTheWordsIndexThatContain_BlackChars(std::string& blackLetters, std::vector<int>& blackCharIndex)
{

	if (blackLetters.empty())
		return;

	RemoveUnnecessaryWords::RemoveReEnteredBlackChars(m_allInputCharacters, blackLetters);
	RemoveUnnecessaryWords::SaveBlackInputChar(m_allInputCharacters, blackLetters);

	std::vector<int> necessaryIndexes;

	for (int i = 0; i < blackCharIndex.size(); i++)
	{
		bool character_available = false;

		for (int j = blackCharIndex[i]; j < blackCharIndex[i] + m_wordLength; j++)
		{
			for (int matching = 0; matching < blackLetters.size(); matching++)
			{
				if ((m_buffer[j] == blackLetters[matching]))
				{
					character_available = true;
					break;
				}
			}
			if (character_available)
				break;
		}
		if (!character_available)
		{
			necessaryIndexes.push_back(blackCharIndex[i]);
		}
	}

	ClearVectorData(blackCharIndex);

	AddNecessaryIndex(necessaryIndexes, blackCharIndex);
}

void RemoveUnnecessaryWords::RemoveTheWordsIndexThatDoNotContain_YellowChar(std::string& yellowLetters, std::vector<int>& yellowCharIndex)
{
	std::vector<int> charIndex, necessaryIndexes;
	GetTheCharIndex(yellowLetters, charIndex);

	if (charIndex.empty())
		return;

	for (int i : yellowCharIndex)
	{
		bool character_available = false;

		for (int characterPos = 0; characterPos < charIndex.size(); characterPos++)
		{
			for (int j = i; j <= i + m_wordLength; j++)
			{
				if (j == i + charIndex[characterPos] && m_buffer[j] == yellowLetters[charIndex[characterPos]])
				{
					character_available = false;
					break;
				}
				else if (m_buffer[j] == yellowLetters[charIndex[characterPos]])
				{
					character_available = true;
				}
			}

			if (!character_available || characterPos >= charIndex.size() - 1)
				break;
			else
				character_available = false;
		}

		if (character_available)
			necessaryIndexes.push_back(i);
	}

	ClearVectorData(yellowCharIndex);

	AddNecessaryIndex(necessaryIndexes, yellowCharIndex);
}

void RemoveUnnecessaryWords::RemoveTheWordsIndexThatDoNotContain_GreenChar(std::string& greenLetters, std::vector<int>& greenCharIndex)
{
	std::vector<int> charIndex, necessaryIndexes;

	GetTheCharIndex(greenLetters, charIndex);

	if (charIndex.empty())
		return;

	for (int i : greenCharIndex)
	{

		int k = 0;
		for (; k < charIndex.size(); k++)
		{
			if (m_buffer[i + charIndex[k]] != greenLetters[charIndex[k]])
				break;
		}

		if (k > charIndex.size() - 1)
			necessaryIndexes.push_back(i);

	}

	ClearVectorData(greenCharIndex);

	AddNecessaryIndex(necessaryIndexes, greenCharIndex);

}
void RemoveUnnecessaryWords::SaveBlackInputChar(std::string& allInputChars, std::string& inputChars)
{
	for (char character : inputChars)
		allInputChars += character;
}
void RemoveUnnecessaryWords::RemoveReEnteredBlackChars(std::string& allInputChars, std::string& inputChars)
{
	if (allInputChars.empty())
		return;

	std::vector<char> nonMatchedCharacters;

	for (char character : inputChars)
	{
		bool found = false;
		for (char allCharacter : allInputChars)
		{
			if (character == allCharacter)
				found = true;
		}
		if (!found)
			nonMatchedCharacters.push_back(character);
	}
	inputChars.clear();

	//insert letters
	for (char character : nonMatchedCharacters)
		inputChars += character;

}
void RemoveUnnecessaryWords::ClearVectorData(std::vector<int>& data)
{
	data.clear();
}
void RemoveUnnecessaryWords::AddNecessaryIndex(std::vector<int>& necessaryIndex, std::vector<int>& wordsIndex)
{
	wordsIndex.assign(necessaryIndex.begin(), necessaryIndex.end());
}

RemoveUnnecessaryWords::~RemoveUnnecessaryWords()
{
	delete[] m_buffer;
}