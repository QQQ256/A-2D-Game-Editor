#include "ECSCoordinator.hpp"

ECSCoordinator::ECSCoordinator(){
    m_ComponentManager  = std::make_unique<ComponentManager>();
    m_EntityManager     = std::make_unique<EntityManager>();
    m_SystemManager     = std::make_unique<SystemManager>();
    m_EventManager      = std::make_unique<EventManager>();

    m_State             = GAME_STATE::EDITOR;
}