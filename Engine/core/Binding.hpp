#pragma once

#include "Common.hpp"
#include <set>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

// Binding configuration
class Binding {
public:
    // utilities
    static bool CheckLua(lua_State*, int);

    // get methods
    static int lua_GetEntityByName(lua_State*);

    // data types
    // Vec2D
    static int Vec2DIndex(lua_State*);
    static int Vec2DNewIndex(lua_State*);
    static int Vec2DGC(lua_State*);
    static void RegisterVec2DComponentMetatable(lua_State*);

    // components
    // Transform component
    static int lua_GetTransformComponent(lua_State*);
    static int TransformIndex(lua_State*);
    static int TransformGC(lua_State*);
    static void RegisterTransformComponentMetatable(lua_State*);

    // Input component
    // static int lua_AddInputComponent(lua_State*);
    // static int lua_RemoveInputComponnet(lua_State*);

    // Script component (Actually get the script path)
    static int lua_GetScriptComponent(lua_State*);

    // Get Input
    static int lua_GetHorizontalInput(lua_State*);
    static int lua_GetVerticalInput(lua_State*);

    // entity list
    static set<Entity> *entities;
    // the entity in process
    static Entity curEntity;
    // Lua Stack
    static lua_State *L;
};