#include <iostream>

#include "CoreWindow.h"
#include "Log.h"

using namespace std;

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,int nCmdShow) 
// If a error happens, make this line comment and use main() function instead of WinMain
//int main()                                                                                    //Error occurs because you have not required library or header. WinMain function is better optimized than main                                                                                                 () function. it is better to use WinMain but using main() is not imposibble either
{
	Messanger::Log::Initialize();

	int ReturnValue = 0;

	CoreWindow* Window = new CoreWindow();
	if (Window->InitializeWindow("DirectX App",1920,1080))
	{
		DX_INFO("The window had been successfully initialized!");

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