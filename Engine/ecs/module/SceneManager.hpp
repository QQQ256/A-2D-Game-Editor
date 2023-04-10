#pragma once

#include "Common.hpp"
#include <memory>

class ECSFactory;

class SceneManager{
public:
    SceneManager();

    void EnterState(GAME_STATE newState);

    /// @brief load resource in this state
    /// @param state 
    void InitState(GAME_STATE state);

    /// @brief release resource in this state
    /// @param state 
    void CleanupState(GAME_STATE state);

    void InitMenu();

    void InitEditor();

    void InitGame();

    void CleanupMenu();

    void CleanupEditor();

    void CleanupGame();

private:

    GAME_STATE                  m_CurrentState;

    shared_ptr<ECSFactory>      m_ECSFactory;
};