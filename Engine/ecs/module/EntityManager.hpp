#pragma once

#include <iostream>
#include <queue>
#include <array>
#include <assert.h>

#include "Common.hpp"


using namespace std;

/// @brief manage all entities
// each entity has a signature
class EntityManager{
public:

    /// @brief add all entities to the queue
    EntityManager();

    /// @brief 
    /// @return an ID of an entity
    Entity CreateEntity();

    void DestroyEntity(Entity entity);

    void SetSignature(Entity entity, Signature signature);

    Signature GetSignatureByEntity(Entity entity);

private:

    uint32_t                           m_existedEntityCount {};

    queue<Entity>                      m_entityQueue {};

    array<Signature, MAX_EntityCount>  m_Signatures {};
};
