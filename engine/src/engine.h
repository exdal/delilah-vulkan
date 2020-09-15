#pragma once
#include <renderer/shader/shader.h>
#include <window/window.h>
#include <glm/vec2.hpp>

#define ENGINE_NAME "Delilah"
#define ENGINE_VERSION "v0.1.0"
#define ENGINE_VERSION_REAL 6600
#define ENGINE_BUILD "#1"
#define ENGINE_BUILD_DATE __TIMESTAMP__
#ifdef DEBUG || ENGINE_DEBUG 
#define ENGINE_BUILD_TYPE "Debug"
#else
#define ENGINE_BUILD_TYPE "Release"
#endif // DEBUG || ENGINE_DEBUG

enum engine_settings {
    // window flags
    ENGINE_VSYNC = 1 << 0,
    ENGINE_RESIZE = 1 << 1,

    // opengl flags
    ENGINE_BLEND = 1 << 2,
    ENGINE_DEPTH = 1 << 3,

    // aa flags
    ENGINE_AA_X2 = 1 << 4, // this disables AA
    ENGINE_AA_X4 = 1 << 5,
    ENGINE_AA_X8 = 1 << 6
};

struct Engine {
    Shader main_shader;
    Shader blur_shader;
    uint8_t engine_state;
};

namespace engine {
    void initialize(const char *title, glm::vec2 window_size, int flags);
    void update_keyboard_input(double delta_time);
    void update_mouse_scroll(double xoffset, double yoffset);
    void update_mouse_input(int button, int action, int mods);
    void update_mouse_position(glm::vec2 pos);
    void poll();

    Engine *get();
}