
#pragma once
#include "Words With Highest Possible Match.h"


const int search_range = 10;

WordsWithHighestPossibleMatch::WordsWithHighestPossibleMatch(char* buffer, int wordLength)
{
	this->m_buffer = buffer;
	this->m_wordLength = wordLength;

}

void WordsWithHighestPossibleMatch::Run(std::vector<int>& wordsIndex)
{

	m_buffer_copy_size = wordsIndex.size() * m_wordLength;
	this->m_buffer_copy = new char[m_buffer_copy_size];

	int buffer_copy_length = m_buffer_copy_size - 1;
	m_constRight = buffer_copy_length - 1;


	CopyTheBufferWithNoSpaces(m_buffer, m_buffer_copy, wordsIndex);

	SortTheBufferCopy(m_buffer_copy, m_buffer_copy_size);

	GetFirstIndexFromSortedBuffer(m_buffer_copy, 0, buffer_copy_length, m_charsFirstIndex);

	GetEveryCharsValue(m_charsFirstIndex, m_buffer_copy_size, m_everyCharsValue);

	GetCharAndItsValue(m_buffer_copy, m_buffer_copy_size, m_charsFirstIndex, m_charAndItsValue);

	GetTheWordsFirstIndexAndItsValue(m_buffer, wordsIndex, m_charAndItsValue, m_wordsFirstIndexAndValue);

	SortWordsByValueInDescendingOrder(m_wordsFirstIndexAndValue);

	GetWordsIndex(m_wordsFirstIndexAndValue, wordsIndex);

	ClearData();

}

void WordsWithHighestPossibleMatch::CopyTheBufferWithNoSpaces(char* buffer, char* buffer_copy, std::vector<int>& wordsIndex)
{
	int next = 0;

	for (int index : wordsIndex)
	{
		for (int j = index; j < index + m_wordLength; j++)
		{
			buffer_copy[next] = buffer[j];
			next++;
		}
	}
}

void WordsWithHighestPossibleMatch::SortTheBufferCopy(char* buffer, int file_size)
{
	Algorithms::QuickSortInAscendingOrder(buffer, 0, file_size - 1);
}

void WordsWithHighestPossibleMatch::GetFirstIndexFromSortedBuffer(char* sortedBuffer, int left, int right,
	std::vector<int>& charsFirstIndex)
{

	if (sortedBuffer[left] == sortedBuffer[right])
	{
		return GetFirstIndexFromSortedBuffer(sortedBuffer, right, m_previousRight, charsFirstIndex);
	}
	else if (right - left >= 1 && right - left <= search_range)
	{
		int nextIndex = 0;
		for (int i = left; i <= right; i++)
		{
			if (sortedBuffer[i] != sortedBuffer[left])
			{
				nextIndex = i;
				charsFirstIndex.push_back(i);
				break;
			}
		}
		if (sortedBuffer[nextIndex] != sortedBuffer[m_constRight])
			return GetFirstIndexFromSortedBuffer(sortedBuffer, nextIndex, m_constRight, charsFirstIndex);
	}
	else if (sortedBuffer[left] != sortedBuffer[right])
	{
		m_previousRight = right;
		int mid = left + ((right - left) / 2);

		return GetFirstIndexFromSortedBuffer(sortedBuffer, left, mid, charsFirstIndex);
	}

	//First data
	if (right == m_constRight)
		if (!charsFirstIndex.empty())
			charsFirstIndex.insert(charsFirstIndex.begin(), 0);


}

void WordsWithHighestPossibleMatch::GetEveryCharsValue(std::vector<int>& charsFirstIndex, int buffer_copy_size,
	std::vector<int>& everyCharsValue)
{
	int charsFirstIndexLength = charsFirstIndex.size() - 1;
	for (int i = 0; i < charsFirstIndexLength; i++)
	{
		int totalCharsAmount = charsFirstIndex[i + 1] - charsFirstIndex[i];
		everyCharsValue.push_back(totalCharsAmount);
	}

	//last data
	everyCharsValue.push_back(buffer_copy_size - charsFirstIndex[charsFirstIndexLength]);
}

