#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <string>

struct VulkanContext
{
    VkInstance Instance = VK_NULL_HANDLE;
    VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
    VkDevice Device = VK_NULL_HANDLE;
    VkSurfaceKHR Surface = VK_NULL_HANDLE;
    uint32_t GraphicsQueueFamily = UINT32_MAX;
    VkQueue GraphicsQueue = VK_NULL_HANDLE;
};

// Initialize a minimal Vulkan context: instance, surface, pick physical device, create logical device and get graphics queue.
// Returns true on success and fills ctx. Caller is responsible for calling CleanupVulkan.
bool InitVulkan(GLFWwindow* window, VulkanContext &ctx, std::string &outError, std::string &outWarn);
void CleanupVulkan(VulkanContext &ctx);
