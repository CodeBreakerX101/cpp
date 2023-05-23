
#include "Files Operations.h"

bool FilesOperations::OpenFile(std::fstream& file, std::string& address, std::ios::openmode& openMode)
{

	file.open(address, openMode);

	if (file.is_open())
		return true;

	m_error_message = (std::string)__FUNCTION__ + "\n Unable to open : " + address + '\n';

	return false;
}

int FilesOperations::FileSize(std::fstream& file)
{

	int file_size = 0;

	file.seekg(0, std::ios::end);
	file_size = (int)file.tellg();
	file.seekg(0);

	return file_size;
}

bool FilesOperations::ReadDataFromFile(char* buffer, int buffer_size, std::fstream& inputFile)
{
	if (!inputFile.good())
	{
		m_error_message = (std::string)__FUNCTION__ + "\n Reading from a file failed\n";
		return false;
	}

	inputFile.read(buffer, buffer_size);

	return true;
}
bool FilesOperations::WriteDataIntoFile(std::fstream& outputFile, char* buffer, int buffer_size)
{
	if (!outputFile.good())
	{
		m_error_message = (std::string)__FUNCTION__ + "\n Writing into a file failed\n";
		return false;
	}

	for (int i = 0; i < buffer_size; i++)
	{
		outputFile << buffer[i];
	}

	return true;
}
bool FilesOperations::WriteDataIntoFileViaWordsIndex(std::fstream& outputFile, char* buffer,
	std::vector<int>& wordsIndex, int wordLength)
{

	if (!outputFile.good())
		return false;

	for (int i = 0; i < wordsIndex.size(); i++)
	{
		for (int j = wordsIndex[i]; j < wordsIndex[i] + wordLength; j++)
		{
			outputFile << buffer[j];
		}
		outputFile << ' ';
	}

	return true;

}

std::string FilesOperations::ErrorMessage()
{

	return m_error_message;
}

