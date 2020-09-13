#include "renderer.h"

#ifdef ENGINE_OGL
#include <renderer/opengl/renderer.h>
#elif ENGINE_OGL_ES
#elif ENGINE_VULKAN
#include <renderer/vulkan/vkrenderer.h>
#elif ENGINE_DX11
#include <renderer/directx/11/dx11renderer.h>
#endif // ENGINE_OGL

#ifdef ENGINE_DX11
bool renderer::initialize(HWND hwnd, int width, int height, bool windowed) {
    return dx11renderer::init(hwnd, width, height, windowed);
}
#elif ENGINE_VULKAN
bool renderer::initialize(int width, int height, bool windowed) {
    return vkrenderer::initialize(width, height, windowed);
}
#endif

void renderer::clear() {
}
void renderer::new_frame() {
}
void renderer::end_frame() {
}