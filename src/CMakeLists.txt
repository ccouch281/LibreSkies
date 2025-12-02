# src CMake for the example application
add_executable(LibreSkiesApp main.cpp)

target_compile_features(LibreSkiesApp PRIVATE cxx_std_20)

# Include directories for header-only libraries
target_include_directories(LibreSkiesApp PRIVATE
    ${EnTT_SOURCE_DIR}/single_include
    ${tinygltf_SOURCE_DIR}
)

# Link GLFW (FetchContent provides target 'glfw')
# When using FetchContent, glfw provides a target named 'glfw' (static/shared lib)
find_package(Threads REQUIRED)
if(TARGET glfw)
    target_link_libraries(LibreSkiesApp PRIVATE glfw Threads::Threads)
else()
    message(WARNING "GLFW target not found; if you have system GLFW installed, link it manually.")
endif()

# Link Vulkan if available
if(Vulkan_FOUND)
    target_link_libraries(LibreSkiesApp PRIVATE Vulkan::Vulkan)
    target_compile_definitions(LibreSkiesApp PRIVATE USE_VULKAN=1)
endif()

# Simple compile flags for performance-focused builds (apply only for Release config)
if(MSVC)
    target_compile_options(LibreSkiesApp PRIVATE $<$<CONFIG:Release>:/O2> $<$<CONFIG:Release>:/arch:AVX2>)
else()
    target_compile_options(LibreSkiesApp PRIVATE $<$<CONFIG:Release>:-O3 -march=native>)
endif()
