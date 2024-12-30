#include "pch.h"

#include "include/Application.h"
#include "include/Window.h"
#include "include/WindowEvent.h"
#include "include/EventDispatcher.h"
#include "include/Layer.h"
#include "include/LayerManager.h"

namespace Creator
{
    Application::Application() : m_Running(true), m_LastFrameTime(0)
    {
        s_Instance = this;
        m_LayerManager = std::make_unique<LayerManager>();
        m_window = Window::Create();
        m_window->SetEventCallback(std::bind(&Application::OnInputCallback, this, std::placeholders::_1));
    }

    Application::~Application() {}

    void Application::Run()
    {
        while (m_Running && m_window != nullptr)
        {
            m_LayerManager->Update();
            m_window->Update();
        }
    }

    void Application::OnInputCallback(Event &event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

        m_LayerManager->OnEvent(event);
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerManager->PushLayer(layer);
        layer->Attach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerManager->PushToTop(layer);
        layer->Attach();
    }
}