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
        //VkQueue graphicsQueue;
        //vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    };

}