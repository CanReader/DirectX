#include "CoreWindow.h"

CoreWindow::CoreWindow(HINSTANCE hInstance) : graph{ std::make_unique<Graphics>() } { this->hInstance = hInstance; }

CoreWindow::~CoreWindow()
{
}

void CoreWindow::SetFullScreen(bool fullscreen)
{
	DEVMODE dmScreenSettings;
	int posX, posY;

	if (fullscreen)
	{
		memset(&dmScreenSettings, 0, sizeof(DEVMODE));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = this->Siz.Width;
		dmScreenSettings.dmPelsHeight = this->Siz.Height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		this->Loc.X = 0;
		this->Loc.Y = 0;

	}
	else
	{
		this->Loc.X = (GetSystemMetrics(SM_CXSCREEN) - this->Siz.Width) / 2;
		this->Loc.Y = (GetSystemMetrics(SM_CYSCREEN) - this->Siz.Height) / 2;
	}
		graph->SetFullscreen(fullscreen);
		Windowed = !fullscreen;
}

HWND CoreWindow::GetHWND()
{ 
	return hWnd;
}

HINSTANCE CoreWindow::GetHinstance()
{
	return hInstance;
}

WNDCLASSEX CoreWindow::CreateWindowClass(LPCSTR ClassName,LPCSTR MenuName)
{
	WNDCLASSEX wnd;
	ZeroMemory(&wnd,sizeof(WNDCLASSEX));
	wnd.cbClsExtra = NULL;
	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.cbWndExtra = NULL;
	wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wnd.hCursor = LoadCursor(hInstance,IDC_ARROW);
	wnd.hIcon = static_cast<HICON>(LoadImage(hInstance,MAKEINTRESOURCE(IDI_ICON1),IMAGE_ICON,32,32,0));
	wnd.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = ClassName;
	wnd.style = CS_VREDRAW | CS_HREDRAW;

	this->ClassName = ClassName;

	RegisterClassEx(&wnd);

	return wnd;
}

bool CoreWindow::InitializeWindow(LPCSTR WindowName,int Width,int Height)
{
	Messanger::Log::Initialize();

	CoreWindow::WindowHandle = this;
	this->WindowName = WindowName;

	CreateWindowClass(WindowName,NULL);

	RECT rect = {0,0,Width,Height};
	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,NULL,NULL);

	hWnd = CreateWindowEx(WS_EX_APPWINDOW,
		this->ClassName,
		this->WindowName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)return false;

	if (!graph->Initialize(hWnd, Width, Height,!this->Windowed))
		return false;

	DX_INFO("Graphic class initialized");

	SetFullScreen(false);

	this->DisplayWindow(true);

	return true;
}

void CoreWindow::DisplayWindow(bool Show)
{
	if(Show)ShowWindow(hWnd,SW_SHOW);
	else
	{
#pragma warning(disable:4996)

		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		char NowText[9] = "        ";

	ShowWindow(hWnd, SW_HIDE);
	}

	UpdateWindow(hWnd);

	this->Visible = Show;
}

void CoreWindow::ProcessMessages()
{
	ZeroMemory(&Messanger,sizeof(MSG));

	while(Messanger.message != WM_QUIT)
	{
		if (PeekMessage(&Messanger, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Messanger);
			DispatchMessage(&Messanger);
			
			if (Messanger.message == WM_QUIT)
				break;
		}

	}
		ReturnValue = Messanger.wParam;
}

void CoreWindow::DestroyWindow()
{
	hWnd = NULL;
	hInstance = NULL;
	Visible = false;

	graph->Shutdown();

	PostQuitMessage(0);
}

bool CoreWindow::isinShow()
{
	return Visible;
}

void CoreWindow::SetWindowTitle(const LPSTR& text)
{
	SetWindowText(hWnd,text);
}

void CoreWindow::SetLocation(int X, int Y)
{
	this->Loc.X = X;
	this->Loc.Y = Y;

	MoveWindow(hWnd, X, Y, Siz.Width, Siz.Height, false);
}

RECT CoreWindow::GetLocation()
{
	RECT rect;
	rect.left = this->Loc.X;
	rect.top = this->Loc.Y;

	return rect;
}

LRESULT CALLBACK CoreWindow::WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
	{
		CoreWindow::WindowHandle->graph->Render();
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	default:DefWindowProc(hWnd, Message, wParam, lParam); 
	}
}
