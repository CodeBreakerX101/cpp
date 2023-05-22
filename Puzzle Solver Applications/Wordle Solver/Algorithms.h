
#pragma once

#include <vector>

class Algorithms
{

private:



public:

    int BinarySearch(std::vector<int>& data, int l, int r, int value);

    /* template doesn't work with declaration in .cpp file */


    template<typename t1>
    void QuickSortInAscendingOrder(t1& data, int left, int right)
    {
        if (right - left <= 0)
            return;

        int pivot = data[right];
        int partition = PartitionFuncInAscendingOrder(data, left, right, pivot);
        QuickSortInAscendingOrder(data, left, partition - 1);
        QuickSortInAscendingOrder(data, partition + 1, right);

    }

    template<typename t1>
    void QuickSortInDescendingOrder(t1& data, int left, int right)
    {
        if (right - left <= 0)
            return;

        int pivot = data[right];
        int partition = PartitionFuncInDescendingOrder(data, left, right, pivot);
        QuickSortInDescendingOrder(data, left, partition - 1);
        QuickSortInDescendingOrder(data, partition + 1, right);

    }

    //std::vector<std::pair<t1,t2>>
    template<typename t1, typename t2>
    void QuickSortInAscendingOrder(std::vector<std::pair<t1, t2>>& data, int left, int right)
    {
        if (right - left <= 0)
            return;

        int pivot = data[right].second;
        int partition = PartitionFuncInAscendingOrder(data, left, right, pivot);
        QuickSortInAscendingOrder(data, left, partition - 1);
        QuickSortInAscendingOrder(data, partition + 1, right);

    }

    template<typename t1, typename t2>
    void QuickSortInDescendingOrder(std::vector<std::pair<t1, t2>>& data, int left, int right)
    {
        if (right - left <= 0)
            return;

        int pivot = data[right].second;
        int partition = PartitionFuncInDescendingOrder(data, left, right, pivot);
        QuickSortInDescendingOrder(data, left, partition - 1);
        QuickSortInDescendingOrder(data, partition + 1, right);

    }

private:

    template<typename t1>
    int PartitionFuncInAscendingOrder(t1& data, int left, int right, int pivot)
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

    template<typename t1>
    int PartitionFuncInDescendingOrder(t1& data, int left, int right, int pivot)
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

    template<typename t1>
    void swap(t1& data, int num1, int num2)
    {
        int temp = data[num1];
        data[num1] = data[num2];
        data[num2] = temp;
    }

    template<typename t1, typename t2>
    int PartitionFuncInAscendingOrder(std::vector<std::pair<t1, t2>>& data, int left, int right, int pivot)
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


    template<typename t1, typename t2>
    int PartitionFuncInDescendingOrder(std::vector<std::pair<t1, t2>>& data, int left, int right, int pivot)
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

    template<typename t1, typename t2>
    void swap(std::vector<std::pair<t1, t2>>& data, int num1, int num2)
    {
        std::pair<int, int> temp = data[num1];
        data[num1] = data[num2];
        data[num2] = temp;
    }

};



