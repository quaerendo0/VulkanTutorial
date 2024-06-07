#pragma once

#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>
#include <iostream>

namespace Vulkan {

    class Debug {
    public:
        Debug(bool enableValidationLayers, VkInstance instance);

        ~Debug();

        static VkDebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo();

    private:
        VkInstance referenceInstance = nullptr;
        VkDebugUtilsMessengerEXT debugMessenger = nullptr;

        void setupDebugMessenger(bool enableValidationLayers, VkInstance instance);

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);

        static VkResult createDebugUtilsMessengerExt(
                VkInstance instance,
                const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                const VkAllocationCallbacks *pAllocator,
                VkDebugUtilsMessengerEXT *pDebugMessenger);

        static void destroyDebugUtilsMessengerExt(VkInstance instance,
                                                  VkDebugUtilsMessengerEXT debugMessenger,
                                                  const VkAllocationCallbacks *pAllocator);
    };

}