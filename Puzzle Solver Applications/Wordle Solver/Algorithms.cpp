
#include "Algorithms.h"

int Algorithms::BinarySearch(std::vector<int>& data, int l, int r, int value)
{

    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (data[mid] == value)
            return mid;

        if (data[mid] > value)
            return BinarySearch(data, l, mid - 1, value);
        else
            return BinarySearch(data, mid + 1, r, value);
    }

    return -1;
}
