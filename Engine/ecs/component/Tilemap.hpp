#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

struct Tilemap
{
    // Dimensions of our TileMap and individual tiles.
    // Used for spiltting up the sprite sheet
    int m_Rows;
    int m_Cols;      
    // How big each tile is.
    int m_TileWidth;
    int m_TileHeight;
    // size of our tilemap
    int m_MapX;
    int m_MapY; 
    int m_ScaleFactor;
    // Where our TileMap is rendered
    // An SDL Surface contains pixel data to draw our TileMap
    SDL_Surface *m_TileSpriteSheet;
    SDL_Texture *m_Texture;
    SDL_Texture *m_FullTexture;
    // Stores our tile types
    // int* m_Tiles;
    vector<int> m_Tiles;
    SDL_Rect    m_Src;
    SDL_Rect    m_Dest;
};

