#pragma once

#include "Vulkan/Window.h"

namespace BromEngine {

    class App {
    public:
        void run();

    private:
        Vulkan::Window window{800, 600};
    };

}