#include "systemclass.hpp"


 
SystemClass::SystemClass() : m_Input{ nullptr }, m_Graphics{ nullptr }
{

}
 
 
BOOL SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	BOOL bResult;

	// Taille de la fenêtre 
	screenWidth = 0;
	screenHeight = 0;

	// Initialize la fenêtre API Win32
	InitializeWindows(screenWidth, screenHeight);


	// Création de l'objet Input permettant de gérer les entrée clavier 
	m_Input = new InputClass;

	if (!m_Input)
		return FALSE;

	// Initialize l'objet input 
	m_Input->Initialize();

	// Création de l'objet Graphics permettant de gérer l'affichage 
	m_Graphics = new GraphicsClass;

	if (!m_Graphics)
		return FALSE;

	bResult = m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);

	if (!bResult)
		return FALSE;

	return TRUE;
}

void SystemClass::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
	}

	if (m_Input)
	{
		//m_Input->Shutdown();
		delete m_Input;
	}

	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	BOOL done, result;

	ZeroMemory(&msg, sizeof(msg));

	done = FALSE;

	while (!done)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = TRUE;
		}
		else
		{
			result = Frame();
			if (!result)
				done = FALSE;
		}
	}
}

BOOL SystemClass::Frame()
{
	BOOL bResult;

	if (m_Input->IsKeyDown(VK_ESCAPE))
		return FALSE;
	
		 
	bResult = m_Graphics->Frame();

	if (!bResult)
		return FALSE;
	return TRUE;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		{
			m_Input->KeyDown(wParam);
			return 0;
		}
	case WM_KEYUP:
		{
			m_Input->KeyUp(wParam);
			return 0;
		}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	 
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;

	// Récuperer l'instance de l'application 
	m_hInstance = GetModuleHandle(nullptr);
	m_applicationName = L"Initiation a DirectX 11";

	// Initialisation des paramètre de la fenêtre win32
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Enregistre la classe de la fenêtre 
	RegisterClassEx(&wc);

	// Hauteur et largeur 
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if (FULL_SCREEN)
	{
		ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));
		dmScreenSettings.dmSize = sizeof(DEVMODE);
		dmScreenSettings.dmPelsWidth = screenWidth;
		dmScreenSettings.dmPelsHeight = screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = 0, posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Crée la fenêtre en récuperant le pointeur de fenêtre 
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP | WS_CAPTION | WS_SYSMENU, posX, posY, screenWidth, screenHeight, nullptr, nullptr, m_hInstance, nullptr);

	// Affiche la fenêtre 
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	//ShowCursor(FALSE);
	
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(TRUE);

	if (FULL_SCREEN)
		ChangeDisplaySettings(nullptr, 0);
	
	// Supprime la fenêtre 
	DestroyWindow(m_hWnd);
	UnregisterClass(m_applicationName, m_hInstance);


	ApplicationHandle = nullptr;

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hWnd, uMsg, wParam, lParam);
	}
}
