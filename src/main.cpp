#include <iostream>
#include <memory>

// Optional Vulkan include
#ifdef USE_VULKAN
#include <vulkan/vulkan.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <entt/entt.hpp>

int main()
{
    // Basic EnTT usage
    entt::registry registry;
    struct Position
    {
        glm::vec3 Value;
    };

    auto entity = registry.create();
    registry.emplace<Position>(entity, glm::vec3(0.0f, 1.0f, 2.0f));

    auto &pos = registry.get<Position>(entity);
    std::cout << "Entity position: (" << pos.Value.x << ", " << pos.Value.y << ", " << pos.Value.z << ")\n";

    // Initialize GLFW and create a window (no GL context; used for input/windowing)
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

#ifdef USE_VULKAN
    if(!glfwVulkanSupported())
    {
        std::cerr << "GLFW reports Vulkan not supported on this system.\n";
    }
#endif

    // Create a windowed mode window and its context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // We will use Vulkan or no GL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "LibreSkies - Example", nullptr, nullptr);
    if(!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "Created window. Close it to exit.\n";

    // Main loop (minimal)
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // In a real app you'd update ECS, run simulation and render here
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
