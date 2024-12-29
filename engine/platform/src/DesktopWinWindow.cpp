#include "include/DesktopWinWindow.h"
#include <d3dcommon.h>
#include <Windows.h>
#include "directx/include/D3DContainer.h"

namespace Creator
{
    DesktopWinWindow::DesktopWinWindow(const WindowParameters &props) : m_isOpen(false), m_windowParameters(props), m_Direct3D(nullptr)
    {
        InitWindow();
        m_isOpen = true;
    }

    DesktopWinWindow::~DesktopWinWindow()
    {
        CleanUp();
    }

    void DesktopWinWindow::Update()
    {
        if (m_isOpen)
        {
            if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&m_Msg);
                DispatchMessage(&m_Msg);
            }

            if (m_Direct3D != nullptr)
            {
                // Clear the buffers to begin the scene.
                m_Direct3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

                // Present the rendered scene to the screen.
                m_Direct3D->EndScene();
            }
        }
    }

    uint32_t DesktopWinWindow::GetWidth() const
    {
        return m_windowParameters.Width;
    }

    uint32_t DesktopWinWindow::GetHeight() const
    {
        return m_windowParameters.Height;
    }

    void DesktopWinWindow::InitWindow()
    {
        ZeroMemory(&m_Msg, sizeof(MSG));

        WNDCLASSEX wc;
        DEVMODE dmScreenSettings;
        int posX, posY;

        m_hInstance = GetModuleHandle(NULL);

        m_applicationName = m_windowParameters.DisplayTitle.c_str();

        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = DesktopWinWindow::MessageHandler;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hIconSm = wc.hIcon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = m_applicationName;
        wc.cbSize = sizeof(WNDCLASSEX);

        RegisterClassEx(&wc);

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        if (m_windowParameters.Fullscreen)
        {
            memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
            dmScreenSettings.dmSize = sizeof(dmScreenSettings);
            dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
            dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
            dmScreenSettings.dmBitsPerPel = 32;
            dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
            ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
            posX = posY = 0;
        }
        else
        {
            screenWidth = m_windowParameters.Width;
            screenHeight = m_windowParameters.Height;

            // Place the window in the middle of the screen.
            posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
            posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
        }

        // Create the window with the screen settings and get the handle to it.
        m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
                                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
                                posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

        // Bring the window up on the screen and set it as main focus.
        ShowWindow(m_hWnd, SW_SHOW);
        SetForegroundWindow(m_hWnd);
        SetFocus(m_hWnd);

        ShowCursor(true);

        m_Direct3D = new D3DContainer();
        m_Direct3D->Initialize(m_windowParameters.Width, m_windowParameters.Height, false, m_hWnd, false, 1000.f, 0.1f);
    }

    void DesktopWinWindow::CleanUp()
    {
        // Show the mouse cursor.
        ShowCursor(true);

        // Fix the display settings if leaving full screen mode.
        bool FULL_SCREEN = false;
        if (FULL_SCREEN)
        {
            ChangeDisplaySettings(NULL, 0);
        }

        // Remove the window.
        DestroyWindow(m_hWnd);
        m_hWnd = NULL;

        // Remove the application instance.
        UnregisterClass(m_applicationName, m_hInstance);
        m_hInstance = NULL;

        // Release the pointer to this class.
        // ApplicationHandle = NULL;

        if (m_Direct3D != nullptr)
        {
            m_Direct3D->Shutdown();
            delete m_Direct3D;
            m_Direct3D = nullptr;
        }

        return;
    }

    bool DesktopWinWindow::InitDirectX()
    {
        return true;
    }

    LRESULT CALLBACK DesktopWinWindow::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        switch (umsg)
        {
        case WM_KEYDOWN:
        {
            KeyboardKeyDown keyDown((unsigned int)wparam);
            DesktopWinWindow::m_callback(keyDown);
            return 0;
        }

        case WM_CLOSE:
        {
            WindowCloseEvent closeEvent;
            DesktopWinWindow::m_callback(closeEvent);
            return 0;
        }

        case WM_KEYUP:
        {
            KeyboardKeyUp keyUp((unsigned int)wparam);
            DesktopWinWindow::m_callback(keyUp);
            return 0;
        }

        default:
        {
            return DefWindowProc(hwnd, umsg, wparam, lparam);
        }
        }
    }
}