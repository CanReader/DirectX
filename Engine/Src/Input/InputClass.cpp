#include "InputClass.h"

bool InputClass::InitDevices(HWND hWnd,HINSTANCE hInstance)
{
    HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,(void**)&DInput,NULL);

    if (FAILED(hr))
        return false;

    hr = DInput->CreateDevice(GUID_SysKeyboard,&KeyboardDevice,NULL);

    if (FAILED(hr))
        return false;

    hr = KeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

    if (FAILED(hr))
        return false;

    hr = KeyboardDevice->SetCooperativeLevel(hWnd,DISCL_FOREGROUND | DISCL_EXCLUSIVE);

    if (FAILED(hr))
        return false;

    hr = DInput->CreateDevice(GUID_SysMouse, &MouseDevice, NULL);

    if (FAILED(hr))
        return false;

    hr = MouseDevice->SetDataFormat(&c_dfDIMouse);

    if (FAILED(hr))
        return false;

    hr = MouseDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

    if (FAILED(hr))
        return false;

    return true;
}

bool InputClass::ReadKeyboard()
{
    HRESULT result;


    // Read the keyboard device.
    result = KeyboardDevice->GetDeviceState(sizeof(KeyboardState), (LPVOID)&KeyboardState);
    if (FAILED(result))
    {
        // If the keyboard lost focus or was not acquired then try to get control back.
        if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
        {
            KeyboardDevice->Acquire();
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool InputClass::IsPressed(int KeyCode)
{
    if (!ReadKeyboard())
        return false;

    if (KeyboardState[KeyCode] & 0x80)
        return true;
}
