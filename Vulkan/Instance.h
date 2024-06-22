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
        static const std::vector<const char *> validationLayers;

        explicit Instance(bool enableValidationLayers, const Log::ILogger &logger);

        ~Instance();

        const VkInstance &getInstance() { return instance; }

    private:

        VkInstance instance = nullptr;
        const Log::ILogger &logger;

        static std::vector<const char *> getRequiredExtensions(bool enableValidationLayers, const Log::ILogger &logger);

        void createInstance(bool enableValidationLayers);

        static bool checkValidationLayerSupport();
    };

} // Vulkan