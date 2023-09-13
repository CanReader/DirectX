#include <exception>
#include <string>
#include <sstream>

#define WND_EXCEPT(hr) CoreWindow::Exception(__LINE__,__FILE__,hr)
#define EXCEPT() BaseException(__LINE__,__FILE__)

class BaseException : public std::exception
{
public:
	BaseException(){}
	BaseException(int line, const char* file);

	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

protected:
	mutable std::string whatbuffer;
	int line;
	std::string file;

private:
};

