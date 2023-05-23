#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Custom Algorithms.h"

namespace fs = std::filesystem;

class FilesOperations : CustomAlgorithms
{
private:

	std::string m_error_message = "Files Operation::";

public:

	bool OpenFile(std::fstream& file, std::string& address, std::ios::openmode& openMode);

	int  FileSize(std::fstream& file);

	bool ReadDataFromFile(char* buffer, int buffer_size, std::fstream& wordle_file);

	bool WriteDataIntoFile(std::fstream& outputFile, char* buffer, int buffer_size);

	bool WriteDataIntoFileViaWordsIndex(std::fstream& outputFile, char* buffer, std::vector<int>& wordsIndex,
		int wordLength);

	std::string ErrorMessage();	


};