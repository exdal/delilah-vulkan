#pragma once
#include <window/window.h>

struct Scene;
struct App {
    bool initialize(const char *title, uint32_t width, uint32_t height, glm::vec2 pos = glm::vec2(0, 0));
    void run();
    void shutdown();

    Scene *current_scene = nullptr;
};

namespace app {
    
}