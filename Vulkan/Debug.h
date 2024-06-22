#pragma once

#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>
#include <iostream>
#include "../Logger/ILogger.h"

namespace Vulkan {

    class Debug {
    public:
        static VkDebugUtilsMessengerCreateInfoEXT populateDebugMessengerCreateInfo(const Log::ILogger &logger);

        Debug(bool enableValidationLayers, const VkInstance &instance, const Log::ILogger &logger);

        ~Debug();

    private:
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

        const VkInstance &referenceInstance;
        VkDebugUtilsMessengerEXT debugMessenger = nullptr;
    };

}