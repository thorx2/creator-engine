# Create an executable target
add_executable(Game
    GameApplication.cpp
    Layers/DebugUiLayer.cpp
)

# Link the engine library
target_link_libraries(Game PRIVATE Engine)

if(USE_DIRECTX)
target_compile_definitions(Game PRIVATE DXD_RENDERING)
elseif(USE_VULCAN)
target_compile_definitions(Game PRIVATE VULCAN_RENDERING)
else()
target_compile_definitions(Game PRIVATE OPEN_GL_RENDERING)
endif()

# Add include directories for the engine
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/engine ${CMAKE_SOURCE_DIR}/engine/thirdparty/imgui)