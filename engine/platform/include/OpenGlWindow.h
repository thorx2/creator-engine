#pragma once

#include "include/Window.h"

class GLFWwindow;
namespace Creator
{
    class OpenGlWindow : public Window
    {
    public:
        OpenGlWindow(const WindowParameters &props);
        ~OpenGlWindow();

        void Update() override;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        bool IsOpen() const;

        inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.CallbackFunction = callback; }

        void *GetNativeWindow() override { return m_window; }

    private:
        WindowParameters m_windowParameters;

        void InitWindow();
        void CleanUp();

        GLFWwindow *m_window;

        bool m_isOpen;

        struct OpenGLMetaData
        {
            std::string Title;
            EventCallbackFn CallbackFunction;

            OpenGLMetaData() : Title(""), CallbackFunction(nullptr) {}
        };

        OpenGLMetaData m_Data;
    };
}