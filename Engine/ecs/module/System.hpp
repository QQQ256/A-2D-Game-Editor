#pragma once
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif


#include "Common.hpp"
#include "Debug.hpp"
#include "Event.hpp"

#include "ResourceManager.hpp"

#include <set>

// TODO: tilemap, collision, animation, 

/// @brief The base class of all sub-systems, use to handle game logics


class ISystem{
public:
    set<Entity> m_Entities;

	// TODO:将其他系统中的GAME_STATE都删掉
	GAME_STATE	m_State;

	virtual void Init() = 0;
	
    virtual void Update() = 0;
};