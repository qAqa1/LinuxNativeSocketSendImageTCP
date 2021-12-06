#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <string.h>

#ifdef _WIN32
// ��������, �������� ���� ����� ��������� windows
std::string ErrorCodeToString(int errnoCode) { return "Unknow platform"; };
#else
#define ErrorCodeToString strerror
#endif

namespace CustomException
{
	// ������� std::runtime_error, �� ������� ������ ��� � � �������
	class RuntimeError : public std::runtime_error
	{
	public:
		RuntimeError() : runtime_error("Unexpected error")
		{
			std::cout << std::endl << "Unexpected error" << std::endl;
		};

		RuntimeError(std::string message) : runtime_error(message.c_str())
		{
			std::cout << std::endl << message << std::endl;
		};
	};

	// ������� std::runtime_error, �� ������� ������ ��� � � ������� ������ � ��������� ������ ������������ �������
	class RuntimeErrorCode : public std::runtime_error
	{
	public:
		RuntimeErrorCode() : runtime_error(("Unexpected error: " + std::string(ErrorCodeToString(errno))).c_str())
		{
			std::cout << std::endl << "Unexpected error: " << std::string(ErrorCodeToString(errno)) << std::endl;
		};

		RuntimeErrorCode(std::string message) : runtime_error((message + ": " + std::string(ErrorCodeToString(errno))).c_str())
		{
			std::cout << std::endl << message << ": " << std::string(ErrorCodeToString(errno)) << std::endl;
		};
	};
}
