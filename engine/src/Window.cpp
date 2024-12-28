#include "pch.h"
#include "include/Window.h"

#if defined(OPEN_GL)
#include "include/OpenGlWindow.h"
#else
#include "include/DesktopWinWindow.h"
#endif

namespace Creator
{
    Window *Window::Create(const WindowParameters &props)
    {
#if defined(OPEN_GL)
        return new OpenGlWindow(props);
#else
        return new DesktopWinWindow(props);
#endif
    }
}