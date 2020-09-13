#include "game.h"
#include <engine.h>
#include <filesys/gamesave.h>
#include <filesys/filesys.h>
#include <renderer/renderer.h>
#include <scenes/TestScene.h>
#include <app/app.h>

#include <Windows.h>

static Game *s_game;

void game::initialize(const char *title) {
    s_game = new (Game);

    if (!fsys::is_exists("state"))
        gamesave::write({ ENGINE_AA_X8 | ENGINE_BLEND, 1 }, "state");

    GameSave save = gamesave::load("state");

    s_game->app = new (App);
    //s_game->app->initialize(title, { GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 50 }, { 10, 10 });
    s_game->app->initialize(title, 1280, 768);

    if (!s_game->app->current_scene)
        s_game->app->current_scene = scene::create<TestScene>();

    s_game->app->current_scene->initialize();
}

void game::set_scene(Scene *scene) {
    s_game->app->current_scene = scene;
}

void game::run() {
    s_game->app->run();
}

void game::deinitialize() {
    if (s_game->app->current_scene)
        s_game->app->current_scene->deinitialize();

    gamesave::write({ engine::get()->engine_state, 0 }, "state");
}

Game *game::get() {
    return s_game;
}
