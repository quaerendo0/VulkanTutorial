#include <vulkan/vulkan_core.h>
#include "RenderPass.h"

Vulkan::RenderPass::RenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
}
