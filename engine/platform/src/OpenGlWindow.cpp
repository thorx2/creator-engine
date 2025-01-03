#include "pch.h"

#if defined(OPEN_GL_RENDERING)
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "include/OpenGlWindow.h"
#include "include/Event.h"
#include "include/WindowEvent.h"
#include "include/KeyboardEvent.h"

namespace Creator
{
    ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);

    OpenGlWindow::OpenGlWindow(const WindowParameters &props) : m_window(nullptr), m_windowParameters(props), m_isOpen(false)
    {
        InitWindow();
    }

    OpenGlWindow::~OpenGlWindow()
    {
        CleanUp();
    }

    void OpenGlWindow::Update()
    {
        while (m_window != nullptr && !glfwWindowShouldClose(m_window))
        {
            glfwPollEvents();

            ImGui::Render();
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_window);
            return;
        }

        m_isOpen = false;
    }

    uint32_t OpenGlWindow::GetWidth() const
    {
        return m_windowParameters.Width;
    }

    uint32_t OpenGlWindow::GetHeight() const
    {
        return m_windowParameters.Height;
    }

    bool OpenGlWindow::IsOpen() const
    {
        return false;
    }

    void OpenGlWindow::InitWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_windowParameters.Width, m_windowParameters.Height, m_windowParameters.DisplayTitle.c_str(), NULL, NULL);
        if (m_window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);
        if (m_windowParameters.VSyncEnabled)
        {
            glfwSwapInterval(1);
        }
        glfwSetWindowUserPointer(m_window, &m_Data);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            if (m_window)
            {
                CleanUp();
            }
            return;
        }
        m_isOpen = true;

        glfwSetKeyCallback(m_window,
                           [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                               switch (action)
                               {
                               case GLFW_PRESS:
                               {
                                   KeyboardKeyDown keyDown(key);
                                   OpenGLMetaData &openWin = *(OpenGLMetaData *)(glfwGetWindowUserPointer(window));
                                   openWin.CallbackFunction(keyDown);
                               }
                               break;
                               case GLFW_RELEASE:
                               {
                                   KeyboardKeyUp keyUp(key);
                               }
                               break;
                               }
                           });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window)
                                   {
            OpenGLMetaData& data = *(OpenGLMetaData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent eve;
            data.CallbackFunction(eve); });
    }

    void OpenGlWindow::CleanUp()
    {
        if (m_window != nullptr)
        {
            glfwDestroyWindow(m_window);
            glfwTerminate(); // Do I need to???
        }
        m_window = nullptr;
    }
}

#endif
