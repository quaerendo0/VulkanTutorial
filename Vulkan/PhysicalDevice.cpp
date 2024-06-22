#include <stdexcept>
#include <vector>
#include <set>
#include "PhysicalDevice.h"
#include "SwapChainSupportDetails.h"
#include "SwapChain.h"

namespace Vulkan {
    const std::vector<const char *> PhysicalDevice::deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    std::vector<VkPhysicalDevice> PhysicalDevice::listAvailableDevices() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(referenceInstance, &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(referenceInstance, &deviceCount, devices.data());

        return devices;
    }

    /*
     * Creates physical device by using instance (main Vulkan entity) and window surface (VkSurfaceKHR), that was already created.
     * If cannot create, throws exception.
     */
    PhysicalDevice::PhysicalDevice(
            const VkInstance &inst,
            const VkSurfaceKHR &surface,
            const Log::ILogger &logger) : referenceInstance{inst}, referenceSurface{surface}, logger{logger} {
        auto devices = listAvailableDevices();

        for (auto &device: devices) {
            VkPhysicalDeviceProperties deviceProps{};
            vkGetPhysicalDeviceProperties(device, &deviceProps);
            logger.LogInfo("Found device: " + std::string(deviceProps.deviceName) + ", checking suitability.");

            if (isDeviceSuitable(device, surface)) {
                physicalDevice = device;
                logger.LogInfo("Device \"" + std::string(deviceProps.deviceName) + "\" is suitable and initialized.");
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    bool PhysicalDevice::isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        bool suitable = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
                        deviceFeatures.geometryShader;

        bool extensionsSupported = checkDeviceExtensionSupport(device);

        auto familyIndices = generateDeviceQueueFamiliesInfo(device, surface);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = SwapChain::querySwapChainSupport(device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }
        suitable = suitable && familyIndices.supportsAllFamilies() && extensionsSupported && swapChainAdequate;

        return suitable;
    }

    PhysicalDeviceQueueFamilyIndexInfo
    PhysicalDevice::generateDeviceQueueFamiliesInfo(VkPhysicalDevice device, VkSurfaceKHR surface) {
        PhysicalDeviceQueueFamilyIndexInfo indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto &queueFamily: queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            i++;
        }

        return indices;
    }

    PhysicalDeviceQueueFamilyIndexInfo PhysicalDevice::getDeviceQueueFamiliesInfo() const {
        return generateDeviceQueueFamiliesInfo(physicalDevice, referenceSurface);
    }

    bool PhysicalDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

        for (const auto &extension: availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }
}