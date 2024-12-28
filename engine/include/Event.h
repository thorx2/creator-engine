#pragma once

#define BIT_MASK(x) 1 << x

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

    enum class EventCategory
    {
        None = 0,
        InputEvent = BIT_MASK(1),
        WindowEvent = BIT_MASK(2),
        ApplicationEvent = BIT_MASK(3),
    };
    class Event
    {
    };
}