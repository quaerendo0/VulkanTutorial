#pragma once

#include <vulkan/vulkan_core.h>
#include <optional>
#include <vector>
#include <memory>

namespace Vulkan {

    struct QueueFamilyIndices {
        // Index in vkGetPhysicalDeviceQueueFamilyProperties returned array
        // for the first family to support graphics commands
        std::optional<uint32_t> graphicsFamilyIndex;
    };

    class PhysicalDevice {

    public:
        explicit PhysicalDevice(const VkInstance& inst);
        VkPhysicalDevice getPhysicalDevicePtr() { return physicalDevice; }
        QueueFamilyIndices getQueueFamilies();

    private:
        std::vector<VkPhysicalDevice> listAvailableDevices();
        static bool isDeviceSuitable(VkPhysicalDevice device);
        static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        VkPhysicalDevice physicalDevice = nullptr;
        const VkInstance& referenceInstance;
    };

}