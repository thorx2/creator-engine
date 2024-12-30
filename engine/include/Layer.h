#pragma once

#include <string>
#include "include/time/CreatorTime.h"
#include "include/Event.h"

namespace Creator
{
    class Layer
    {
    public:
        Layer(const std::string displayName = "Layer") : m_DisplayName(displayName) {}
        virtual ~Layer() {}
        virtual void Attach() {}
        virtual void Detach() {}
        virtual void Update(CreatorTime time) {}
        virtual void OnUiRender() {}
        virtual void OnEvent(Event &event) {}

        const std::string &GetDisplayName() const { return m_DisplayName; }

    private:
        std::string m_DisplayName;
    };
}