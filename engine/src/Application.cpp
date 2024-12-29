#include "pch.h"

#include "include/Application.h"
#include "include/Window.h"

namespace Creator
{
    Application::Application() : m_Running(true)
    {
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(std::bind(&Application::OnInputCallback, this, std::placeholders::_1));
    }

    Application::~Application() {}

    void Application::Run()
    {
        while (m_Running && m_window != nullptr)
        {
            m_window->Update();
        }
    }

    void Application::OnInputCallback(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}