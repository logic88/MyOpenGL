cmake_minimum_required(VERSION 3.16)

project(MyOpenGL_Lighting LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SHADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vs"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.fs"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl"
)

add_executable(MyOpenGL_Lighting
    src/main.cpp
    src/glad.c
    src/Shader.cpp
    src/myStb.cpp
    include/Shader.h
    include/stb_image.h
	include/Camera.h
    ${SHADER_FILES}
    textures/wall.jpg
)

target_include_directories(MyOpenGL_Lighting PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "../glm-1.0.3/glm"
)

target_compile_options(MyOpenGL_Lighting PRIVATE
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)

target_compile_definitions(MyOpenGL_Lighting PRIVATE
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

target_link_libraries(MyOpenGL_Lighting PRIVATE glfw opengl32)

add_custom_command(TARGET MyOpenGL_Lighting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:glfw>"
        "$<TARGET_FILE_DIR:MyOpenGL_Lighting>"
)
