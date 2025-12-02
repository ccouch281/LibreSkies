#include <iostream>
#include <memory>

// Optional Vulkan include
#ifdef USE_VULKAN
#include <vulkan/vulkan.h>
#endif

#include <GLFW/glfw3.h>
// Minimal math replacement to avoid an external dependency in the starter.
#include <entt/entt.hpp>

struct Vec3
{
    float x;
    float y;
    float z;
};

// Components used for imported glTF data (runtime engine would expand these)
struct GLTFModelComponent
{
    std::shared_ptr<tinygltf::Model> Model;
    std::string Path;
};

struct MeshComponent
{
    int MeshIndex;
    int PrimitiveIndex;
    std::string Name;
};

int main()

    // Basic EnTT usage
    entt::registry registry;
    struct Position
    {
        Vec3 Value;
    };

    auto entity = registry.create();
    registry.emplace<Position>(entity, Vec3{0.0f, 1.0f, 2.0f});

    auto &pos = registry.get<Position>(entity);
    std::cout << "Entity position: (" << pos.Value.x << ", " << pos.Value.y << ", " << pos.Value.z << ")\n";

    // Initialize GLFW and create a window (no GL context; used for input/windowing)
    if(!glfwInit())
    {
    #include <filesystem>
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

#ifdef USE_VULKAN
    VulkanContext vkctx{};
    std::string vkErr, vkWarn;
    if(InitVulkan(window, vkctx, vkErr, vkWarn))
    {
        std::cout << "Vulkan initialized successfully." << std::endl;
    }
    else
    {
        std::cerr << "Vulkan init failed: " << vkErr << std::endl;
    }
#endif

    std::cout << "Created window. Close it to exit.\n";

    // Main loop (minimal)
    while(!glfwWindowShouldClose(window))
    {
        // Attempt to find the asset on disk and report status. If tinygltf is available
        // build-time, we can load and parse the file; currently tinygltf is not
        // fetched by the build system, so we only check for presence.
        const std::string assetPath = std::string("C:") + std::filesystem::path("\\Users\\usr\\source\\repos\\LibreSkies\\assets\\SkyCube.glb").string();
        if(std::filesystem::exists(assetPath))
        {
            std::cout << "Asset exists at: " << assetPath << " (glTF loader not enabled in this build)\n";
            std::cout << "To enable runtime glTF loading, add tinygltf to the build or provide an external loader.\n";
        }
        else
        {
            std::cout << "Asset not found at: " << assetPath << "\n";
        }
        glfwPollEvents();
        // In a real app you'd update ECS, run simulation and render here
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
