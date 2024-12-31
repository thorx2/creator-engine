
#include "pch.h"
#include "include/Layer.h"
#include "include/Application.h"
#include "include/Window.h"

#if defined(DXD_RENDERING)
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "include/DesktopWinWindow.h"
#include "platform/directx/include/D3DContainer.h"
#include <d3dcommon.h>
#elif defined(OPEN_GL_RENDERING)
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#endif

namespace Creator
{
    void Layer::Attach()
    {
        Application app = Application::Get();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        ImGui::StyleColorsDark();

#if defined(DXD_RENDERING)
        DesktopWinWindow *winInstance = static_cast<DesktopWinWindow *>(app.GetWindow());
        auto dxcontainer = winInstance->GetD3DContainer().lock();
        auto hwnd = static_cast<HWND*>(winInstance->GetNativeWindow());
        ImGui_ImplWin32_Init(&hwnd);
        ImGui_ImplDX11_Init(dxcontainer->GetDevice(), dxcontainer->GetDeviceContext());
#elif defined(OPEN_GL_RENDERING)
        GLFWwindow *instance = static_cast<GLFWwindow *>(app.GetWindow()->GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(instance, true);

        ImGui_ImplOpenGL3_Init("#version 130");
#endif
    }

    void Layer::Detach()
    {
#if defined(DXD_RENDERING)
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
#elif defined(OPEN_GL_RENDERING)
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
#endif
        ImGui::DestroyContext();
    }
}