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

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx"
)

file(GLOB_RECURSE PROJECT_HEADER_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hh"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hxx"
)

add_executable(MyOpenGL_Lighting
    ${PROJECT_SOURCE_FILES}
    ${PROJECT_HEADER_FILES}
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
	MODEL_DIR="${CMAKE_CURRENT_SOURCE_DIR}/models"
)

set(GLFW_ROOT "../glfw-3.4.bin.WIN64")
set(ASSIMP_ROOT "../Assimp_windows-x64-v6.0.5")

get_filename_component(GLFW_ROOT_ABS "${GLFW_ROOT}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
get_filename_component(ASSIMP_ROOT_ABS "${ASSIMP_ROOT}" ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_IMPLIB "${GLFW_ROOT_ABS}/lib-vc2022/glfw3dll.lib"
    IMPORTED_LOCATION "${GLFW_ROOT_ABS}/lib-vc2022/glfw3.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${GLFW_ROOT_ABS}/include"
)

target_include_directories(MyOpenGL_Lighting PRIVATE
    "${ASSIMP_ROOT_ABS}/include"
)

set(ASSIMP_IMPLIB "${ASSIMP_ROOT_ABS}/Release/assimp-vc143-mt.lib")
set(ASSIMP_DLL "${ASSIMP_ROOT_ABS}/Release/assimp-vc143-mt.dll")

if(EXISTS "${ASSIMP_IMPLIB}")
    add_library(assimp SHARED IMPORTED)
    set_target_properties(assimp PROPERTIES
        IMPORTED_IMPLIB "${ASSIMP_IMPLIB}"
        IMPORTED_LOCATION "${ASSIMP_DLL}"
        INTERFACE_INCLUDE_DIRECTORIES "${ASSIMP_ROOT_ABS}/include"
    )

    target_link_libraries(MyOpenGL_Lighting PRIVATE assimp)

    add_custom_command(TARGET MyOpenGL_Lighting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:assimp>"
            "$<TARGET_FILE_DIR:MyOpenGL_Lighting>"
    )
else()
    message(WARNING "Assimp import library not found: ${ASSIMP_IMPLIB}. Headers are configured, but linking Assimp code requires assimp-vc143-mt.lib.")

    if(EXISTS "${ASSIMP_DLL}")
        add_custom_command(TARGET MyOpenGL_Lighting POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${ASSIMP_DLL}"
                "$<TARGET_FILE_DIR:MyOpenGL_Lighting>"
        )
    endif()
endif()

target_link_libraries(MyOpenGL_Lighting PRIVATE glfw opengl32)

add_custom_command(TARGET MyOpenGL_Lighting POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:glfw>"
        "$<TARGET_FILE_DIR:MyOpenGL_Lighting>"
)
