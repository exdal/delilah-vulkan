#pragma once

#define ENGINE_VULKAN 1
#ifdef ENGINE_OGL
#include <renderer/opengl/renderer.h>
#elif ENGINE_OGL_ES
#elif ENGINE_VULKAN
#include <renderer/vulkan/vkrenderer.h>
#elif ENGINE_DX11
#include <Windows.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#endif // ENGINE_OGL

namespace renderer {
#ifdef ENGINE_DX11
    bool initialize(HWND hwnd, int width, int height, bool windowed);
#elif ENGINE_VULKAN
    bool initialize(int width, int height, bool windowed);
#endif
    void clear();
    void new_frame();
    void end_frame();
}