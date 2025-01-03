#pragma once

#include "include/Window.h"

// TODO Show this only for windows
#include <d3d11.h>
#include <DirectXMath.h>
namespace Creator
{
    class D3DContainer
    {
    public:
        D3DContainer();
        D3DContainer(const D3DContainer &);
        ~D3DContainer();

        bool Initialize(HWND, WindowParameters, float, float);
        void Shutdown();

        void BeginScene(float, float, float, float, float, float);
        void EndScene();

        ID3D11Device *GetDevice();
        ID3D11DeviceContext *GetDeviceContext();

        void GetProjectionMatrix(DirectX::XMMATRIX &);
        void GetWorldMatrix(DirectX::XMMATRIX &);
        void GetOrthoMatrix(DirectX::XMMATRIX &);

        void GetVideoCardInfo(char *, int &);

        void SetBackBufferRenderTarget();
        void ResetViewport();

    private:
        bool m_vsync_enabled;
        int m_videoCardMemory;
        char m_videoCardDescription[128];
        IDXGISwapChain *m_swapChain;
        ID3D11Device *m_device;
        ID3D11DeviceContext *m_deviceContext;
        ID3D11RenderTargetView *m_renderTargetView;
        ID3D11Texture2D *m_depthStencilBuffer;
        ID3D11DepthStencilState *m_depthStencilState;
        ID3D11DepthStencilView *m_depthStencilView;
        ID3D11RasterizerState *m_rasterState;
        DirectX::XMMATRIX m_projectionMatrix;
        DirectX::XMMATRIX m_worldMatrix;
        DirectX::XMMATRIX m_orthoMatrix;
        D3D11_VIEWPORT m_viewport;
    };
}