#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include "Event.h"

class KeyEvent : public Event
{
public:
	inline int GetKeyCode() const { return keyCode; }

	EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryKeyboard)
protected:
	KeyEvent(int keycode):keyCode(keycode){}

	int keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keycode, int repeatcount) : KeyEvent(keycode), repeatCount(repeatcount) {};

	inline int GetRepeatCount() { return repeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Key pressed event: " << keyCode << "( " << repeatCount << " repeats )";
		return ss.str();
	}

	EVENT_TYPE(KeyPressed)

protected:
	int repeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keycode, int repeatcount) : KeyEvent(keycode){}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Key released : " << keyCode;
		return ss.str();
	}

	EVENT_TYPE(KeyReleased)


protected:
};

#endif // !KEYEVENT_H_

