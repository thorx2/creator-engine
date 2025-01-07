#pragma once

#define BIT_MASK(x) 1 << x

#if defined(DXD_RENDERING)
#define GET_PROCESS_TIME 0.f
#define __IM_GUI_FRAME_INIT__   \
    ImGui_ImplWin32_NewFrame(); \
    ImGui_ImplDX11_NewFrame();
#elif defined(VULCAN_RENDERING)
#elif defined(OPEN_GL_RENDERING)
#define GET_PROCESS_TIME glfwGetTime()
#define __IM_GUI_FRAME_INIT__     \
    ImGui_ImplOpenGL3_NewFrame(); \
    ImGui_ImplGlfw_NewFrame();
#endif