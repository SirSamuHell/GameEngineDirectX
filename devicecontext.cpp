#include "devicecontext.hpp"
#include "swapchain.hpp"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context) : m_device{device_context}
{
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red, green, blue, alpha };
	m_device->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	return false;
}

bool DeviceContext::release()
{
	m_device->Release();
	delete this;
	return true;
}
