#include "pch.h"
#include "include/Window.h"

#if defined(OPEN_GL_RENDERING)
#include "include/OpenGlWindow.h"
#elif defined(DXD_RENDERING)
#include "include/DesktopWinWindow.h"
#endif

namespace Creator
{
    Window *Window::Create(const WindowParameters &props)
    {
#if defined(OPEN_GL_RENDERING)
        return new OpenGlWindow(props);
#elif defined(DXD_RENDERING)
        return new DesktopWinWindow(props);
#endif
    }
}