#include "App.h"

namespace BromEngine {
    void App::run() {
        while (!window.shouldClose()) {
            window.pollEvents();
        }
    }
}