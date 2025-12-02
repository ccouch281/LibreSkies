#include "vulkan.h"
#include <vector>
#include <iostream>
#include <cstring>

bool InitVulkan(GLFWwindow* window, VulkanContext &ctx, std::string &outError, std::string &outWarn)
{
    outError.clear();
    outWarn.clear();

    // Application info (optional)
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "LibreSkiesApp";
    appInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
    appInfo.pEngineName = "LibreSkiesEngine";
    appInfo.engineVersion = VK_MAKE_VERSION(0,1,0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Instance create
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Extensions required by GLFW
    uint32_t glfwExtCount = 0;
    const char** glfwExt = glfwGetRequiredInstanceExtensions(&glfwExtCount);
    std::vector<const char*> extensions;
    for(uint32_t i=0;i<glfwExtCount;i++) extensions.push_back(glfwExt[i]);

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.empty() ? nullptr : extensions.data();

    VkResult res = vkCreateInstance(&createInfo, nullptr, &ctx.Instance);
    if(res != VK_SUCCESS)
    {
        outError = "Failed to create Vulkan instance.";
        return false;
    }

    // Create surface from GLFW window
    if(glfwCreateWindowSurface(ctx.Instance, window, nullptr, &ctx.Surface) != VK_SUCCESS)
    {
        outError = "Failed to create window surface.";
        return false;
    }

    // Pick a physical device that supports graphics and present
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(ctx.Instance, &deviceCount, nullptr);
    if(deviceCount == 0)
    {
        outError = "No Vulkan-compatible GPU found.";
        return false;
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(ctx.Instance, &deviceCount, devices.data());

    for(const auto &dev : devices)
    {
        // Query queue families
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

        int graphicsIndex = -1;
        for(uint32_t i=0;i<queueFamilyCount;i++)
        {
            if(queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                VkBool32 presentSupport = VK_FALSE;
                vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, ctx.Surface, &presentSupport);
                if(presentSupport)
                {
                    graphicsIndex = static_cast<int>(i);
                    break;
                }
            }
        }

        if(graphicsIndex >= 0)
        {
            ctx.PhysicalDevice = dev;
            ctx.GraphicsQueueFamily = static_cast<uint32_t>(graphicsIndex);
            break;
        }
    }

    if(ctx.PhysicalDevice == VK_NULL_HANDLE)
    {
        outError = "No suitable physical device with graphics+present support found.";
        return false;
    }

    // Create logical device and retrieve queue
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = ctx.GraphicsQueueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;

    // Enable required device extensions for swapchain/present (optional here)
    const char* deviceExts[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    deviceCreateInfo.enabledExtensionCount = 1;
    deviceCreateInfo.ppEnabledExtensionNames = deviceExts;

    if(vkCreateDevice(ctx.PhysicalDevice, &deviceCreateInfo, nullptr, &ctx.Device) != VK_SUCCESS)
    {
        outError = "Failed to create logical Vulkan device.";
        return false;
    }

    vkGetDeviceQueue(ctx.Device, ctx.GraphicsQueueFamily, 0, &ctx.GraphicsQueue);

    // Print selected GPU name
    VkPhysicalDeviceProperties props;
    vkGetPhysicalDeviceProperties(ctx.PhysicalDevice, &props);
    std::cout << "Vulkan GPU: " << props.deviceName << "\n";

    return true;
}

void CleanupVulkan(VulkanContext &ctx)
{
    if(ctx.Device != VK_NULL_HANDLE)
    {
        vkDeviceWaitIdle(ctx.Device);
        vkDestroyDevice(ctx.Device, nullptr);
        ctx.Device = VK_NULL_HANDLE;
    }

    if(ctx.Surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(ctx.Instance, ctx.Surface, nullptr);
        ctx.Surface = VK_NULL_HANDLE;
    }

    if(ctx.Instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(ctx.Instance, nullptr);
        ctx.Instance = VK_NULL_HANDLE;
    }
}
