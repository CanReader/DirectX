#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <functional>
#include <sstream>

enum class EventType
{
	None = 0,
	WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
	WindowTick, WindowUpdate, WindowRender,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryWindow,
	EventCategoryInput,
	EventCategoryKeyboard,
	EventCategoryMouse,
	EventCategoryMouseButton,
};

#define EVENT_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
                                  virtual EventType GetType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

class __declspec(dllexport) Event 
{
	friend class EventDispatcher;

public:
	 virtual EventType GetType() const = 0;
	 virtual const char* GetName() const = 0;
	 virtual int GetCategoryFlags() const = 0;
	 virtual std::string ToString() const { return GetName(); }

	 inline bool IsInCategory(EventCategory category)
	 {
		 return GetCategoryFlags() & category;
	 }
protected:
	bool handled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_Event(event){}

	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.Handled |= func(static_cast<T&>(m_Event));
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

#endif // !EVENT_H_


