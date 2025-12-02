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
    #include <tiny_gltf.h>
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

    std::cout << "Created window. Close it to exit.\n";

    // Main loop (minimal)
    while(!glfwWindowShouldClose(window))
    {
        // Create a container for the loaded model
        const std::string assetPath = "C:/Users/usr/source/repos/LibreSkies/assets/SkyCube.glb";
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err;
        std::string warn;

        bool ret = false;
        try
        {
            ret = loader.LoadBinaryFromFile(&model, &err, &warn, assetPath);
        }
        catch(const std::exception &e)
        {
            std::cerr << "Exception while loading glTF: " << e.what() << std::endl;
        }

        if(!warn.empty())
        {
            std::cout << "glTF warn: " << warn << std::endl;
        }

        if(!err.empty())
        {
            std::cerr << "glTF err: " << err << std::endl;
        }

        if(!ret)
        {
            std::cerr << "Failed to load glTF: " << assetPath << std::endl;
        }
        else
        {
            std::cout << "Loaded glTF: " << assetPath << " (meshes=" << model.meshes.size() << ")\n";

            // Store model in registry as a single component (shared_ptr)
            auto modelPtr = std::make_shared<tinygltf::Model>(std::move(model));
            auto modelEntity = registry.create();
            registry.emplace<GLTFModelComponent>(modelEntity, GLTFModelComponent{modelPtr, assetPath});

            // Create entities for each mesh primitive
            for(size_t mi = 0; mi < modelPtr->meshes.size(); ++mi)
            {
                const tinygltf::Mesh &mesh = modelPtr->meshes[mi];
                const std::string meshName = mesh.name.empty() ? ("mesh_" + std::to_string(mi)) : mesh.name;

                for(size_t pi = 0; pi < mesh.primitives.size(); ++pi)
                {
                    const tinygltf::Primitive &prim = mesh.primitives[pi];
                    auto e = registry.create();
                    MeshComponent mc;
                    mc.MeshIndex = static_cast<int>(mi);
                    mc.PrimitiveIndex = static_cast<int>(pi);
                    mc.Name = meshName + "_prim_" + std::to_string(pi);
                    registry.emplace<MeshComponent>(e, mc);

                    std::cout << "Created entity for " << mc.Name << " (attributes: ";
                    for(const auto &attr : prim.attributes)
                    {
                        std::cout << attr.first << ",";
                    }
                    std::cout << ")\n";
                }
            }
        }
        glfwPollEvents();
        // In a real app you'd update ECS, run simulation and render here
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
