#pragma once

#include <vulkan/vulkan_core.h>
#include "PhysicalDevice.h"

namespace Vulkan {

    class LogicalDevice {

    public:
        LogicalDevice(PhysicalDevice& physicalDevice,
                      const std::vector<const char *>& validationLayers,
                      bool enableValidationLayers);

        ~LogicalDevice();

    private:
        VkDevice device = nullptr;
        VkQueue graphicsQueue = nullptr;

        static VkDeviceQueueCreateInfo generateVkDeviceQueueCreateInfoStruct(PhysicalDevice& physicalDevice, unsigned int queueFamilyIndex);
        static VkPhysicalDeviceFeatures generateVkPhysicalDeviceFeaturesStruct();
        static VkDeviceCreateInfo generateVkDeviceCreateInfoStruct(
            VkDeviceQueueCreateInfo* queueCreateInfo,
            VkPhysicalDeviceFeatures* features,
            bool enableValidationLayers,
            const std::vector<const char *>& validationLayers);

        void initializeGraphicsQueue(unsigned int queueFamilyIndex);
    };

}