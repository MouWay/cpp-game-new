#include "ExceptionExtension.h"
#include <sstream>


ExceptionExtension::ExceptionExtension(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ExceptionExtension::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ExceptionExtension::GetType() const noexcept
{
	return "Exception";
}

int ExceptionExtension::GetLine() const noexcept
{
	return line;
}

const std::string& ExceptionExtension::GetFile() const noexcept
{
	return file;
}

std::string ExceptionExtension::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}