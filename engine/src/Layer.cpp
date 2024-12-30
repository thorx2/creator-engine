
#include "pch.h"
#include "include/Layer.h"
#include "include/Application.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#if defined(DXD_RENDERING)
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#elif defined(OPEN_GL_RENDERING)
#include "include/Window.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#endif

namespace Creator
{
    void Layer::Attach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

        ImGui::StyleColorsDark();

        auto x = Application::Get();

        GLFWwindow *instance = static_cast<GLFWwindow *>(x.GetWindow()->GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(instance, true);

        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void Layer::Detach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}