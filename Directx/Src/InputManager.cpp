#include "InputManager.h"

InputManager::InputManager()
{
	for (int i = 0; i < 256; i++)
		Keys[i] = false;
}

InputManager::InputManager(const InputManager&)
{
	for (int i = 0; i < 256; i++)
		Keys[i] = false;
}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
}

void InputManager::KeyDown(unsigned int keycode)
{
	Keys[keycode] = true;
	PressedKey = keycode;
	if (keycode >= 65 && keycode <= 90)
		IsChar = true;
}

void InputManager::KeyUp(unsigned int keycode)
{
	Keys[keycode] = false;
	PressedKey = -1;
	IsChar = false;
}

bool InputManager::IsKeyDown(unsigned int keycode)
{
	return Keys[keycode];
}

bool InputManager::IsCharDown()
{
	return IsChar;
}

int InputManager::GetNum()
{
	int result = PressedKey - 48;

	if (result < 0 || result > 10 || PressedKey == -1)
		result = -1;

	return result;
}
