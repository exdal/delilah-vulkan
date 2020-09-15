#pragma once
#include <chrono>
#include <string>

struct Scene;
struct Font;
struct FrameBuffer;
struct Game {
    double delta_time = 0;
    double last_frame = 0;
    double fps_last_frame = 0;
    int frames = 0;
    int fps = 0;

    Scene *current_scene = nullptr;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    uint32_t elapsed_ms;

    Font *font22;
    FrameBuffer *main_framebuffer;
};

namespace game {
    void initialize(const char *title);
    void set_scene(Scene *scene);
    void run();
    void deinitialize();

    Game *get();
}