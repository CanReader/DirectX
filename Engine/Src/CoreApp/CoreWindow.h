#ifndef COREWINDOW_H_ 
#define COREWINDOW_H_
#define WIN32_LEAN_AND_MEAN

#define DEFAULT_LOCATION 0

#include <Windows.h>
#include <iostream>
#include <memory>
#include <sstream>

#include "../../../Client/resource.h"

#include "Direct11.h"
#include "Graphics.h"
#include "../Debugging/Log.h"
#include "../Debugging/Debugger.h"
#include "../Debugging/BaseException.h"

std::shared_ptr<spdlog::logger> Messanger::Log::m_Logger;


typedef struct Location
{
	int X;
	int Y;
};

typedef struct Size
{
	int Width;
	int Height;
};

class DLL_API CoreWindow
{
public:
	CoreWindow(HINSTANCE hInstance);
	 ~CoreWindow();

	//Variables
private:
	Location Loc;
	Size Siz;

	bool Visible;
	bool Windowed = true;

	LPCSTR ClassName;
	LPCSTR WindowName;

	HMENU Menu;

	MSG Messanger;

	HWND hWnd;
	HINSTANCE hInstance;
public:
	int ReturnValue = 0;

public:
	bool InitializeWindow(LPCSTR WindowName, int Width, int Height);
	void DisplayWindow(bool Show);
	void ProcessMessages();
	void DestroyWindow();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	bool isinShow();

	void SetWindowTitle(const LPSTR&);
	void SetLocation(int X, int Y);
	RECT GetLocation();
	void SetSize(int Width,int Height);
	RECT GetSize();
	void SetFullScreen(bool);


	HWND GetHWND();
	HINSTANCE GetHinstance();

private:
	WNDCLASSEX CreateWindowClass(LPCSTR ClassName, LPCSTR MenuName);

	inline static CoreWindow* WindowHandle;

public:
	std::unique_ptr<Graphics> graph;

	class Exception : public BaseException
	{
	public:
		Exception() {}
		Exception(int line, const char* file, HRESULT hr)
		{
				this->line = line;
				this->file = file;
				this->hr = hr;
		}
			
		const char* what() const noexcept override
		{
			std::ostringstream oss;

			oss << GetType() << std::endl 
				<< "[Error Code]: " << GetErrorCode() << std::endl
				<< "[Description]: " << GetErrorString() << std::endl
				<< GetOriginString();

			whatbuffer = oss.str();
			return whatbuffer.c_str();
		}

		virtual const char* GetType() const noexcept
		{
			return "Window Exception";
		}

		static std::string TranslateErrorCode(HRESULT hr)
		{
			char* pMsgBuf = nullptr;
			DWORD nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,nullptr,hr,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);

			if (nMsgLen == 0)
				return "Unidentified error code";

			std::string	ErrorString = pMsgBuf;
			LocalFree(pMsgBuf);
			return ErrorString;
		}

		HRESULT GetErrorCode() const noexcept
		{
			return hr;
		}

		std::string GetErrorString() const
		{
			return TranslateErrorCode(hr);
		}

	private:
		HRESULT hr;
	};
};

#endif
