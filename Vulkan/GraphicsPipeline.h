#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "LogicalDevice.h"
#include "SwapChain.h"

namespace Vulkan {

    class GraphicsPipeline {
    public:
        GraphicsPipeline(const LogicalDevice& logicalDevice, const SwapChain &swapChain);
        ~GraphicsPipeline();
    private:
        VkPipelineLayout pipelineLayout;
        const LogicalDevice& logicalDevice;
    };

}