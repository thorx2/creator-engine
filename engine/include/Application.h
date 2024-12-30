#pragma once

#include <memory>

namespace Creator
{
    class Window;
    class Event;
    class WindowCloseEvent;

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnInputCallback(Event &event);

    private:
        std::unique_ptr<Window> m_window;
        bool m_Running;
        bool OnWindowClose(WindowCloseEvent &e);
    };

    Application *CreateApplication();
}