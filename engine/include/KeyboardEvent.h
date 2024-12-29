#pragma once

#include <sstream>
#include "Event.h"
#include "KeyCode.h"

namespace Creator
{
    class KeyboardEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategory::KeyboardEvent | EventCategory::InputEvent)
    protected:
        KeyboardEvent(const KeyCode keycode)
            : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class KeyboardKeyDown : public KeyboardEvent
    {
    public:
        KeyboardKeyDown(const KeyCode keycode, bool isRepeat = false)
            : KeyboardEvent(keycode), m_IsRepeat(isRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyDown)
    private:
        bool m_IsRepeat;
    };

    class KeyboardKeyUp : public KeyboardEvent
    {
    public:
        KeyboardKeyUp(const KeyCode keycode)
            : KeyboardEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyUp)
    };
}