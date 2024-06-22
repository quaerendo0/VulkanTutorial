#include "Window.h"

void Vulkan::Window::initWindow(int w, int h) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
}

Vulkan::Window::Window(int w, int h, const Log::ILogger& logger) : width{w}, height{h} {
    initWindow(width, height);
    instance = new Instance(true, logger);
    debug = new Debug(enableValidationLayers, instance->getInstance(), logger);
    surface = new Surface(instance->getInstance(), window);
    physicalDevice = new PhysicalDevice(instance->getInstance(), surface->getSurface(), logger);
    logicalDevice = new LogicalDevice(*physicalDevice, Instance::validationLayers, enableValidationLayers);
}

Vulkan::Window::~Window() {
    delete logicalDevice;
    delete physicalDevice;
    delete surface;
    delete debug;
    delete instance;
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Vulkan::Window::shouldClose() { return glfwWindowShouldClose(window); }

void Vulkan::Window::pollEvents() {
    glfwPollEvents();
}
