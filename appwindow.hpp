#ifndef APPWINDOW_HPP_INCLUDED
#define APPWINDOW_HPP_INCLUDED 

#include "window.hpp"
#include "graphicsengine.hpp"
#include "swapchain.hpp"
#include "devicecontext.hpp"

class AppWindow : public Window
{
public:
	AppWindow() = default;
	~AppWindow() = default;

	// Hérité via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
};

#endif 