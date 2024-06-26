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

        [[nodiscard]] const VkDevice &getDevicePtr() const noexcept { return device; }

        [[nodiscard]] const PhysicalDevice &getParentPhysicalDevice() const noexcept { return physicalDevice; }

    private:
        VkDevice device = nullptr;
        const PhysicalDevice &physicalDevice;

        std::unique_ptr<Queue> graphicsQueue;
        std::unique_ptr<Queue> presentQueue;
    };

}