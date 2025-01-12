#pragma once

#include"CoreMacros.h"

namespace Creator
{
    enum class EventType
    {
        None = 0,

        KeyDown,
        KeyUp,

        MouseBtnDown,
        MouseBtnUp,
        MouseMoved,

        WindowClose,
        WindowResize,

        FINAL
    };

    enum EventCategory
    {
        None = 0,
        InputEvent = BIT_MASK(1),
        KeyboardEvent = BIT_MASK(2),
        MouseEvent = BIT_MASK(3),
        WindowEvent = BIT_MASK(4),
        ApplicationEvent = BIT_MASK(5),
    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char *GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}