cmake_minimum_required(VERSION 3.16)

project(MyOpenGL1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MyOpenGL1
    src/main.cpp
    src/glad.c
    src/Shader.cpp
    src/myStb.cpp
    include/Shader.h
    include/stb_image.h
    shaders/vertex.glsl
    shaders/fragment.glsl
    textures/wall.jpg
)

target_include_directories(MyOpenGL1 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_options(MyOpenGL1 PRIVATE
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)

target_compile_definitions(MyOpenGL1 PRIVATE
    SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    TEXTURE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

set(GLFW_ROOT "G:/MyOpenGL/glfw-3.4.bin.WIN64" CACHE PATH "Path to the GLFW prebuilt package")

add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_IMPLIB "${GLFW_ROOT}/lib-vc2022/glfw3dll.lib"
    IMPORTED_LOCATION "${GLFW_ROOT}/lib-vc2022/glfw3.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_ROOT}/include"
)

target_link_libraries(MyOpenGL1 PRIVATE glfw opengl32)

add_custom_command(TARGET MyOpenGL1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:glfw>"
        "$<TARGET_FILE_DIR:MyOpenGL1>"
)
