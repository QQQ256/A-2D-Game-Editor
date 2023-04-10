#include "Binding.hpp"
#include "ECSCoordinator.hpp"

using namespace std;

extern ECSCoordinator coordinator;

Entity Binding::curEntity;
lua_State* Binding::L = nullptr;
set<Entity>* Binding::entities = nullptr;

bool Binding::CheckLua(lua_State* L, int state) {
    if (state != LUA_OK) {
        // print error message
        cout << lua_tostring(L, -1) << endl;
        return false;
    }
    return true;
}

int Binding::lua_GetEntityByName(lua_State* L) {
    cout << "calling: [C++] lua_GetEntityByName(...)" << endl;
    if(entities == NULL || entities->size() == 0) {
        return 0;
    }
    const char *requestName = luaL_checkstring(L, 1);
    for(auto& entity : *entities) {
        if(coordinator.HashComponent<Name>(entity)) {
            auto& name = coordinator.GetComponent<Name>(entity);
            if(strcmp(name.theName.c_str(), requestName) == 0) {
                lua_pushinteger(L, static_cast<lua_Integer>(entity));
                return 1;
            }
        }
    }
    return 0;
}

int Binding::Vec2DIndex(lua_State* L) {
    cout << "calling: [C++] Vec2DIndex(...)" << endl;
    Vec2D* vec = (Vec2D*)lua_touserdata(L, 1);
    const char *key = luaL_checkstring(L, 2);

    if (strcmp(key, "x") == 0) {
        lua_pushinteger(L, vec->x);
        return 1;
    } else if (strcmp(key, "y") == 0) {
        lua_pushinteger(L, vec->y);
        return 1;
    }

    return 0;
}

int Binding::Vec2DNewIndex(lua_State* L) {
    cout << "calling: [C++] Vec2DAssign(...)" << endl;
    Vec2D* vec = (Vec2D*)lua_touserdata(L, 1);
    const char *key = luaL_checkstring(L, 2);
    float value = (float)luaL_checknumber(L, 3);

    if (strcmp(key, "x") == 0) {
        vec->x = value;
        return 0;
    } else if (strcmp(key, "y") == 0) {
        vec->y = value;
        return 0;
    }

    return 0;
}

int Binding::Vec2DGC(lua_State* L) {
    cout << "calling: [C++] Vec2DGC(...)" << endl;
    Vec2D* vec = (Vec2D*)lua_touserdata(L, 1);
    delete vec;
    return 0;
}

void Binding::RegisterVec2DComponentMetatable(lua_State* L) {
    luaL_newmetatable(L, "Vec2D");
    lua_pushcfunction(L, Vec2DGC);
    lua_setfield(L, -2, "__gc");
    lua_pushcfunction(L, Vec2DIndex);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, Vec2DNewIndex);
    lua_setfield(L, -2, "__newindex");
    lua_pop(L,1);
}

int Binding::lua_GetTransformComponent(lua_State* L) {
    cout << "calling: [C++] lua_GetTransformComponent(...)" << endl;
    int paramNum = lua_gettop(L);
    Transform* transform;
    if(paramNum == 0) {
        transform = &(coordinator.GetComponent<Transform> (Binding::curEntity));
    } else {
        Entity requestEntity = static_cast<Entity>(lua_tointeger(L, 1));
        transform = &(coordinator.GetComponent<Transform> (requestEntity));
    }

    if(transform == nullptr) {
        return 0;
    }
    cout << "[C++] transform.position.X:" << transform->position.x << endl;
    // cout << "[C++] transform.position.Y:" << transform->position.y << endl;
    lua_pushlightuserdata(L, transform);
    luaL_getmetatable(L, "Transform");
    lua_setmetatable(L, -2);
    return 1;
}

int Binding::TransformIndex(lua_State *L) {
    cout << "calling: [C++] TransformIndex(...)" << endl;
    Transform* transform = (Transform*)lua_topointer(L, 1);
    const char *key = luaL_checkstring(L, 2);

    if (std::strcmp(key, "position") == 0) {
        cout << "[C++] position.X:" << transform->position.x << endl;
        lua_pushlightuserdata(L, &(transform->position));
        // register new meta table
        luaL_getmetatable(L, "Vec2D");
        lua_setmetatable(L, -2);
        return 1;
    }

    return 0;
}

