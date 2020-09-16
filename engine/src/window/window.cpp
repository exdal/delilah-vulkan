#include "window.h"
#include <renderer/camera/camera.h>
#include <utils/logger.h>
#include <engine.h>
#include <game/game.h>
#include <utils/utils.h>
#include <renderer/vulkan/vk_core.h>

static Window *s_window;

void framebuffer_size_callback(GLFWwindow *handle, int width, int height) {
    if (_vk::_core::get())
        _vk::_core::get()->resized = true;
}

void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    //engine::update_mouse_scroll(xoffset, yoffset);
}

void mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
}

void mouse_position_callback(GLFWwindow *handle, double xpos, double ypos) {
    auto window = (Window *)glfwGetWindowUserPointer(handle);
    window->mouse_pos = glm::vec2(xpos, ypos);

}

void window::initialize(const char *title, int32_t width, int32_t height, int8_t multisample_size) {
    s_window = new (Window);
    
    // TODO(loanselot): make those hits are editable

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);     
    glfwWindowHint(GLFW_SAMPLES, multisample_size); // enable x MSAA

    s_window->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    s_window->width = width;
    s_window->height = height;

    glfwSetWindowUserPointer(s_window->handle, s_window);

    // callbacks
    glfwSetFramebufferSizeCallback(s_window->handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(s_window->handle, mouse_button_callback);
    glfwSetCursorPosCallback(s_window->handle, mouse_position_callback);

    glfwMakeContextCurrent(s_window->handle);
}

bool window::should_close() {
    return glfwWindowShouldClose(s_window->handle);
}


Window *window::get() {
    return s_window;
}
