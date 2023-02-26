#include "graphicsengine.hpp"
#include "swapchain.hpp"

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] = {
		D3D_DRIVER_TYPE_HARDWARE, // GPU 
		D3D_DRIVER_TYPE_WARP, // CPU 
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_level[] = { 
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	HRESULT res;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
	{
		res = D3D11CreateDevice(nullptr, driver_types[driver_type_index], nullptr, 0, feature_level, num_driver_types, D3D11_SDK_VERSION, &m_d3d_device, &m_d3d_feature_level, &m_imm_context);
		
		if (SUCCEEDED(res))
			break;
	}
 
	if (FAILED(res))
		return false;


	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgi_device));
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_dxgi_adapter));
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgi_factory));
 	 
	return true;
}

bool GraphicsEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_imm_context->Release();
	m_d3d_device->Release();
	return true;
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;

	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain;
}
