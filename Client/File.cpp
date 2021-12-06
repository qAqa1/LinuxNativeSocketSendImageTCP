#include "File.h"

#include <vector>
#include <algorithm>
//#include <iostream>

// для GetExecutableDir
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
// для GetExecutableDir

void File::ForeachByBuffer(std::ifstream& file, buffer_handler bufferHandler, long long bufferSize, long long fileLength)
{
	std::vector<char> buffer(bufferSize);

	if (fileLength == -1)
	{
		file.seekg(0, file.end);
		fileLength = file.tellg();
		file.seekg(0, file.beg);
	}

	long long readSize = 0;

	for (long long seekPos = 0; seekPos < fileLength; seekPos += readSize)
	{
		// поидее эта штука должна оптимизироваться компилятором до memset с нужными параметрами
		std::fill(begin(buffer), end(buffer), 0);

		file.seekg(seekPos);
		file.read(buffer.data(), bufferSize);

		readSize = file.gcount();
		bufferHandler(buffer.data(), readSize);

		//std::cout << "read_size = " << readSize << std::endl;
	}
}

void File::ForeachByBuffer(std::filesystem::path fileName, buffer_handler bufferHandler, long long bufferSize, long long fileLength)
{
	std::ifstream file(fileName, std::ifstream::binary);
	ForeachByBuffer(file, bufferHandler, bufferSize, fileLength);

	// Необязательно, деструктор потока закроет сам
	//file.close();
}

std::filesystem::path File::GetExecutableDir()
{
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) return "errno code: " + std::to_string(errno);

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
	return std::filesystem::path(cCurrentPath);
}
