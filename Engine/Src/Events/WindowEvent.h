#ifndef WINDOWEVENT_H_
#define WINDOWEVENT_H_

#include "Event.h"

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height) : Width(width), Height(height) {}

	inline unsigned int GetWidth() const { return Width; }
	inline unsigned int GetHeight() const { return Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Window resized: " << "(" << Width << ", " << Height << ")";
		return ss.str();
	}

	EVENT_TYPE(WindowResize)
	EVENT_CATEGORY(EventCategoryWindow)
private:
	unsigned int Width, Height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() {}

	std::string ToString() const override
	{
		return std::string("Window closing...");
	}

	EVENT_TYPE(WindowClose)
	EVENT_CATEGORY(EventCategoryWindow)
};

class WindowTickEvent : public Event
{
public:
	WindowTickEvent() {}

	EVENT_TYPE(WindowUpdate)
	EVENT_CATEGORY(EventCategoryWindow)
};

class WindowUpdateEvent : public Event
{
public:
	WindowUpdateEvent() {}

	EVENT_TYPE(WindowUpdate)
	EVENT_CATEGORY(EventCategoryWindow)
};

class WindowRenderEvent : public Event
{
public:
	WindowRenderEvent() {}

	EVENT_TYPE(WindowRender)
		EVENT_CATEGORY(EventCategoryWindow)
};

#endif