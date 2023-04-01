#pragma once

#include "ECSCoordinator.hpp"

extern ECSCoordinator coordinator;

class ECSFactory{
public:
    void Init();

    void InitComponents();

    void InitSybSystems();

    void InitEntities();

private:
    void CreatePlayerFromJSON();

    void CreateTilemapFromJSON();

    void CreateEnemyFromJSON();

    void CreateCamera();

    void AddEntity(ENTITY_TYPE);

    void AddEnemyToJSON(Enemy enemyData);

    void CreateEditorUI();

    void CreateButton(Entity entity, const string& btnName, const json& buttonConfig);
};