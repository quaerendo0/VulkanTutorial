#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <memory>

#include "Debug.h"
#include "PhysicalDevice.h"
#include "LogicalDevice.h"

namespace Vulkan {

    class Instance {
    public:
        explicit Instance(bool enableValidationLayers);

        ~Instance();

    private:
        const std::vector<const char *> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        VkInstance instance = nullptr;

        Debug* debug;
        PhysicalDevice* physicalDevice;
        LogicalDevice* logicalDevice;

        static std::vector<const char *> getRequiredExtensions(bool enableValidationLayers);
        void createInstance(bool enableValidationLayers);
        bool checkValidationLayerSupport();
    };

} // Vulkan