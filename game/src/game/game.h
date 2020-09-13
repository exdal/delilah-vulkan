#pragma once
#include <chrono>
#include <string>

struct App;
struct Scene;
struct Game {
    App *app;
};

namespace game {
    void initialize(const char *title);
    void set_scene(Scene *scene);
    void run();
    void deinitialize();

    Game *get();
}