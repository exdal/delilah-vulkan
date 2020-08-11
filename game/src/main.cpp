#include <Windows.h>
#include <engine.h>
#include <renderer/renderer.h>
#include <renderer/camera/camera.h>
#include <filesys/gamesave.h>
#include <filesys/filesys.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    if (!fsys::is_exists("state"))
        gamesave::write({ ENGINE_AA_X8 | ENGINE_BLEND | ENGINE_VSYNC }, "state");

    GameSave save = gamesave::load("state");
    engine::initialize("delilah", glm::vec2(1280, 780), save.engine_state);

    

    while (!window::should_close()) {
        renderer::new_frame();

        shader::use(engine::get()->main_shader);
        shader::set_mat4(engine::get()->main_shader, "u_projection", camera::get()->projection);
        shader::set_mat4(engine::get()->main_shader, "u_view", camera::get()->view);

        renderer::draw_rect({ 50, 50 }, { 100, 100 }, { 1, 1, 1, 1 }, 1);
        renderer::draw_rect({ 250, 50 }, { 100, 100 }, { 1, 0, 1, 1 }, 1);
        renderer::draw_rect({ 250, 250 }, { 50, 100 }, { 0, 0, 1, 1 }, 1);

        renderer::end_frame();
        engine::poll();
    }
}