#include "SceneManager.hpp"
#include "ECSFactory.hpp"

SceneManager::SceneManager()
{
    m_CurrentState = GAME_STATE::MENU;

    m_ECSFactory   = make_shared<ECSFactory>();
}

void SceneManager::EnterState(GAME_STATE newState)
{
    CleanupState(m_CurrentState);

    m_CurrentState = newState;
    coordinator.m_State = newState;

    InitState(m_CurrentState);
}

void SceneManager::InitState(GAME_STATE state)
{
    switch (state)
    {
    case GAME_STATE::MENU:
        InitMenu();
        break;
    case GAME_STATE::EDITOR:
        InitEditor();
        break;
    case GAME_STATE::GAME:
        InitGame();
        break;
    }
}

void SceneManager::CleanupState(GAME_STATE state)
{
     switch (state)
    {
    case GAME_STATE::MENU:
        CleanupMenu();
        break;
    case GAME_STATE::EDITOR:
        CleanupEditor();
        break;
    case GAME_STATE::GAME:
        CleanupGame();
        break;
    }
}

void SceneManager::InitMenu()
{
    m_ECSFactory->InitMenu();
}

void SceneManager::InitEditor()
{
    cout << "init editor with state: "<< m_CurrentState;
    m_ECSFactory->InitEditor();
    // 这里写你要修改什么东西，子系统内基于m_CurrentState去判断一些赋值
    coordinator.m_RenderSystem->EnterState(m_CurrentState);
    coordinator.m_CameraSystem->EnterState(m_CurrentState);
}

void SceneManager::InitGame()
{
    cout << "init game with state: "<< m_CurrentState;
    m_ECSFactory->InitGame();
    coordinator.m_RenderSystem->EnterState(m_CurrentState);
    coordinator.m_CameraSystem->EnterState(m_CurrentState);
}

void SceneManager::CleanupMenu()
{
    Debug::PrintMessage("CleanupMenu");
    // TODO: 在切换场景的时候，应该删除首页中所有的entity
    coordinator.m_RenderSystem->Clear();
}

void SceneManager::CleanupEditor()
{
    Debug::PrintMessage("CleanupEditor");
    //TODO: 问题：到底要释放哪些资源啊。。这里还没写清除
    // coordinator.m_RenderSystem->Clear();
    // m_ECSFactory->m_IsInitGameSystem = false; 
}

void SceneManager::CleanupGame()
{
    Debug::PrintMessage("CleanupGame");
    // coordinator.m_RenderSystem->Clear();  
}
