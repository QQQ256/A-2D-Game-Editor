#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

#include <TinyMath.hpp>

/// @brief SpriteComponent
struct Sprite{
	SDL_Texture*    m_Texture       =  nullptr;	
    SDL_Surface*    m_SpriteSheet   =  nullptr;
    SDL_Renderer*   m_Render        =  nullptr;
    SDL_Rect        m_Src;
	SDL_Rect        m_Dest;			// this is the position of a sprite
    int             m_Frame         = 0;
    int             m_CurrentFrame  = 0;
	int				m_SizeX			= 0;
	int				m_SizeY			= 0;
	unsigned int    mCurrentFrame{0};
};