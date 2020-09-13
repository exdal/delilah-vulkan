#include "window.h"
#include <renderer/renderer.h>
#include <renderer/camera/camera.h>
#include <utils/logger.h>
#include <engine.h>
#include <game/game.h>
#include <utils/utils.h>
#include <vulkan/vulkan.h>

static Window *s_window;

#if ENGINE_DX11
void window::initialize(const char *caption, WNDPROC proc, glm::vec2 size, glm::vec2 pos) {
    s_window = new (Window);

    s_window->width = size.x;
    s_window->height = size.y;
    s_window->x = pos.x;
    s_window->y = pos.y;
    s_window->style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = proc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = caption;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);

    s_window->hWnd =
        CreateWindowEx(NULL, wc.lpszClassName, caption, s_window->style, (int32_t)pos.x, (int32_t)pos.y, (int32_t)size.x, (int32_t)size.y, NULL, NULL, NULL, NULL);

    ShowWindow(s_window->hWnd, SW_NORMAL);
    UpdateWindow(s_window->hWnd);
}

void window::resize(int32_t width, int32_t height) {
}

void window::adjust() {
    RECT rect;
    rect.left = (LONG)s_window->x;
    rect.top = (LONG)s_window->y;
    rect.right = (LONG)s_window->width;
    rect.bottom = (LONG)s_window->height;
    AdjustWindowRect(&rect, s_window->style, false);
}

#elif ENGINE_VULKAN
void window::initialize(const char *caption, int32_t width, int32_t height, int8_t multisample_size) {
    s_window = new (Window);

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    s_window->handle = glfwCreateWindow(width, height, caption, nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    logger::logf("extc: %d\n", extensionCount);
}
bool window::should_close() {
    return glfwWindowShouldClose(s_window->handle);
}
#endif

Window *window::get() {
    return s_window;
}
