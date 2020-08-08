#include <Windows.h>
#include <engine.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    Engine *engine = new Engine("delilah", glm::vec2(1280, 780), ENGINE_AA_X8 | ENGINE_BLEND | ENGINE_VSYNC);

    while (!engine->m_window->should_close()) {
        engine->poll();
    }
}