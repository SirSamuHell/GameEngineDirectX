#ifndef SWAPCHAIN_HPP_INCLUDED
#define SWAPCHAIN_HPP_INCLUDED

#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain() = default;

	bool init(HWND hwnd, UINT width, UINT height);
	bool present(bool vsync);
	bool release();
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
private:
	friend class DeviceContext;
};


#endif 