#include <Windows.h>

#include "systemclass.hpp"
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	SystemClass* hSystem{nullptr};
 
	hSystem = new SystemClass;

	if (!hSystem)
	{
		MessageBoxA(nullptr, "Error", "Initialize SystemClass failed", MB_ICONERROR | MB_OK);
		return EXIT_FAILURE;
	}

	BOOL bResult = hSystem->Initialize();

	if (bResult)
	{
		hSystem->Run();
	}

	hSystem->Shutdown();
	delete hSystem;
 
	return EXIT_SUCCESS;
}