# Create an executable target
add_executable(Game
    GameApplication.cpp
)

# Link the engine library
target_link_libraries(Game PRIVATE Engine)

# Add include directories for the engine
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/engine)