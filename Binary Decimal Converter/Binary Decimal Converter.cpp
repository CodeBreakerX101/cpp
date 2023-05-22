
#include <iostream>
#include <math.h>

void Binary_to_Decimal();
void find_the_right_number(int& value, int& exponent);
void Decimal_to_Binary();

int main()
{
    int number = 0;
    std::cout << "Press 1 To Convert Binary To Decimal\n";
    std::cout << "Press 2 To Convert Decimal To Binary\n";

    std::cin >> number;

    switch (number)
    {
    case 1:
        Binary_to_Decimal();
        break;
    case 2:
        Decimal_to_Binary();
        break;
    }
    


}
void Binary_to_Decimal()
{
    std::string number = "";
    int decimal = 0;
    bool characterFree = true;

    std::cout << "Type Binary number\n";
    std::cin >> number;

    for (int i = std::size(number) - 1; i >= 0; i--)
    {

        if (number[i] == '1')
        {
            decimal += pow(2, (std::size(number) - 1) - i);
        }
        else if (number[i] == '0')
        {

        }
        else
        {
            std::cout << "characters are not allowed\n";
            characterFree = false;
        }

    }
    if (characterFree)
        std::cout << decimal;
}
void Decimal_to_Binary()
{
    int decimal = 0, value = 0, exponent = 0;
    std::string binary = "";
    std::cout << "Type Decimal Number\n";
    std::cin >> decimal;
    value = decimal;

    find_the_right_number(value, exponent);
   
    value = decimal - pow(2, exponent);

    if (value == 0)
    {
        binary += "1";
        for (int x = 0; x < exponent; x++)
        {
            binary += "0";
        }
    }
    else
    {
        binary += "1";
        
        for (int x = 0; x < exponent; x++)
        {
            if (value == pow(2, exponent - 1 - x))
            {
                binary += "1";
                value -= pow(2, exponent - 1 - x);
            }
            else if (value < pow(2, exponent - 1 - x))
            {
                binary += "0";               
            }
            else if (value > pow(2, exponent - 1 - x))
            {
                binary += "1"; 
                value -= pow(2, exponent - 1 - x);
       
            }
            else if (value == 0)
            {
                binary += "0";
            }

        }
    }
    std::cout << binary << "\n";
}


void find_the_right_number(int& value,int& exponent)
{
    if (value == (pow(2, 8)))
    {
        exponent = 8;
    }
    else if (value > (pow(2, 8) ))
    {
        int expo = 8;
        while (value > (pow(2, expo) - 1))
        {
            expo += 1;
        }
        exponent = expo - 1;
    }
    else
    {
        int expo = 8;
        while (value < (pow(2, expo)))
        {
            expo -= 1;
        }
        exponent = expo;
    }
}