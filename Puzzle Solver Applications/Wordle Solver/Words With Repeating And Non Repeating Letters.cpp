
#include "Words With Repeating And Non Repeating Letters.h"


void WordsWithRepeatingAndNonRepeatingLetters::FindBySearchingInWholeBuffer(char* buffer, int file_size,
    std::vector<int>& NoRepeatingLetterWordsIndex, std::vector<int>& repeatingLetterWordsIndex, int wordLength)
{
    int firstCharPos = 0;

    for (int i = 0; i < file_size; i++)
    {
        if (buffer[i] == 32)
        {
            firstCharPos = i + 1;
            continue;
        }

        int wordsPos = i;

        for (; wordsPos < firstCharPos + wordLength; wordsPos++)
        {
            if (buffer[i] == buffer[wordsPos + 1])
            {
                i = firstCharPos + wordLength - 1;
                break;
            }
        }

        if (wordsPos - i == wordLength)
        {
            NoRepeatingLetterWordsIndex.push_back(firstCharPos);
        }
        else
            repeatingLetterWordsIndex.push_back(firstCharPos);

    }
}

void WordsWithRepeatingAndNonRepeatingLetters::AddTheWordsIndexes(char* buffer, std::vector< int >& wordsIndex,
    std::vector<int>& NoRepeatingLetterWordsIndex, std::vector<int>& repeatingLetterWordsIndex, int wordleLength)
{
    for (int i = 0; i < wordsIndex.size(); i++)
    {
        bool hasRepeatedChar = false;
        for (int j = 0; j < wordleLength; j++)
        {
            for (int k = j + 1; k < wordleLength; k++)
            {
                if (buffer[wordsIndex[i] + j] == buffer[wordsIndex[i] + k])
                {
                    hasRepeatedChar = true;
                    break;
                }
            }

            if (hasRepeatedChar)
                break;
        }

        if (!hasRepeatedChar)
            NoRepeatingLetterWordsIndex.push_back(wordsIndex[i]);
        else
            repeatingLetterWordsIndex.push_back(wordsIndex[i]);
    }
}

void WordsWithRepeatingAndNonRepeatingLetters::RemoveTheWordsIndexes(char* buffer, std::vector<int>& wordsIndex,
    std::vector<int>& NoRepeatingLetterWordsIndex, std::vector<int>& repeatingLetterWordsIndex, int wordleLength)
{

    CustomAlgorithms::QuickSortInAscendingOrder(NoRepeatingLetterWordsIndex, 0, NoRepeatingLetterWordsIndex.size() - 1);

    std::vector<int> necessaryWordsIndexes;

    ClearVectorData(repeatingLetterWordsIndex);

    for (auto& i : wordsIndex)
    {
        int index = Algorithms::BinarySearch(NoRepeatingLetterWordsIndex, 0, NoRepeatingLetterWordsIndex.size() - 1, i);
        if (index != -1)
            necessaryWordsIndexes.push_back(i);
        else
            repeatingLetterWordsIndex.push_back(i);
    }

    ClearVectorData(NoRepeatingLetterWordsIndex);

    AddNecessaryIndex(NoRepeatingLetterWordsIndex, necessaryWordsIndexes);
}

void WordsWithRepeatingAndNonRepeatingLetters::ClearVectorData(std::vector<int>& data)
{
    data.clear();
}
void WordsWithRepeatingAndNonRepeatingLetters::AddNecessaryIndex(std::vector<int>& NoRepeatingLetterWordsIndex,
    std::vector<int>& necessaryIndex)
{

    for (int i : necessaryIndex)
        NoRepeatingLetterWordsIndex.push_back(i);

}

