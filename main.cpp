#include "appwindow.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	AppWindow app;
 
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();

		}
	}

	return 0;
}