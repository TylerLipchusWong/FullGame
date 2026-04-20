#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct GLFWwindow;

namespace Engine::Render {

class VulkanRenderer {
public:
    bool Initialize(GLFWwindow* window, int width, int height);
    void Shutdown();

    bool BeginFrame();
    bool EndFrame();

private:
    bool CreateInstance();
    bool CreateSurface(GLFWwindow* window);
    bool SelectPhysicalDevice();
    bool CreateDeviceAndQueue();
    bool CreateSwapchain(int width, int height);
    bool CreateRenderPass();
    bool CreateFramebuffers();
    bool CreateCommandPool();
    bool CreateCommandBuffers();
    bool CreateSyncObjects();

    void DestroySwapchainResources();

    VkInstance m_instance {VK_NULL_HANDLE};
    VkSurfaceKHR m_surface {VK_NULL_HANDLE};
    VkPhysicalDevice m_physicalDevice {VK_NULL_HANDLE};
    VkDevice m_device {VK_NULL_HANDLE};
    VkQueue m_graphicsQueue {VK_NULL_HANDLE};
    uint32_t m_graphicsQueueFamily {0};

    VkSwapchainKHR m_swapchain {VK_NULL_HANDLE};
    VkFormat m_swapchainFormat {VK_FORMAT_B8G8R8A8_UNORM};
    VkExtent2D m_extent {};
    std::vector<VkImage> m_swapchainImages;
    std::vector<VkImageView> m_swapchainImageViews;

    VkRenderPass m_renderPass {VK_NULL_HANDLE};
    std::vector<VkFramebuffer> m_framebuffers;

    VkCommandPool m_commandPool {VK_NULL_HANDLE};
    std::vector<VkCommandBuffer> m_commandBuffers;

    VkSemaphore m_imageAvailableSemaphore {VK_NULL_HANDLE};
    VkSemaphore m_renderFinishedSemaphore {VK_NULL_HANDLE};
    VkFence m_inFlightFence {VK_NULL_HANDLE};

    uint32_t m_currentImageIndex {0};
};

} // namespace Engine::Render
