#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>


class CustomAlgorithms
{
private:


public:


    void Get_the_char_only(std::string& word);
    void GetTheCharIndex(std::string& inputCharacters, std::vector<int>& charIndex);

    int TotalLettersEnteredByUser(std::string& inputCharacters);

    int TotalGreenLettersEnteredByUser(std::string& inputCharacters, std::vector<int>& CharPos);

    void lower_to_upper_case(std::string& character);
    int CountSpaces(int file_size, int wordLength);

    int GetWordsFirstIndex(int index);

    //QuickSort

    void QuickSortInAscendingOrder(std::vector<std::pair<int, int>>& data, int left, int right);
    void QuickSortInDescendingOrder(std::vector<std::pair<int, int>>& data, int left, int right);

    void QuickSortInAscendingOrder(std::vector<int>& data, int left, int right);
    void QuickSortInDescendingOrder(std::vector<int>& data, int left, int right);

private:

    int PartitionFuncInAscendingOrder(std::vector<int>& data, int left, int right, int pivot);
    int PartitionFuncInDescendingOrder(std::vector<int>& data, int left, int right, int pivot);

    int PartitionFuncInAscendingOrder(std::vector<std::pair<int, int>>& data, int left, int right, int pivot);
    int PartitionFuncInDescendingOrder(std::vector<std::pair<int, int>>& data, int left, int right, int pivot);

    void swap(std::vector<int>& data, int num1, int num2);
    void swap(std::vector<std::pair<int, int>>& data, int num1, int num2);


};