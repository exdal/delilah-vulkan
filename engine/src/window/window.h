#pragma once
#include <glm/glm.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <renderer/camera/camera.h>
#include <renderer/renderer.h>

struct Window {
    // members
    int32_t width;
    int32_t height;
#if ENGINE_VULKAN
    GLFWwindow *handle;
#endif // ENGINE_VULKAN

    bool windowed;
};

namespace window {
#if ENGINE_DX11
    void initialize(const char *caption, WNDPROC proc, glm::vec2 size, glm::vec2 pos);
    void resize(int32_t width, int32_t height);
    void adjust();
#elif ENGINE_VULKAN
    void initialize(const char *caption, int32_t width, int32_t height, int8_t multisample_size);
    bool should_close();
#endif // ENGINE_DX11


    Window *get();
}