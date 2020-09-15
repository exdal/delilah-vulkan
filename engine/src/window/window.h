#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <renderer/camera/camera.h>

struct Window {
    // members
    int32_t width;
    int32_t height;
    GLFWwindow *handle;

    glm::vec2 mouse_pos;

    bool mouse_down;
};

namespace window {
    void initialize(const char *title, int32_t width, int32_t height, int8_t multisample_size);
    bool should_close();

    Window *get();
}