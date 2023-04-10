#pragma once

#include "ECSCoordinator.hpp"

extern ECSCoordinator coordinator;

class ECSFactory{
public:
    ECSFactory();

    void InitComponents();

    void InitMenu();

    void InitEditor();

    void InitGame();

private:
    void CreateTestEntityFromJSON();

    void CreateTestEntitySecondFromJSON();

    void CreatePlayerFromJSON();

    void CreateTilemapFromJSON();

    void CreateEnemyFromJSON();

    void CreateCamera();

    void AddEntity(ENTITY_TYPE);

    void AddEnemyToJSON(Enemy enemyData);

    void CreateMenuUI();

    void CreateEditorUI();

    void CreateUIElement(Entity entity, const string& btnName, const json& buttonConfig, GAME_STATE state, UIType uiType, RENDER_ORDER renderOrder);

    /// @brief register common system for game and editor
    void RegisterCommonSystem();

    void RegisterMenuSystem();

    void RegisterGameSystem();
    
    void RegisterMenuEntity();

    /// @brief register common entity for game and editor
    void RegisterCommonEntity();

    bool m_IsUIConfigFileExist;

    bool m_IsConfigFileExist;

    json m_Config;
    json m_ImageConfig;
    json m_ButtonConfig;
    json m_CameraConfig;
    // json m_ComponentConfig;

    bool m_IsInitEditorSystem;

    bool m_IsInitGameSystem;

    bool m_IsInitComponents;

    bool m_IsInitCommonEntity;

    bool m_IsInitCamera;
};