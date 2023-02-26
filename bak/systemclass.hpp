//////////////////////////////////////////////
// Filename: systemclass.hpp               //
////////////////////////////////////////////
#ifndef SYSTEMCLASS_HPP_INCLUDED
#define SYSTEMCLASS_HPP_INCLUDED 

// Directive de preprocesseur 
#define WIN32_LEAN_AND_MEAN // Permet d'allegez de r�duire les fichier d'en-t�te C++ en chargeant que les biblioth�ques les plus utilis� permet d'acc�ler

// Inclusion d'en-t�tes 
#include <Windows.h>

// Inclusion d'en t�tes personnel 

#include "inputclass.hpp"
#include "graphicsclass.hpp"


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&) = delete;
	~SystemClass() = default;

	BOOL Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	BOOL Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
};

// Prototypes de fonction
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Variable Global 
static SystemClass* ApplicationHandle = nullptr;

#endif