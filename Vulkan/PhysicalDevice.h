#pragma once

#include <vulkan/vulkan_core.h>
#include <optional>
#include <vector>
#include <memory>
#include "../Logger/ILogger.h"

namespace Vulkan {

    struct PhysicalDeviceQueueFamilyIndexInfo {
        // Index in vkGetPhysicalDeviceQueueFamilyProperties returned array
        // for the first family to support graphics commands
        std::optional<uint32_t> graphicsFamilyIndex;
        // support for windows presentation
        std::optional<uint32_t> presentFamily;

        bool supportsAllFamilies() const { return graphicsFamilyIndex.has_value() && presentFamily.has_value(); }
    };

    class PhysicalDevice {

    public:
        PhysicalDevice(const VkInstance& inst, const VkSurfaceKHR& surface, const Log::ILogger& logger);
        VkPhysicalDevice getPhysicalDevicePtr() { return physicalDevice; }
        PhysicalDeviceQueueFamilyIndexInfo getDeviceQueueFamiliesInfo();

    private:
        std::vector<VkPhysicalDevice> listAvailableDevices();
        static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
        static PhysicalDeviceQueueFamilyIndexInfo generateDeviceQueueFamiliesInfo(VkPhysicalDevice device, VkSurfaceKHR surface);

        VkPhysicalDevice physicalDevice = nullptr;
        const VkInstance& referenceInstance;
        const VkSurfaceKHR& referenceSurface;
        const Log::ILogger& logger;
    };

}