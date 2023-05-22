
#include <iostream>
#include <string>
#include <vector>

void Shell_Sort(int data[], int size);

int main()
{
    
    int data[] = { 2,5,3,9,0,1,4,8,7,6,10,30,12 };

    Shell_Sort(data, std::size(data));

    for (int i = 0; i < std::size(data); i++)
    {
        std::cout << data[i] << " ";
    }


    return 0;
}

void Shell_Sort(int data[], int size)
{
    int interval = 1;
    int inner = 0, outer = 0;
    int value_to_insert;
    int i = 0;

    while (interval <= size / 3)
    {
        interval = interval * 3 + 1;
    }
    while (interval > 0)
    {
      
        for (outer = interval; outer < size; outer++)
        {
            value_to_insert = data[outer];
            inner = outer;

            while (inner > interval - 1 && data[inner - interval] >= value_to_insert)
            {
                data[inner] = data[inner - interval];
                inner -= interval;
            }
            data[inner] = value_to_insert;
        }
        interval = (interval - 1) / 3;
    }
        
}
