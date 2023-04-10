#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

enum UIType
{
	MENU_BUTTON,
	MENU_IMAGE,
	EDITOR_IMAGE,
	EDITOR_BUTTON,
	GAME_IMAGE,
	GAME_BUTTON
};

struct UIComponent
{
    // SDL_Rect 	rect;
	UIType 		m_Type;
};
