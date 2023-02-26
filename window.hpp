#ifndef WINDOW_HPP_INCLUDED 
#define WINDOW_HPP_INCLUDED 

#include <Windows.h>

class Window
{
public:
	Window() = default;
	~Window() = default;

	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);


	// Events 
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

protected:
	HWND m_hwnd;
	LPCWSTR m_szClassname;
	bool m_isRun;

};

#endif 