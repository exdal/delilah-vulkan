#pragma once
#include <window/window.h>
#include <glm/vec2.hpp>

enum engine_settings {
    // window flags
    ENGINE_VSYNC = 1 << 0,
    ENGINE_RESIZE = 1 << 1,

    // opengl flags
    ENGINE_BLEND = 1 << 2,
    ENGINE_DEPTH = 1 << 3,

    // aa flags
    ENGINE_AA_X0 = 1 << 4, // this disables AA
    ENGINE_AA_X2 = 1 << 5,
    ENGINE_AA_X4 = 1 << 6,
    ENGINE_AA_X8 = 1 << 7
};

struct Engine {
    Window *m_window;
    
    Engine(const char *title, glm::vec2 window_size, int flags);
    void update_keyboard_input(Window *window, double delta_time);
    void update_mouse_input(int button, int action, int mods);
    void update_mouse_position(glm::vec2 pos);
    void poll();
};