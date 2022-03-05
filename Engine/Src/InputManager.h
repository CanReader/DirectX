#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_


class InputManager
{
public:
	InputManager();
	InputManager(const InputManager&);
	~InputManager();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);
	bool IsCharDown();

	int GetNum();

private:
	bool Keys[256];
	bool IsChar;

	int PressedKey;
};


#endif // !INPUTMANAGER_H_