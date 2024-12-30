#pragma once

#include "Event.h"
#include <string>

namespace Creator
{
    struct WindowParameters
    {
        std::string DisplayTitle;
        uint32_t Width;
        uint32_t Height;
        bool Fullscreen;
        bool VSyncEnabled;
        WindowParameters(const std::string &title = "Base Window",
                         uint32_t width = 1600,
                         uint32_t height = 900,
                         bool fullscreen = false,
                         bool vSyncEnabled = false)
            : DisplayTitle(title), Width(width), Height(height), Fullscreen(fullscreen), VSyncEnabled(vSyncEnabled) {}
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void Update() = 0;

        virtual bool IsOpen() const = 0;
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        static Window *Create(const WindowParameters &props = WindowParameters());

        virtual void *GetNativeWindow() { return this; }
    };

}
