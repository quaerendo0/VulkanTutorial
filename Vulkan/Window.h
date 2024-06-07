#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include "Device.h"
#include "Instance.h"

#pragma once

namespace Vulkan {
    class Window {
    public:
        Window(int w, int h);

        ~Window();

        GLFWwindow *glfwWindowPtr() { return window; }

        bool shouldClose();

        static void pollEvents();

    private:
        int width = 800;
        int height = 600;

        void initWindow(int w, int h);

        GLFWwindow *window = nullptr;
        Instance *instance;
    };
}