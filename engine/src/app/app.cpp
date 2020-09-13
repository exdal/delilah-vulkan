#include "app.h"
#include <engine.h>
#include <utils\logger.h>
#include <renderer/renderer.h>

static App *s_app;
#if ENGINE_DX11
LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(ENGINE_QUIT_WNDPROC);
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}
#endif
bool App::initialize(const char *title, uint32_t width, uint32_t height, glm::vec2 pos) {
    s_app = new (App);
    logger::clear();

#if ENGINE_DX11
    window::initialize(title, wndproc, size, pos);
#elif ENGINE_VULKAN
    window::initialize(title, width, height, 0);
#endif

    return engine::initialize(window::get(), 0);
}

void App::run() {
#if ENGINE_DX11
    MSG msg;
    while (true) {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                logger::logf("Killed app with message %#08x\n", msg.wParam);
                shutdown();
                return;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        dx11renderer::clear({ 0, 0, 0, 1 });
        dx11renderer::present(1, 0);
    }
#elif ENGINE_VULKAN
    while (!window::should_close()) {
        engine::poll();
    }
#endif
}

void App::shutdown() {
}
