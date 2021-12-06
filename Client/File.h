#pragma once

#include <filesystem>
#include <fstream>
#include <functional>

#define DEFAUL_BUFFER_SIZE_FOR_ITERATING_FILE 10240

namespace File
{
	using buffer_handler = std::function<void(char*, long long)>;

	void ForeachByBuffer(std::ifstream& file, buffer_handler bufferHandler, long long bufferSize = DEFAUL_BUFFER_SIZE_FOR_ITERATING_FILE, long long fileLength = -1);
	void ForeachByBuffer(std::filesystem::path fileName, buffer_handler bufferHandler, long long bufferSize = DEFAUL_BUFFER_SIZE_FOR_ITERATING_FILE, long long fileLength = -1);

	std::filesystem::path GetExecutableDir();
}
