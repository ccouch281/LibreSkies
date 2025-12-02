cmake_minimum_required(VERSION 3.16)
# Use an explicit policy version to avoid compatibility failures when fetching
# older dependencies that declare very old cmake_minimum_required values.
cmake_policy(VERSION 3.16)
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
    EnTT
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.10.0
)

FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG master
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)

# Make available
FetchContent_MakeAvailable(EnTT glfw)

# Add src directory
add_subdirectory(src)
