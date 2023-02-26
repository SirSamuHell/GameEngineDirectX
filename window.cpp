#include "window.hpp"

Window* window = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
		// Evenement lors de la création de la fenêtre 
		window->setHWND(hwnd);
		window->onCreate();
		break;
	case WM_DESTROY:
		// Evenement lors de la déstruction de la fenêtre 
		window->onDestroy();
		PostQuitMessage(0); 

		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

bool Window::init()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	m_szClassname = L"DirectX-Engine";

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = wc.hIcon;
	wc.hInstance = nullptr;
	wc.lpszClassName = m_szClassname;
	wc.lpszMenuName = nullptr;
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wc))
		return false;
 
	if (!window)
		window = this;

	m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, m_szClassname, L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, nullptr, nullptr, nullptr, nullptr);

	if (!m_hwnd)
		return false;
	

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);
 
	m_isRun = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->onUpdate();
	Sleep(0);

	return false;
}

bool Window::release()
{
	if (DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool Window::isRun()
{
	return m_isRun;
}

RECT Window::getClientWindowRect()
{
	RECT rc;

	GetClientRect(this->m_hwnd, &rc);

	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
	m_isRun = false;
}


