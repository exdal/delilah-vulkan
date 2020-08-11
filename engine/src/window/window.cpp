#include "window.h"
#include <renderer/renderer.h>
#include <renderer/camera/camera.h>
#include <engine.h>

static Window *s_window;

void framebuffer_size_callback(GLFWwindow *handle, int width, int height) {
    auto window = (Window *)glfwGetWindowUserPointer(handle);
    auto camera = camera::get();

    window->width = width;
    window->height = height;

    glfwMakeContextCurrent(handle);
    renderer::set_view(width, height);

    camera->size.x = (float)width;
    camera->size.y = (float)height;
    camera::update_matrices();
}

void mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
    engine::update_mouse_input(button, action, mods);
}

void mouse_position_callback(GLFWwindow *handle, double xpos, double ypos) {
    auto window = (Window *)glfwGetWindowUserPointer(handle);
    window->mouse_pos = glm::vec2(xpos, ypos);
}

void window::initialize(const char *title, int32_t width, int32_t height, int8_t multisample_size) {
    s_window = new (Window);

    // TODO(loanselot): make those hits are editable
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
