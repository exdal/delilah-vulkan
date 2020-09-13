#if ENGINE_DX11
#include "dx11renderer.h"
#include <utils/logger.h>

static DX11Device *s_device;

#define LOG_ERROR_L logger::logf("DX11 ERROR | %#08x(L%d)\n", hr, __LINE__)

bool dx11renderer::init(HWND hwnd, int width, int height, bool windowed) {
    s_device = new (DX11Device);
    s_device->windowed = windowed;

    uint32_t createDeviceFlags = 0;

#if defined(_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0, D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1 };

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &s_device->device,
        &featureLevel, &s_device->device_context);

    if (FAILED(hr)) {
        LOG_ERROR_L;
        return false;
    }

    // swap chain
    s_device->device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, s_device->msaa_count, &s_device->msaa_quality);

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.OutputWindow = hwnd;
    if (s_device->msaa) {
        scd.SampleDesc.Count = s_device->msaa_count;
        scd.SampleDesc.Quality = s_device->msaa_quality - 1;
    } else {
        scd.SampleDesc.Count = 1;
        scd.SampleDesc.Quality = 0;
    }
    scd.Windowed = windowed;

    IDXGIDevice *dxgiDevice = 0;
    s_device->device->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);

    IDXGIAdapter *dxgiAdapter = 0;
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void **)&dxgiAdapter);

    IDXGIFactory *dxgiFactory = 0;
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&dxgiFactory);

    hr = dxgiFactory->CreateSwapChain(s_device->device, &scd, &s_device->swap_chain);
    if (FAILED(hr)) {
        LOG_ERROR_L;
        return false;
    }
    SAFE_RELEASE(dxgiDevice);
    SAFE_RELEASE(dxgiAdapter);
    SAFE_RELEASE(dxgiFactory);

    s_device->swap_chain->SetFullscreenState(!windowed, NULL);

    

    // depth stencil texture
    ID3D11Texture2D *backBuffer = NULL;
    if (FAILED(s_device->swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBuffer))) {
        LOG_ERROR_L;
        return false;
    }

    if (FAILED(s_device->device->CreateRenderTargetView(backBuffer, 0, &s_device->renderer_target_view))) {
        LOG_ERROR_L;
        return false;
    }

    SAFE_RELEASE(backBuffer);

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
    bd.RenderTarget[0].BlendEnable = true;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    if (FAILED(s_device->device->CreateBlendState(&bd, &s_device->blend_state))) {
        LOG_ERROR_L;
        return false;
    }

    s_device->device_context->OMSetBlendState(s_device->blend_state, 0, 0xffffffff);

    // Depth/Stencil Texture Creation
    D3D11_TEXTURE2D_DESC td;
    td.ArraySize = 1;
    td.MipLevels = 1;
    td.Width = width;
    td.Height = height;
    td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    td.CPUAccessFlags = 0;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    td.MiscFlags = 0;
    if (s_device->msaa) {
        td.SampleDesc.Count = s_device->msaa_count;
        td.SampleDesc.Quality = s_device->msaa_quality - 1;
    } else {
        td.SampleDesc.Count = 1;
        td.SampleDesc.Quality = 0;
    }
    td.Usage = D3D11_USAGE_DEFAULT;

    if (FAILED(s_device->device->CreateTexture2D(&td, 0, &s_device->depth_stencil_buffer))) {
        LOG_ERROR_L;
        return false;
    }

    if (FAILED(s_device->device->CreateDepthStencilView(s_device->depth_stencil_buffer, 0, &s_device->depth_stencil_view))) {
        LOG_ERROR_L;
        return false;
    }

    // Bind the Views to the Output Merger Stage
    s_device->device_context->OMSetRenderTargets(1, &s_device->renderer_target_view, s_device->depth_stencil_view);

    // depth stencil state
    D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc;
    ZeroMemory(&depthStencilStateDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilStateDesc.DepthEnable = s_device->msaa;
    depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    depthStencilStateDesc.StencilEnable = FALSE;

    hr = s_device->device->CreateDepthStencilState(&depthStencilStateDesc, &s_device->depth_stencil_state);
    if (FAILED(hr)) {
        LOG_ERROR_L;
        return false;
    }

    // Setup rasterizer state.
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterizerDesc.AntialiasedLineEnable = s_device->msaa;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = FALSE;
    rasterizerDesc.MultisampleEnable = s_device->msaa;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;

    // Create the rasterizer state object.
    hr = s_device->device->CreateRasterizerState(&rasterizerDesc, &s_device->rasterizer_state);
    if (FAILED(hr)) {
        LOG_ERROR_L;
        return false;
    }

    // viewport
    D3D11_VIEWPORT vp;
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    s_device->device_context->RSSetViewports(1, &vp);

    // hello atipls ive done d11 in leonard 2 how about you

    return true;
}

void dx11renderer::shutdown() {
    SAFE_RELEASE(s_device->swap_chain);
    SAFE_RELEASE(s_device->renderer_target_view);
    SAFE_RELEASE(s_device->depth_stencil_view);
    SAFE_RELEASE(s_device->device_context);

#ifdef _DEBUG
    // ref: http://masterkenth.com/directx-leak-debugging/
    // reporting live objects ref count
    ID3D11Debug *m_debugDevice = nullptr;
    HRESULT hr = s_device->device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void **>(&m_debugDevice));
    if (hr == S_OK) {
        hr = m_debugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
        SAFE_RELEASE(m_debugDevice);
    }
#endif

    SAFE_RELEASE(s_device->device);
}

void dx11renderer::resize(int width, int height) {
}

void dx11renderer::clear(const glm::vec4 &color) {
    const float colorf[4] = { color[0], color[1], color[2], color[3] };

    s_device->device_context->ClearRenderTargetView(s_device->renderer_target_view, colorf);
    s_device->device_context->ClearDepthStencilView(s_device->depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void dx11renderer::present(int32_t syncInterval, int32_t presentFlag) {
    if (s_device->swap_chain)
        s_device->swap_chain->Present(syncInterval, presentFlag);
}

#endif