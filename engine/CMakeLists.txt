# Fetch spdlog using CMake's FetchContent
include(FetchContent)

# Create a library target
add_library(Engine STATIC
    pch.cpp
    src/Application.cpp
    src/Log.cpp
    src/Window.cpp
    platform/src/DesktopWinWindow.cpp
    platform/src/OpenGlWindow.cpp
    platform/directx/src/D3DContainer.cpp
    thirdparty/GLAD/src/glad.cpp
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.0  # Use a stable version or the latest release
)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# add_subdirectory(thirdparty/glfw34)

# Make spdlog available
FetchContent_MakeAvailable(spdlog)


# Specify include directories for the library
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} thirdparty/glfw34/include)
target_include_directories(Engine PRIVATE thirdparty/GLAD/include platform)

# Enable precompiled headers
target_precompile_headers(Engine PRIVATE pch.h)

if(USE_DIRECTX)
target_link_libraries(Engine PRIVATE d3d11.lib dxgi.lib d3dcompiler.lib)
else()
target_compile_definitions(Engine PRIVATE OPEN_GL)
target_link_libraries(Engine PRIVATE glfw opengl32)
endif()

# target_link_libraries(Engine PRIVATE glfw opengl32 d3d11.lib dxgi.lib d3dcompiler.lib)
target_link_libraries(Engine PUBLIC spdlog::spdlog)