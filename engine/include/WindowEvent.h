#pragma once

#include "Event.h"

namespace Creator
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(ApplicationEvent)
    };

}