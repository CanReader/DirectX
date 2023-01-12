#include "Exception.h"

Exception::Exception(int line, const char* file) : line(line), file(file){}

const char* Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();

	whatbuffer = oss.str();

	return whatbuffer.c_str();
}

const char* Exception::GetType() const noexcept
{
	return "Exception";
}

int Exception::GetLine() const noexcept
{
	return line;
}

std::string& Exception::GetFile() const noexcept
{
	return (std::string&)file;
}

std::string Exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl << "[Line] " << line;
	return oss.str();
}
