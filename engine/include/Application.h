#pragma once

#include <memory>

namespace Creator
{
    class Window;
    class Event;
    class WindowCloseEvent;
    class LayerManager;
    class Layer;

    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnInputCallback(Event &event);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

        Window *GetWindow()
        {
            return m_window;
        }

        static Application &Get() { return *s_Instance; }

    private:
        Window *m_window;
        bool m_Running;
        bool OnWindowClose(WindowCloseEvent &e);

        std::shared_ptr<LayerManager> m_LayerManager;

        float m_LastFrameTime;

        inline static Application *s_Instance;
    };

    Application *CreateApplication();
}