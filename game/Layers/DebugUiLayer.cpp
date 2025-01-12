#include "pch.h"

#include "include/CoreMacros.h"
#include "DebugUiLayer.h"
#include "include/Event.h"
#include "include/time/CreatorTime.h"
#include "include/Application.h"
#include "include/Window.h"
#include "imgui.h"
#include "imgui_internal.h"

#if defined(DXD_RENDERING)
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#elif defined(OPEN_GL_RENDERING)
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

namespace OverWorld
{
    DebugUiLayer::DebugUiLayer() : Creator::Layer("DebugUI")
    {
    }

    DebugUiLayer::~DebugUiLayer()
    {
    }

    void DebugUiLayer::Update(Creator::CreatorTimer time)
    {
        Creator::Application app = Creator::Application::Get();

        __IM_GUI_FRAME_INIT__

        ImGuiIO &io = ImGui::GetIO();
        int windowWidth = app.GetWindow()->GetWidth();
        int windowHeight = app.GetWindow()->GetHeight();
        io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

        ImGui::NewFrame();

        // Custom frame stuff
        static bool show_demo_window = false;
        static bool show_another_window = false;
        static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
        // End custom frame stuff
    }

    void DebugUiLayer::OnEvent(Creator::Event &event)
    {
    }

    void DebugUiLayer::Detach()
    {
    }
}