int Binding::TransformGC(lua_State* L) {
    cout << "calling: [C++] TransformGC(...)" << endl;
    Transform* transform = (Transform*)lua_touserdata(L, 1);
    delete transform;
    return 0;
}

void Binding::RegisterTransformComponentMetatable(lua_State* L) {
    luaL_newmetatable(L, "Transform");
    lua_pushcfunction(L, TransformGC);
    lua_setfield(L, -2, "__gc");
    lua_pushcfunction(L, TransformIndex);
    lua_setfield(L, -2, "__index");
    lua_pop(L,1);
}

// int Binding::lua_AddInputComponent(lua_State* L) {
//     cout << "calling: [C++] lua_AddInputComponent(...)" << endl;

//     int paramNum = lua_gettop(L);
//     if(paramNum == 0) {

//         if(coordinator.HashComponent<InPut>(Binding::curEntity)) {
//             lua_pushboolean(L, true);
//             return 1;
//         }

//         coordinator.AddComponent(Binding::curEntity, InPut{});
//         if(coordinator.HashComponent<InPut>(Binding::curEntity)) {
//             lua_pushboolean(L, true);
//         } else {
//             lua_pushboolean(L, false);
//         }
//     } else {
//         Entity requestEntity = static_cast<Entity>(lua_tointeger(L, 1));

//         if(coordinator.HashComponent<InPut>(requestEntity)) {
//             lua_pushboolean(L, true);
//             return 1;
//         }

//         coordinator.AddComponent(requestEntity, InPut{});
//         if(coordinator.HashComponent<InPut>(requestEntity)) {
//             lua_pushboolean(L, true);
//         } else {
//             lua_pushboolean(L, false);
//         }
//     }

//     return 1;
// }

// int Binding::lua_RemoveInputComponnet(lua_State* L) {
//     cout << "calling: [C++] lua_RemoveInputComponent(...)" << endl;
//     int paramNum = lua_gettop(L);
//     if(paramNum == 0) {

//         if(!coordinator.HashComponent<InPut>(Binding::curEntity)) {
//             lua_pushboolean(L, true);
//             return 1;
//         }

//         coordinator.RemoveComponent<InPut>(Binding::curEntity);
//         if(!coordinator.HashComponent<InPut>(Binding::curEntity)) {
//             lua_pushboolean(L, true);
//         } else {
//             lua_pushboolean(L, false);
//         }
//     } else {
//         Entity requestEntity = static_cast<Entity>(lua_tointeger(L, 1));

//         if(!coordinator.HashComponent<InPut>(requestEntity)) {
//             lua_pushboolean(L, true);
//             return 1;
//         }

//         coordinator.RemoveComponent<InPut>(requestEntity);
//         if(!coordinator.HashComponent<InPut>(requestEntity)) {
//             lua_pushboolean(L, true);
//         } else {
//             lua_pushboolean(L, false);
//         }
//     }

//     return 1;
// }

// Return not the component but the sciprt path
int Binding::lua_GetScriptComponent(lua_State*) {
    cout << "calling: [C++] lua_GetScriptComponent(...)" << endl;
    Script* script;
    Entity requestEntity = static_cast<Entity>(lua_tointeger(L, 1));
    if(!coordinator.HashComponent<Script>(requestEntity)) {
        cout << "No script binded on this entity." << endl;
        return 0;
    }

    script = &(coordinator.GetComponent<Script> (requestEntity));

    if(script == nullptr) {
        cout << "Error: cannot get corresponding script component" << endl;
        return 0;
    }
    
    lua_pushstring(L, (script->scriptPath).c_str());
    return 1;
}

int Binding::lua_GetHorizontalInput(lua_State* L) {
    cout << "calling: [C++] lua_GetHorizontalInput(...)" << endl;
    lua_pushinteger(L, Controlling::horizontalInput);
    return 1;
}

int Binding::lua_GetVerticalInput(lua_State*) {
    cout << "calling: [C++] lua_GetVerticalInput(...)" << endl;
    lua_pushinteger(L, Controlling::verticalInput);
    return 1;
}