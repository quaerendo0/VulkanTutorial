#pragma once

#include <vulkan/vulkan_core.h>
#include <optional>
#include <vector>
#include <memory>
#include "../Logger/ILogger.h"
#include "PhysicalDeviceQueueFamilyIndexInfo.h"

namespace Vulkan {
    class PhysicalDevice {

    public:
        PhysicalDevice(const VkInstance &inst, const VkSurfaceKHR &surface, const Log::ILogger &logger);

        const VkPhysicalDevice &getPhysicalDevicePtr() const { return physicalDevice; }

        PhysicalDeviceQueueFamilyIndexInfo getDeviceQueueFamiliesInfo() const;

    private:
        std::vector<VkPhysicalDevice> listAvailableDevices();

        static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);

        static PhysicalDeviceQueueFamilyIndexInfo
        generateDeviceQueueFamiliesInfo(VkPhysicalDevice device, VkSurfaceKHR surface);

        VkPhysicalDevice physicalDevice = nullptr;
        const VkInstance &referenceInstance;
        const VkSurfaceKHR &referenceSurface;
        const Log::ILogger &logger;
    };

}