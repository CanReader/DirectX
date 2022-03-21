#ifndef MOUSEEVENT_H_
#define MOUSEEVENT_H_

#include "Event.h"

class MouseMoveEvent : public Event
{
public:
	MouseMoveEvent(float x, float y) : OffsetX(x), OffsetY(y) {}

	inline float GetX() const { return OffsetX; }
	inline float GetY() const { return OffsetY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Key moved: " << "( " << OffsetX << ", " << OffsetY << " repeats )";
		return ss.str();
	}
	
	EVENT_TYPE(MouseMoved)
	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
	float OffsetX, OffsetY;
};

class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xOffset, float yOffset) : OffsetX(xOffset),OffsetY(yOffset) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Key scrolled: " << "( " << OffsetX << ", " << OffsetY << " repeats )";
		return ss.str();
	}

	inline float GetXOffset() const {return OffsetX;}
	inline float GetYOffset() const {return OffsetY;}

	EVENT_TYPE(MouseScrolled)
	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
	float OffsetX, OffsetY;
};

class MouseButtonEvent : public Event
{
public:
	inline int GetMouseButton() const { return Button; }

	EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
	MouseButtonEvent(int button) : Button(button) {};

	int Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button):MouseButtonEvent(button) {}

	std::string ToString()
	{
		std::stringstream ss;
		ss << "Button " << this->Button << " is pressed";
		return ss.str();
	}
	
	EVENT_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button) :MouseButtonEvent(button) {}

	std::string ToString()
	{
		std::stringstream ss;
		ss << "Button " << this->Button << " is released";
		return ss.str();
	}

	EVENT_TYPE(MouseButtonReleased)

};

#endif