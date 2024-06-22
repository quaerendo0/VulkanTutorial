#include "Queue.h"
#include "LogicalDevice.h"

Vulkan::Queue::Queue(const LogicalDevice& device, ) {

    vkGetDeviceQueue(device, queueFamilyIndex, 0, &graphicsQueue);
}
