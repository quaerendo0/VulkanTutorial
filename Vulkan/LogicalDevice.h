#pragma once

#include <vulkan/vulkan_core.h>
#include "PhysicalDevice.h"
#include "Queue.h"

namespace Vulkan {

    class LogicalDevice {

    public:
        LogicalDevice(const PhysicalDevice &physicalDevice,
                      const std::vector<const char *> &validationLayers,
                      bool enableValidationLayers);

        ~LogicalDevice();

        [[nodiscard]] const VkDevice &getDevicePtr() const { return device; }

        [[nodiscard]] const PhysicalDevice &getParentPhysicalDevice() const { return physicalDevice; }

    private:
        VkDevice device = nullptr;
        const PhysicalDevice &physicalDevice;

        static std::vector<VkDeviceQueueCreateInfo>
        generateVkDeviceQueueCreateInfoStructs(const PhysicalDevice &physicalDevice,
                                               PhysicalDeviceQueueFamilyIndexInfo familiesIndexes);

        static VkPhysicalDeviceFeatures generateVkPhysicalDeviceFeaturesStruct();

        static VkDeviceCreateInfo generateVkDeviceCreateInfoStruct(
                const std::vector<VkDeviceQueueCreateInfo> &queueCreateInfos,
                VkPhysicalDeviceFeatures *features,
                bool enableValidationLayers,
                const std::vector<const char *> &validationLayers);

        std::unique_ptr<Queue> graphicsQueue;
        std::unique_ptr<Queue> presentQueue;
    };

}