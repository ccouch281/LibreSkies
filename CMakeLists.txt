cmake_minimum_required(VERSION 3.16)
project(LibreSkies VERSION 0.1 LANGUAGES CXX)

# Project settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Try to find Vulkan (optional, recommended)
find_package(Vulkan QUIET)
if(NOT Vulkan_FOUND)
    message(WARNING "Vulkan not found. Install the Vulkan SDK for full functionality.")
endif()

# Fetch header-only GLM (math) and EnTT (ECS), and GLFW for windowing
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8
)

FetchContent_Declare(
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.10.0
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)

# Make available
FetchContent_MakeAvailable(glm EnTT glfw)

# Add src directory
add_subdirectory(src)
