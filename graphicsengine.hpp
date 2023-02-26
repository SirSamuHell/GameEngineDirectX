#ifndef GRAPHICSENGINE_HPP_INCLUDED
#define GRAPHICSENGINE_HPP_INCLUDED

#include <d3d11.h>

class SwapChain;

class GraphicsEngine
{
public:
	GraphicsEngine() = default;
	~GraphicsEngine() = default;

	bool init();
	bool release();

	static GraphicsEngine* get();

	SwapChain* createSwapChain();

private:
	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_d3d_feature_level;
	ID3D11DeviceContext* m_imm_context;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	friend class SwapChain;
};

#endif 