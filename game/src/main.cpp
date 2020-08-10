#include <Windows.h>
#include <engine.h>
#include <renderer/renderer.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    engine::initialize("delilah", glm::vec2(1280, 780), ENGINE_AA_X8 | ENGINE_BLEND | ENGINE_VSYNC);
    renderer::initialize();

    while (!window::should_close()) {
        renderer::new_frame();

        renderer::end_frame();
        engine::poll();
    }
}