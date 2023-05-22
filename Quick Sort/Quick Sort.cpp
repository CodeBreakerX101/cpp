
#include <iostream>

void QuickSort(int left, int right);
int PartitionFunc(int left, int right, int pivot);
void swap(int num1, int num2);
void ShowData();

int data[] = { 3,8,9,5,7,4,6,11 };
int main()
{
    int dataSize = std::size(data);
    std::cout << dataSize << ' ' << '\n';

    ShowData();

    QuickSort(0, dataSize - 1);

    ShowData();


    return 0;
}

int PartitionFunc(int left, int right, int pivot)
{
    int leftPointer = left - 1;
    int rightPointer = right ;

    while (true)
    {
        while (data[++leftPointer] < pivot) {}

        while (rightPointer > 0 && data[--rightPointer] > pivot) {}

        if (leftPointer >= rightPointer)
            break;
        else
            swap(leftPointer, rightPointer);
    }

    //std::swap(leftPointer, right);
    std::cout << "Swap " << data[leftPointer] << " <-> " << data[rightPointer] << '\n';
    swap(leftPointer, right);

    return leftPointer;

}


void QuickSort(int left, int right)
{
    if (right - left <= 0)
        return;

    int pivot = data[right];
    int partition = PartitionFunc(left, right, pivot);
    QuickSort(left, partition - 1);
    QuickSort(partition + 1, right);

}
void ShowData()
{
    for (int i = 0; i < std::size(data); i++)
        std::cout << data[i] << " ";

    std::cout << '\n';
}
void swap(int num1, int num2) 
{
    int temp = data[num1];
    data[num1] = data[num2];
    data[num2] = temp;
}
