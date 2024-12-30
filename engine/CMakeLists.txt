# Fetch spdlog using CMake's FetchContent
include(FetchContent)

# Create a library target
add_library(Engine STATIC
    pch.cpp
    src/Application.cpp
    src/Log.cpp
    src/Window.cpp
    src/Layer.cpp
    src/LayerManager.cpp
    platform/src/DesktopWinWindow.cpp
    platform/src/OpenGlWindow.cpp
    platform/directx/src/D3DContainer.cpp
    thirdparty/GLAD/src/glad.cpp
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_demo.cpp
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.0  # Use a stable version or the latest release
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)


# Specify include directories for the library
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Engine PRIVATE platform thirdparty/GLAD/include thirdparty/imgui thirdparty/imgui/backends)

# Enable precompiled headers
target_precompile_headers(Engine PRIVATE pch.h)

if(USE_DIRECTX)
target_sources(Engine
    thirdparty/imgui/backends/imgui_impl_dx11.cpp
)
target_link_libraries(Engine PRIVATE d3d11.lib dxgi.lib d3dcompiler.lib)
target_compile_definitions(Engine PRIVATE DXD_RENDERING)
elseif(USE_VULCAN)
target_sources(Engine STATIC
)
target_compile_definitions(Engine PRIVATE VULCAN_RENDERING)
else()
target_sources(Engine PRIVATE
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp
    thirdparty/imgui/backends/imgui_impl_glfw.cpp
)
target_compile_definitions(Engine PRIVATE OPEN_GL_RENDERING)
target_link_libraries(Engine PRIVATE glfw opengl32)
endif()

target_link_libraries(Engine PUBLIC spdlog::spdlog)