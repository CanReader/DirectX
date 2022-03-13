#ifndef GENERALINPUT_H_
#define GENERALINPUT_H_

#include <dinput.h>
#include <iostream>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class InputClass
{
public:
	bool InitDevices(HWND hWnd,HINSTANCE hInstance);

	bool IsPressed(int KeyCode);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	void EnumurateDevices();

	IDirectInput8* DInput;
	IDirectInputDevice8* KeyboardDevice;
	IDirectInputDevice8* MouseDevice;

	unsigned char KeyboardState[256];
	DIMOUSESTATE LastMouseState;
	LPDIRECTINPUT LDInput;

	int MouseX, MouseY;
};


#endif //