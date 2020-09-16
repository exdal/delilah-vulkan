#include "game.h"
#include <engine.h>
#include <filesys/gamesave.h>
#include <filesys/filesys.h>
#include <chrono>
#include <thread>
#include <renderer/vulkan/vk_renderer.h>

static Game *s_game;

void calc_fps() {
    auto current_frame = glfwGetTime();
    s_game->frames++;
    s_game->delta_time = current_frame - s_game->last_frame;
    s_game->last_frame = current_frame;
    if (current_frame - s_game->fps_last_frame >= 1) {
        s_game->fps_last_frame += 1;
        s_game->fps = s_game->frames;
        s_game->frames = 0;
    }
}

void game::initialize(const char *title) {
    s_game = new (Game);

    if (!fsys::is_exists("state"))
        gamesave::write({ ENGINE_AA_X2, 1 }, "state");

    GameSave save = gamesave::load("state");

    engine::initialize(title, glm::vec2(1280, 780), save.engine_state);
    //assetmgr::initialize();

    camera::get()->zoom = save.zoom;
    camera::update_matrices();

    renderer::initialize();
}

void game::set_scene(Scene *scene) {
    s_game->current_scene = scene;
}

void game::run() {
    while (!window::should_close()) {
        s_game->begin = std::chrono::steady_clock::now();
        calc_fps();

        renderer::draw_frame();

        engine::update_keyboard_input(s_game->delta_time);
        engine::poll();

        s_game->end = std::chrono::steady_clock::now();
        s_game->elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(s_game->end - s_game->begin).count();
    }
}

void game::deinitialize() {
    gamesave::write({ engine::get()->engine_state, camera::get()->zoom }, "state");
}

Game *game::get() {
    return s_game;
}
