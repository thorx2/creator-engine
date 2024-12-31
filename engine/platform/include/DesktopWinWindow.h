#pragma once

#include "include/Window.h"
#include <memory>

// TODO Hide this only for windows
#include <windows.h>

namespace Creator
{
    // Forward declarations
    // struct RECT;
    // typedef void *HWND;
    // typedef void *HINSTANCE;
    // typedef const char *LPCSTR;
    // struct MSG;
    // typedef long LRESULT;

    class D3DContainer;

    class DesktopWinWindow : public Window
    {
    public:
        DesktopWinWindow(const WindowParameters &props);
        ~DesktopWinWindow();

        void Update() override;

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        bool IsOpen() const { return m_isOpen; }

        void *GetNativeWindow() override { return &m_hWnd; }

    private:
        WindowParameters m_windowParameters;

        void InitWindow();
        void CleanUp();

        bool m_isOpen;

        inline static EventCallbackFn m_callback;

    public:
        inline void SetEventCallback(const EventCallbackFn &callback) override { DesktopWinWindow::m_callback = callback; }
        static LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

        std::weak_ptr<D3DContainer> GetD3DContainer() { return std::weak_ptr<D3DContainer>(m_Direct3D); }

    private:
        bool InitDirectX();

        RECT m_rc;
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        LPCSTR m_applicationName;
        MSG m_Msg;

        std::shared_ptr<D3DContainer> m_Direct3D;
    };
}