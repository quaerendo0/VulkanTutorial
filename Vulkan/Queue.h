#pragma once

#include <vulkan/vulkan.h>

namespace Vulkan {
    class Queue {
    public:
        Queue();
    private:
        VkQueue queue = nullptr;
    };
}