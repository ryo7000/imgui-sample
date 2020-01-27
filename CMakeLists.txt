cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(external/glfw)

add_executable(main
    external/glad/src/glad.c
    external/imgui/examples/imgui_impl_glfw.cpp
    external/imgui/examples/imgui_impl_opengl3.cpp
    external/imgui/imgui.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_widgets.cpp
    src/main.cpp)
target_link_libraries(main glfw)
target_compile_definitions(main PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories(main PUBLIC
    external/imgui
    external/imgui/examples
    external/glad/include)
