#pragma once

// managers
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "EventManager.hpp"

// subsystems
#include "PlayerControllerSystem.hpp"
#include "SpriteSystem.hpp"
#include "TilemapSystem.hpp"
#include "RenderSystem.hpp"
#include "SDLGraphicsSystem.hpp"
#include "InputSystem.hpp"
#include "LevelEditorSystem.hpp"
#include "UISystem.hpp"
#include "CameraSystem.hpp"

// components
#include "InPut.hpp"
#include "Player.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Tilemap.hpp"
#include "Renderer.hpp"
#include "Enemy.hpp"
#include "Editor.hpp"
#include "UIButton.hpp"
#include "Camera.hpp"

#include "FileReader.hpp"

class ECSCoordinator{
public:
    ECSCoordinator();

    // --- Component Manager ---

    template<typename T>
    void RegisterComponent();

    template<typename T>
    ComponentType GetComponentTypeUniqueIndex();

    template<typename T>
    void AddComponent(Entity entity, T component);

    template<typename T>
    void RemoveComponent(Entity entity);

    template<typename T>
    T& GetComponent(Entity entity);

    // --- Entity Manager ---
    Entity CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}

    // TODO: 加destroy entity的方法，直接调ECS中的函数
    // void DestroyEntity(Entity entity);

    // --- System Manager ---
    template<typename T>
    shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSignature(Signature signature);

    template<typename T>
    bool HashComponent(Entity entity);

    // --- Event Manager ---
    inline void AddEventListener(EVENT eventId, function<void(Event&)> const& callBack);

    inline void RemoveEventListener(EVENT eventId, function<void(Event&)> const& callBack);

    inline void TriggerEvent(Event& event);

    inline void TriggerEvent(EVENT eventId);


    shared_ptr<RenderSystem>                    m_RenderSystem;
    shared_ptr<PlayerControllerSystem>          m_PlayerControllerSystem;
    shared_ptr<SpriteSystem>                    m_SpriteSystem;
    shared_ptr<TilemapSystem>                   m_TilemapSystem;
    shared_ptr<SDLGraphicsSystem>               m_SDLGraphicsSystem;
    shared_ptr<InputSystem>                     m_InputSystem;
    shared_ptr<LevelEditorSystem>               m_LevelEditorSystem;
    shared_ptr<UISystem>                        m_UISystem;
    shared_ptr<CameraSystem>                    m_CameraSystem;

    GAME_STATE                                  m_State;
private:
    
    unique_ptr<ComponentManager>                m_ComponentManager;
    unique_ptr<EntityManager>                   m_EntityManager;
    unique_ptr<SystemManager>                   m_SystemManager;
    unique_ptr<EventManager>                    m_EventManager;
};


template<typename T>
void ECSCoordinator::RegisterComponent(){
    m_ComponentManager->RegisterComponent<T>();
}

template<typename T>
ComponentType ECSCoordinator::GetComponentTypeUniqueIndex(){
    return m_ComponentManager->GetComponentTypeUniqueIndex<T>();
}

template<typename T>
void ECSCoordinator::AddComponent(Entity entity, T component){
    // bind the componet with entity
    m_ComponentManager->AddComponent<T>(entity, component);

    // get signature via entity id
    auto signature = m_EntityManager->GetSignatureByEntity(entity);

    // set signature in bitset to show which component is TRUE now
    signature.set(this->GetComponentTypeUniqueIndex<T>(), true);

    m_EntityManager->SetSignature(entity, signature);

    m_SystemManager->EntitySignatureChanged(entity, signature);

}

template<typename T>
void ECSCoordinator::RemoveComponent(Entity entity){
    m_ComponentManager->RemoveComponent<T>(entity);

    auto signature = m_EntityManager->GetSignatureByEntity(entity);
    signature.set(this->GetComponentTypeUniqueIndex<T>(), false);
    m_EntityManager->SetSignature(entity, signature);

    m_SystemManager->EntitySignatureChanged(entity, signature);
}

// void ECSCoordinator::DestroyEntity(Entity entity){
//     m_EntityManager->DestroyEntity(entity);
    
//     m_ComponentManager->DestroyEntity(entity);

//     m_SystemManager->DestroyEntity(entity);
// }

/// @brief 基于entity的ID查找挂载再它身上的组件ID
/// @tparam T 组件类型
/// @param entity 你要查找的entity
/// @return 
template<typename T>
T& ECSCoordinator::GetComponent(Entity entity){
    return m_ComponentManager->GetComponent<T>(entity);
}

template<typename T>
shared_ptr<T> ECSCoordinator::RegisterSystem(){
    return m_SystemManager->RegisterSystem<T>();
}

template<typename T>
void ECSCoordinator::SetSignature(Signature signature){
    m_SystemManager->SetSignature<T>(signature);
}

template<typename T>
bool ECSCoordinator::HashComponent(Entity entity){
    return m_ComponentManager->HasComponent<T>(entity);
}

// ////////  --- event system ---  ///////////
inline void ECSCoordinator::AddEventListener(EVENT eventId, function<void(Event&)> const& callBack){
    m_EventManager->AddListener(eventId, callBack);
}

inline void ECSCoordinator::RemoveEventListener(EVENT eventId, function<void(Event&)> const& callBack){
    m_EventManager->RemoveListener(eventId, callBack);
}

inline void ECSCoordinator::TriggerEvent(Event& event){
    m_EventManager->Trigger(event);
}

inline void ECSCoordinator::TriggerEvent(EVENT eventId){
    m_EventManager->Trigger(eventId);
}