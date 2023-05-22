
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

const int total_char_in_the_word = 7; ///SET THE NUMBER OF CHARACTCER CONTAINS IN THE WORD

void User_input(char character_contains_in_the_word[], char& must_character);
void Put_must_char_in_the_char_contains(std::string& char_contains, char must_char);
int  Copy_data_from_string_to_char_array_var(std::string& contains_char, char characters_contains_in_the_word[]);
void Sort_User_Input(char contains_char[], int size);

int Find_the_must_char_in_the_contains_char_var(char contains_char[], int contains_char_size, char must_char);

void Convert_to_capital(char characters_contains_in_the_word[], int char_size);

int  Open_File(std::fstream& word_file, fs::path& word_file_path, std::string file_address);
void Load_Words(std::fstream& word_file, fs::path& word_file_path, char* buffer);
void Show_words(fs::path& word_file_path, char* buffer);


void Find_Words(std::fstream& word_file, fs::path& word_file_path, char* buffer,
    char characters_contains_in_the_word[], int must_character_pos, std::vector<int>& found_pos);

bool Is_the_char_available(char* buffer, int pos, char char_contains_in_the_word[], int must_char_pos, bool& is_must_char_available);
int Binary_Search(char char_contains_in_the_word[], int l, int r, char character_to_find);

int main()
{
    //Initialing Variable
    char* buffer = nullptr;
    char characters_contains_in_the_word[total_char_in_the_word];
    char must_char;
    std::vector<int> found_pos;
    int must_char_pos = -1;

    std::string file_address = "C:\\Users\\Kakashi\\Desktop\\wordle.txt";

    std::fstream word_file;
    fs::path word_file_path;

    //Functions
    User_input(characters_contains_in_the_word, must_char);
    must_char_pos = Find_the_must_char_in_the_contains_char_var(characters_contains_in_the_word,
        total_char_in_the_word, must_char);

    Convert_to_capital(characters_contains_in_the_word, total_char_in_the_word);

    Open_File(word_file, word_file_path, file_address);
    buffer = new char[fs::file_size(word_file_path)];

    Load_Words(word_file, word_file_path, buffer);

    Find_Words(word_file, word_file_path, buffer, characters_contains_in_the_word, must_char_pos, found_pos);

    std::cout << "\nTotal words found " << found_pos.size() << "\n\n";
    if (!found_pos.empty())
    {
        for (int i = 0; i < found_pos.size(); i++)
        {
            for (int j = found_pos[i]; j < found_pos[i] + 5; j++)
            {
                std::cout << buffer[j];
            }
            std::cout << '\n';
        }
    }
    std::cin.ignore(10, '\n');
    std::cin.get();

    return 0;
}
void User_input(char character_contains_in_the_word[], char& must_character)
{
    std::string contains_char;


    std::cout << "Type Must Character\n";
    std::cin >> must_character;

    std::cin.ignore(10, '\n');

    std::cout << "Type all the  charaters contains in the word\n";
    std::cin >> contains_char;

    //Functions
    if (contains_char.empty() || must_character == NULL)
        return;

    Put_must_char_in_the_char_contains(contains_char, must_character);
    Copy_data_from_string_to_char_array_var(contains_char, character_contains_in_the_word);
    Sort_User_Input(character_contains_in_the_word, total_char_in_the_word);

}
void Put_must_char_in_the_char_contains(std::string& char_contains, char must_char)
{
    int is_must_char_available_in_contains_char_var = Binary_Search(&char_contains[0], 0, char_contains.size() - 1, must_char);

    if (is_must_char_available_in_contains_char_var == -1)
    {
        char_contains += must_char;
    }
}
int Copy_data_from_string_to_char_array_var(std::string& contains_char, char characters_contains_in_the_word[])
{
    if (contains_char.size() > total_char_in_the_word)
    {
        std::cout << "Character Contains in the input String more than char[] Initialized with\n "
            << "CHARACTER_CONTAINS_IN_THE_WORD " << contains_char.size() << " char[] var initialized with "
            << total_char_in_the_word << '\n';

        return -1;
    }
    for (int i = 0; i < contains_char.size(); i++)
    {
        characters_contains_in_the_word[i] = contains_char[i];
    }

    return 0;
}
void Sort_User_Input(char contains_char[], int size)
{
    for (int i = 0; i < size; i++)
    {
        bool swapped = false;

        for (int j = 0; j < size - 1; j++)
        {
            if (contains_char[j] > contains_char[j + 1])
            {
                std::swap(contains_char[j], contains_char[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}
void Convert_to_capital(char characters_contains_in_the_word[], int total_size)
{
    for (int i = 0; i < total_size; i++)
    {
        char the_char = characters_contains_in_the_word[i];
        if (the_char >= 97 && the_char <= 122)
            characters_contains_in_the_word[i] = the_char - 32;

    }
}
int Find_the_must_char_in_the_contains_char_var(char contains_char[], int contains_char_size, char must_char)
{
    return Binary_Search(contains_char, 0, contains_char_size, must_char);
}

int Open_File(std::fstream& word_file, fs::path& word_file_path, std::string file_address)
{
    word_file.open(file_address, std::ios::in | std::ios::binary);

    word_file_path = file_address;

    if (!word_file.is_open())
    {
        std::cout << "File Does Not Exists :: ERROR OPENING FILE IN FSTREAM\n";
        return -1;
    }
    if (!fs::exists(word_file_path))
    {
        std::cout << "File Does Not Exists:: ERROR::FS::PATH\n";
        return -1;
    }
    return 0;
}

void Load_Words(std::fstream& word_file, fs::path& word_file_path, char* buffer)
{
    int file_size = fs::file_size(word_file_path);

    word_file.read(buffer, file_size);

}
void Show_words(fs::path& word_file_path, char* buffer)
{
    int file_size = fs::file_size(word_file_path);

    for (int i = 0; i < file_size; i++)
        std::cout << buffer[i];

}
void Find_Words(std::fstream& word_file, fs::path& word_file_path, char* buffer, char characters_contains_in_the_word[], int must_char_pos, std::vector<int>& found_pos)
{

    int file_size = fs::file_size(word_file_path);

    for (int i = 0; i < file_size; i++)
    {
        if (buffer[i] == 32)
            continue;

        bool is_must_char_available = false;
        int j = i;

        for (; j < i + 5; j++)
        {
            if (!Is_the_char_available(buffer, j, characters_contains_in_the_word, must_char_pos, is_must_char_available))
            {
                i += 4;
                break;
            }
        }
        if (j >= i + 4)
        {

            if (is_must_char_available)
                found_pos.push_back(i);
        }
    }


}
bool Is_the_char_available(char* buffer, int pos, char char_contains_in_the_word[], int must_char_pos, bool& is_must_char_available)
{

    int char_pos = Binary_Search(char_contains_in_the_word, 0, total_char_in_the_word, buffer[pos]);

    if (char_pos != -1)
    {
        if (buffer[pos] == char_contains_in_the_word[must_char_pos]) // Must char is in the first Pos
        {
            is_must_char_available = true;
        }
        return true;
    }

    return false;
}
int Binary_Search(char char_contains_in_the_word[], int l, int r, char character_to_find)
{

    //std::cout << "ran for \n";
    if (r >= l)
    {

        int mid = l + ((r - l) / 2);

        if (char_contains_in_the_word[mid] == character_to_find)
            return mid;

        if (char_contains_in_the_word[mid] > character_to_find)
            return Binary_Search(char_contains_in_the_word, l, mid - 1, character_to_find);
        else
            return Binary_Search(char_contains_in_the_word, mid + 1, r, character_to_find);

    }

    return -1;
}

