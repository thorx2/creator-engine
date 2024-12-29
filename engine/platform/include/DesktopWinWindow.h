#pragma once

#include "include/Window.h"

#include <windows.h>
#include <d3d11.h>

namespace Creator
{
    class DesktopWinWindow : public Window
    {
    public:
        DesktopWinWindow(const WindowParameters &props);
        ~DesktopWinWindow();

        void Update() override;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        bool IsOpen() const { return m_isOpen; }

    private:
        WindowParameters m_windowParameters;

        void InitWindow();
        void CleanUp();

        bool m_isOpen;

        inline static EventCallbackFn m_callback;

    public:
        inline void SetEventCallback(const EventCallbackFn &callback) override { DesktopWinWindow::m_callback = callback; }

        static LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

    private:
        bool InitDirectX();
        void Render();

        RECT m_rc;
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        LPCSTR m_applicationName;
        MSG m_Msg;

        class D3DContainer *m_Direct3D;
    };
}