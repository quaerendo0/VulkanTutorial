#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Surface {
public:
    Surface(const VkInstance& instance, GLFWwindow* window);
    const VkSurfaceKHR& getSurface() { return surface; }
    ~Surface();
private:
    VkSurfaceKHR surface;
    const VkInstance& referenceInstance;
};
