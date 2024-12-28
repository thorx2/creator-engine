#include "pch.h"
#include "include/OpenGlWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Creator
{
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
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
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