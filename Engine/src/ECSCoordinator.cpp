#include "ECSCoordinator.hpp"

ECSCoordinator::ECSCoordinator(){
    m_ComponentManager  = std::make_unique<ComponentManager>();
    m_EntityManager     = std::make_unique<EntityManager>();
    m_SystemManager     = std::make_unique<SystemManager>();
    m_EventManager      = std::make_unique<EventManager>();
    m_SceneManager      = std::make_unique<SceneManager>();

    m_State             = GAME_STATE::MENU;
}

void ECSCoordinator::Init()
{
    m_SceneManager->InitMenu();
    // cout << "In ECSCoordinator with address: "<< &m_SceneManager << endl;
    // m_SceneManager->InitEditor();
    // m_SceneManager->InitGame();
}

void ECSCoordinator::Update()
{
    // menu state required
    m_SpriteSystem->Update();
    m_InputSystem->Update();

    if (m_State == GAME_STATE::GAME)
    {
        // if (m_PlayerControllerSystem != nullptr)
        // {
        //     // Debug::PrintMessage("Update m_PlayerControllerSystem in ECS");
        //     m_PlayerControllerSystem->Update();
        // }
        
        // cout << "Entered ECSCoordinator::Update() with GAME_STATE::GAME " << std::endl;

        // if (m_PlayerControllerSystem != nullptr)
        // {
        //     m_PlayerControllerSystem->Update();
        // }
        if (m_InputSystem != nullptr)
        {
            m_InputSystem->Update();
        }

        if(m_CameraSystem != nullptr)
        {
            m_CameraSystem->Update();
        }

        if (m_PhysicsManagerSystem != nullptr)
        {
            m_PhysicsManagerSystem->Update();
        }

        if (m_ScriptingSystem != nullptr)
        {
            m_ScriptingSystem->Update();
        }
    }

    if (m_State == GAME_STATE::EDITOR)
    {
        m_LevelEditorSystem->Update();
    }
}

void ECSCoordinator::Render()
{
    m_RenderSystem->Render();
}
