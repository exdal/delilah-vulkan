#include "window.h"

void framebuffer_size_callback(GLFWwindow *handle, int width, int height) {
    auto window = (Window *)glfwGetWindowUserPointer(handle);
    /*auto camera = window->camera;

    window->width = width;
    window->height = height;

    glfwMakeContextCurrent(handle);
    glViewport(0, 0, width, height);

    camera->aspect = (float)width / (float)height;
    camera->size.x = (float)width;
    camera->size.y = (float)height;
    camera::update_matrices(camera);
    camera::update_gui_matrices(camera);*/
}

void mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
    //engine::update_mouse_input(button, action, mods);
}

void mouse_position_callback(GLFWwindow *handle, double xpos, double ypos) {
    auto window = (Window *)glfwGetWindowUserPointer(handle);
    //auto camera = (Camera *)glfwGetWindowUserPointer(handle);
    //window->mouse_pos = glm::vec2(xpos, ypos);
}

Window::Window(const char *title, int32_t width, int32_t height, int8_t multisample_size) : m_width(width), m_height(height) {
    // TODO(loanselot): make those hits are editable
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, multisample_size); // enable 8x MSAA

    m_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    m_width = width;
    m_height = height;

    glfwSetWindowUserPointer(m_handle, this);

    // callbacks
    glfwSetFramebufferSizeCallback(m_handle, framebuffer_size_callback);
    glfwSetMouseButtonCallback(m_handle, mouse_button_callback);
    glfwSetCursorPosCallback(m_handle, mouse_position_callback);

    glfwMakeContextCurrent(m_handle);
}

bool Window::should_close() {
    return glfwWindowShouldClose(m_handle);
}
