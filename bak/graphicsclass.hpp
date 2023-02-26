//////////////////////////////////////////////
// Filename: graphicsclass.hpp             //
////////////////////////////////////////////
#ifndef GRAPHICSCLASS_HPP_INCLUDED
#define GRAPHICSCLASS_HPP_INCLUDED 


// Includes 
#include <Windows.h>

// Constants globals 
constexpr BOOL FULL_SCREEN = FALSE;
constexpr BOOL VSYNC_ENABLED = TRUE;
const FLOAT SCREEN_DEPTH = 1000.0f;
const FLOAT SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&) = delete;
	~GraphicsClass() = default;

	BOOL Initialize(int, int, HWND);
	void Shutdown();
	BOOL Frame();
private:
	BOOL Render();

};


#endif