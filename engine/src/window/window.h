#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Window {
    // members
    int32_t width;
    int32_t height;
    GLFWwindow *handle;

    glm::vec2 mouse_pos;

    //Camera *camera;
    bool mouse_down;
};

namespace window {
    void initialize(const char *title, int32_t width, int32_t height, int8_t multisample_size);
    bool should_close();
    void set_camera();

    Window *get();
}