#if ENGINE_DX11
#pragma once
#include <d3d11.h>
#include <d3dCompiler.h>
#include <cstdint>

#include <glm/glm.hpp>

#include <Windows.h>
#undef max
#define WIN32_LEAN_AND_MEAN

#include <utils/utils.h>

struct DX11Device {
    ID3D11Device *device;
    ID3D11DeviceContext *device_context;
    IDXGISwapChain *swap_chain;

    ID3D11BlendState *blend_state;
    ID3D11RenderTargetView *renderer_target_view;
    ID3D11DepthStencilView *depth_stencil_view;
    ID3D11Texture2D *depth_stencil_buffer;

    ID3D11DepthStencilState *depth_stencil_state;
    ID3D11RasterizerState *rasterizer_state;

    bool msaa = false;
    int32_t msaa_count;
    uint32_t msaa_quality;
    bool windowed;
};

namespace dx11renderer {
    bool init(HWND hwnd, int width, int height, bool windowed);
    void shutdown();
    void resize(int width, int height);
    void clear(const glm::vec4 &color);
    void present(int32_t syncInterval = 0, int32_t presentFlag = 0);
}
#endif