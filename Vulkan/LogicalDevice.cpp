//
// Created by Asus on 6/8/2024.
//

#include <stdexcept>
#include "LogicalDevice.h"

namespace Vulkan {
    LogicalDevice::LogicalDevice(PhysicalDevice* physicalDevice,
                                 const std::vector<const char *>& validationLayers,
                                 bool enableValidationLayers) {
        auto queueFamilyIndex = (physicalDevice->getQueueFamilies()).graphicsFamilyIndex.value();

        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = &queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = 0;

        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(physicalDevice->getPhysicalDevicePtr(), &createInfo, nullptr, &device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical physicalDevice!");
        }
    }

    LogicalDevice::~LogicalDevice() {
        vkDestroyDevice(device, nullptr);
    }
} // Vulkan