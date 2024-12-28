#include "pch.h"

#include "include/Application.h"
#include "include/Window.h"

namespace Creator
{
    Application::Application() : m_Running(true)
    {
        m_window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application() {}

    void Application::Run()
    {
        while (m_Running && m_window != nullptr)
        {
            m_window->Update();
        }
    }
}