#pragma once

#include "include/Layer.h"

namespace OverWorld
{
    class Creator::CreatorTime;
    class Creator::Event;

    class DebugUiLayer : public Creator::Layer
    {
    public:
        DebugUiLayer();
        ~DebugUiLayer();

        void Update(Creator::CreatorTimer time) override;
        void OnEvent(Creator::Event &event) override;

        void Detach() override;
    };
}