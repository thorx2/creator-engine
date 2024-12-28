#pragma once

#include <memory>
namespace Creator
{
    class Window;

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

    private:
        std::unique_ptr<Window> m_window;
        bool m_Running;
    };

    Application *CreateApplication();
}