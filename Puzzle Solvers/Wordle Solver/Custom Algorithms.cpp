#include "Custom Algorithms.h"


void CustomAlgorithms::Get_the_char_only(std::string& userInput)
{

    for (int i = 0; i < userInput.size(); i++)
    {
        if (userInput[i] == '*')
            userInput.erase(userInput.begin() + i);
    }
}

void CustomAlgorithms::GetTheCharIndex(std::string& inputCharacters, std::vector<int>& char_pos)
{
    for (int i = 0; i < inputCharacters.size(); i++)
    {
        if (inputCharacters[i] != '*')
            char_pos.push_back(i);
    }
}

int CustomAlgorithms::TotalLettersEnteredByUser(std::string& inputCharacters)
{
    int totalLetters = 0;
    for (int i = 0; i < inputCharacters.size(); i++)
    {
        if (inputCharacters[i] != '*')
            totalLetters += 1;
    }
    return totalLetters;
}

int CustomAlgorithms::TotalGreenLettersEnteredByUser(std::string& inputCharacters, std::vector<int>& charPos)
{
    int newGreenLetters = 0;
    for (int i = 0; i < inputCharacters.size(); i++)
    {
        if (inputCharacters[i] != '*')
        {
            auto isAvailable = std::find(charPos.begin(), charPos.end(), i);

            if (isAvailable == charPos.end()) // if data is not avilable the insert
            {
                newGreenLetters++;
                charPos.push_back(i);
            }
        }
    }

    return newGreenLetters;
}

void CustomAlgorithms::lower_to_upper_case(std::string& character)
{
    for (int i = 0; i < character.size(); i++)
    {
        if (character[i] >= 97 && character[i] <= 122)
            character[i] = character[i] - 32;
    }
}

int CustomAlgorithms::CountSpaces(int file_size, int wordLength)
{
    // if wordLength == 5 and file_size is <= 5 then return 0; 
    // if file_size is 5 then there are 5 chars and index is from 0..4 means no space available thus return 0
    if (file_size <= wordLength)
        return 0;
    int spaces = (file_size + 1) / (wordLength + 1);
    return spaces;
}

int CustomAlgorithms::GetWordsFirstIndex(int index)
{
    int remainder = (index + 1) % 6;
    int firstIndex = index - remainder;

    return firstIndex;
}



//QuickSortInDescendingOrder

void CustomAlgorithms::QuickSortInAscendingOrder(std::vector<int>& data, int left, int right)
{
    if (right - left <= 0)
        return;

    int pivot = data[right];
    int partition = PartitionFuncInAscendingOrder(data, left, right, pivot);
    QuickSortInAscendingOrder(data, left, partition - 1);
    QuickSortInAscendingOrder(data, partition + 1, right);

}

int CustomAlgorithms::PartitionFuncInAscendingOrder(std::vector<int>& data, int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right;

    while (true)
    {
        while (data[++leftPointer] < pivot) {}

        while (rightPointer > 0 && data[--rightPointer] > pivot) {}

        if (leftPointer >= rightPointer)
            break;
        else
            swap(data, leftPointer, rightPointer);
    }

    swap(data, leftPointer, right);

    return leftPointer;
}

void CustomAlgorithms::QuickSortInDescendingOrder(std::vector<int>& data, int left, int right)
{
    if (right - left <= 0)
        return;

    int pivot = data[right];
    int partition = PartitionFuncInDescendingOrder(data, left, right, pivot);
    QuickSortInDescendingOrder(data, left, partition - 1);
    QuickSortInDescendingOrder(data, partition + 1, right);

}

int CustomAlgorithms::PartitionFuncInDescendingOrder(std::vector<int>& data, int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right;

    while (true)
    {
        while (data[++leftPointer] > pivot) {}

        while (rightPointer > 0 && data[--rightPointer] < pivot) {}

        if (leftPointer >= rightPointer)
            break;
        else
            swap(data, leftPointer, rightPointer);
    }

    swap(data, leftPointer, right);

    return leftPointer;
}

void CustomAlgorithms::swap(std::vector<int>& data, int num1, int num2)
{
    int temp = data[num1];
    data[num1] = data[num2];
    data[num2] = temp;
}

void CustomAlgorithms::QuickSortInAscendingOrder(std::vector<std::pair<int, int>>& data, int left, int right)
{
    if (right - left <= 0)
        return;

    int pivot = data[right].second;
    int partition = PartitionFuncInAscendingOrder(data, left, right, pivot);
    QuickSortInDescendingOrder(data, left, partition - 1);
    QuickSortInDescendingOrder(data, partition + 1, right);

}

int CustomAlgorithms::PartitionFuncInAscendingOrder(std::vector<std::pair<int, int>>& data, int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right;

    while (true)
    {
        while (data[++leftPointer].second < pivot) {}

        while (rightPointer > 0 && data[--rightPointer].second > pivot) {}

        if (leftPointer >= rightPointer)
            break;
        else
            swap(data, leftPointer, rightPointer);
    }

    swap(data, leftPointer, right);

    return leftPointer;
}

void CustomAlgorithms::QuickSortInDescendingOrder(std::vector<std::pair<int, int>>& data, int left, int right)
{
    if (right - left <= 0)
        return;

    int pivot = data[right].second;
    int partition = PartitionFuncInDescendingOrder(data, left, right, pivot);
    QuickSortInDescendingOrder(data, left, partition - 1);
    QuickSortInDescendingOrder(data, partition + 1, right);

}

int CustomAlgorithms::PartitionFuncInDescendingOrder(std::vector<std::pair<int, int>>& data, int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right;

    while (true)
    {
        while (data[++leftPointer].second > pivot) {}

        while (rightPointer > 0 && data[--rightPointer].second < pivot) {}

        if (leftPointer >= rightPointer)
            break;
        else
            swap(data, leftPointer, rightPointer);
    }

    swap(data, leftPointer, right);

    return leftPointer;
}

void CustomAlgorithms::swap(std::vector<std::pair<int, int>>& data, int num1, int num2)
{
    std::pair<int, int> temp = data[num1];
    data[num1] = data[num2];
    data[num2] = temp;
}