#ifndef SWAPCHAIN_HPP_INCLUDED
#define SWAPCHAIN_HPP_INCLUDED

#include <d3d11.h>

class SwapChain
{
public:
	SwapChain() = default;
	~SwapChain() = default;

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
private:
	IDXGISwapChain* m_swap_chain;
};


#endif 