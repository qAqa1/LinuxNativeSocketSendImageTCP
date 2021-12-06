#include "Configuration.h"

int Configuration::Port()
{
	return 1226;
}

std::string Configuration::IpAddress()
{
	return "127.0.0.1";
}

std::filesystem::path Configuration::FilePath()
{
	return std::filesystem::path("/mnt/c/send_test_dir/receive.jpg");
}
