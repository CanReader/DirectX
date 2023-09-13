#include "CoreApp/CoreWindow.h"

using namespace std;

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,int nCmdShow)
{
	int ReturnValue = 0;

	CoreWindow* Window = new CoreWindow(hInstance);
	if (Window->InitializeWindow("DirectX App",1920,1080))
	{

		Window->ProcessMessages();
		ReturnValue = Window->ReturnValue;
	}
	else
		MessageBox(NULL,"Failed to create window!","ERROR",MB_OK | MB_ICONERROR);

	Window->DestroyWindow();
	delete Window;
	Window = 0;

	return ReturnValue;
}
