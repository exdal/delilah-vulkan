#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct Window {
    Window(const char *title, int32_t width, int32_t height, int8_t multisample_size);
    bool should_close();
    void set_camera();

    // members
    int32_t m_width;
    int32_t m_height;
    GLFWwindow *m_handle;

    glm::vec2 m_mouse_pos;

    //Camera *camera;
    bool m_mouse_down;
};