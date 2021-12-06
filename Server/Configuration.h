#pragma once

//#include <string>
#include <filesystem>

namespace Configuration
{
	int Port();
	std::string IpAddress();
	std::filesystem::path FilePath();
}
