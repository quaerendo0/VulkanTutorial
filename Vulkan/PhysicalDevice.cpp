#include <stdexcept>
#include <vector>
#include "PhysicalDevice.h"

namespace Vulkan {

    std::vector<VkPhysicalDevice> PhysicalDevice::listAvailableDevices() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        return devices;
    }

    PhysicalDevice::PhysicalDevice(VkInstance inst) : instance{inst} {
        auto devices = listAvailableDevices();

        for (auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        bool suitable = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                        deviceFeatures.geometryShader;

        auto familyIndices = findQueueFamilies(device);

        suitable = suitable && familyIndices.graphicsFamilyIndex.has_value();

        return suitable;
    }

    QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamilyIndex = i;
            }

            i++;
        }

        return indices;
    }

    QueueFamilyIndices PhysicalDevice::getQueueFamilies() {
        return findQueueFamilies(physicalDevice);
    }
}