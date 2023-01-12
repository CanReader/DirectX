#include "Exception.h"

BaseException::BaseException(int line, const char* file) : line(line), file(file){}

const char* BaseException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();

	whatbuffer = oss.str();

	return whatbuffer.c_str();
}

const char* BaseException::GetType() const noexcept
{
	return "Exception";
}

int BaseException::GetLine() const noexcept
{
	return line;
}

std::string& BaseException::GetFile() const noexcept
{
	return (std::string&)file;
}

std::string BaseException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl << "[Line] " << line;
	return oss.str();
}
