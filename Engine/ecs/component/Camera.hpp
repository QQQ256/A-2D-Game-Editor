#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

struct Camera
{
    SDL_FRect   viewport;
    int         cameraX; // 摄像机位置
    int         cameraY;
    int         viewportWidth; // 摄像机渲染区域大小
    int         viewportHeight; 
    int         worldWidth; // 游戏地图大小
    int         worldHeight; // 
};