void WordsWithHighestPossibleMatch::AssignCharInCharAndItsValue(std::vector < std::pair<char, int> >& charAndItsValue)
{
	for (char i = 'A'; i <= 'Z'; i++)
		charAndItsValue.push_back(std::pair<char, int>(i, 0));
}

void WordsWithHighestPossibleMatch::GetCharAndItsValue(char* sortedBuffer, int file_size, std::vector<int>& charsFirstIndex,
	std::vector < std::pair<char, int> >& charAndItsValue)
{

	AssignCharInCharAndItsValue(charAndItsValue);

	int charsFirstIndexLength = charsFirstIndex.size() - 1;
	for (int i = 0; i < charsFirstIndexLength; i++)
	{
		int index = sortedBuffer[charsFirstIndex[i]] - 'A';
		int value = charsFirstIndex[i + 1] - charsFirstIndex[i];

		charAndItsValue[index].second = value;
	}

	//last data
	int lastIndex = charsFirstIndex.size() - 1;
	int index = sortedBuffer[charsFirstIndex[lastIndex]] - 'A';
	int value = file_size - charsFirstIndex[lastIndex];

	charAndItsValue[index].second = value;

}
//Add up every chars value of a word and get that word's first index
void WordsWithHighestPossibleMatch::GetTheWordsFirstIndexAndItsValue(char* buffer, std::vector<int>& wordsIndex,
	std::vector < std::pair<char, int> >& charAndItsValue,
	std::vector< std::pair<int, int> >& wordsFirstIndexAndValue)
{

	for (auto& i : wordsIndex)
	{
		if (buffer[i] == ' ')
			continue;

		int wordValue = 0;
		for (int j = i; j < i + m_wordLength; j++)
		{
			wordValue += charAndItsValue[buffer[j] - 'A'].second;
		}
		wordsFirstIndexAndValue.push_back(std::pair<int, int>(i, wordValue));

	}
}

void WordsWithHighestPossibleMatch::SortWordsByValueInDescendingOrder(std::vector< std::pair<int, int> >& wordsFirstIndexAndValue)
{
	CustomAlgorithms::QuickSortInDescendingOrder(wordsFirstIndexAndValue, 0, wordsFirstIndexAndValue.size() - 1);
}

void WordsWithHighestPossibleMatch::GetWordsIndex(std::vector< std::pair<int, int> >& wordsFirstIndexAndValue,
	std::vector<int>& wordsIndex)
{

	wordsIndex.clear();

	for (int i = 0; i < wordsFirstIndexAndValue.size(); i++)
	{
		wordsIndex.push_back(wordsFirstIndexAndValue[i].first);
	}
}

void WordsWithHighestPossibleMatch::ClearData()
{

	delete[] m_buffer_copy;
	m_buffer_copy_size = 0;

	m_charsFirstIndex.clear();
	m_everyCharsValue.clear();

	m_charAndItsValue.clear();
	m_wordsFirstIndexAndValue.clear();

}

void WordsWithHighestPossibleMatch::ShowBuffer(char* buffer, int bufferSize)
{
	for (int i = 0; i < bufferSize; i++)
		std::cout << buffer[i];
}
void WordsWithHighestPossibleMatch::ShowIndexData(char* buffer, std::vector<int>& charsFirstIndex, int wordLength)
{
	int count = 1;
	for (int i : charsFirstIndex)
	{
		std::cout << count << ' ';
		for (int j = i; j < i + wordLength; j++)
			std::cout << buffer[j];
		std::cout << '\n';
		count++;
	}
	std::cout << '\n';
}

WordsWithHighestPossibleMatch::~WordsWithHighestPossibleMatch()
{
	delete[] m_buffer_copy;
}