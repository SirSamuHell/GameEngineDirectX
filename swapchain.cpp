#include "swapchain.hpp"
#include "graphicsengine.hpp"


bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device = GraphicsEngine::get()->m_d3d_device;
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.BufferCount = 1; // front buffer et le back buffer (double buffering)
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
 
	// Cr�ation de la swap chain
	HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
		return false;

	ID3D11Texture2D* buffer = nullptr;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));

	if (FAILED(hr))
		return false;

	device->CreateRenderTargetView(buffer, nullptr, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
		return false;

	return true;
}

bool SwapChain::present(bool vsync)
{
	m_swap_chain->Present(vsync, 0);

	return false;
}

bool SwapChain::release()
{
	m_swap_chain->Release();
	delete this;
	return true;
}
