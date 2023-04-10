#include "ECSCoordinator.hpp"
#include "Binding.hpp"

extern ECSCoordinator coordinator;

void ScriptingSystem::Init() 
{
    std::cout << "ScriptingSystem::Init() called" << std::endl;

    if(Binding::L == NULL) 
    {
        std::cout << "ScriptingSystem::Init() entered Binding::L == NULL" << std::endl;
        Binding::L = luaL_newstate();
        if(Binding::L == NULL) {
            cout << "Unable to initialize the scripting system." << endl;
            return;
        }
        luaL_openlibs(Binding::L);

        const luaL_Reg regFunctions[] = {
            {"get_transform_component", Binding::lua_GetTransformComponent},
            {"get_entity_by_name", Binding::lua_GetEntityByName},
            // {"add_input_component", Binding::lua_AddInputComponent},
            // {"remove_input_component", Binding::lua_RemoveInputComponnet},
            {"get_script_ccomponent", Binding::lua_GetScriptComponent},
            {"get_horizontal_input", Binding::lua_GetHorizontalInput},
            {"get_vertical_input", Binding::lua_GetVerticalInput},
            { NULL, NULL } // End marker
        };

        luaL_newlib(Binding::L, regFunctions);
        lua_setglobal(Binding::L, "engine");
        
        // register meta tables for all possible component
        Binding::RegisterVec2DComponentMetatable(Binding::L);
        Binding::RegisterTransformComponentMetatable(Binding::L);

        // give access of entity list to Bind class
        Binding::entities = &m_Entities;
    }

}

void ScriptingSystem::Shutdown() {
    std::cout << "ScriptingSystem::Shutdown() called" << std::endl;
    if(Binding::L != NULL) {
        lua_close(Binding::L);
    }
}

void ScriptingSystem::Update() {
    std::cout << "ScriptingSystem::Update() called" << std::endl;
    for(auto& entity : m_Entities) {
        if(coordinator.HashComponent<Script>(entity)) {
            auto& script = coordinator.GetComponent<Script>(entity);
            Binding::curEntity = entity;
            Execute(script.scriptPath.c_str());
        }
    }
}

void ScriptingSystem::Execute(const char * s) {

    std::cout << "ScriptingSystem::Execute()" << std::endl;
    std::cout << "s.scriptPath: " <<  s << std::endl;

    if(Binding::CheckLua(Binding::L, luaL_dofile(Binding::L, s))) {
        lua_pcall(Binding::L, 0, 0, 0);
    }
}


