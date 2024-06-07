#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "Debug.h"

namespace Vulkan {

    class Instance {
    public:
        Instance(bool enableValidationLayers) {
            createInstance(enableValidationLayers);
            debug = new Debug{enableValidationLayers, instance};
        }
        ~Instance() {
            delete debug;
        }
    private:
        VkInstance instance = nullptr;
        Debug* debug = nullptr;
        const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
        };

        static std::vector<const char*> getRequiredExtensions(bool enableValidationLayers);
        void createInstance(bool enableValidationLayers);
        bool checkValidationLayerSupport();
    };

} // Vulkan