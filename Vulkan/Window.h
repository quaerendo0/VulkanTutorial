#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include "PhysicalDevice.h"
#include "Instance.h"
#include "Surface.h"

#pragma once

namespace Vulkan {
    class Window {
    public:
        Window(int w, int h, const Log::ILogger& logger);
        ~Window();

        bool shouldClose();
        static void pollEvents();

    private:
        int width = 800;
        int height = 600;

        static const bool enableValidationLayers = true;

        void initWindow(int w, int h);

        GLFWwindow *window = nullptr;
        Instance *instance;

        Debug* debug;
        Surface* surface;
        PhysicalDevice* physicalDevice;
        LogicalDevice* logicalDevice;
    };
}