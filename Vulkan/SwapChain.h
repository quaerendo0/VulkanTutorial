#pragma once

#include <vulkan/vulkan_core.h>
#include "SwapChainSupportDetails.h"
#include "GLFW/glfw3.h"
#include "PhysicalDevice.h"
#include "Surface.h"
#include "LogicalDevice.h"

namespace Vulkan {
    class SwapChain {
    public:
        SwapChain(const Vulkan::LogicalDevice &logicalDevice, const Surface &surface, GLFWwindow *window);

        ~SwapChain();

        static SwapChainSupportDetails
        querySwapChainSupport(const VkPhysicalDevice &device, const VkSurfaceKHR &surface);

        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

    private:
        VkSwapchainKHR swapChain;
        const LogicalDevice &logicalDevice;

        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    };
}