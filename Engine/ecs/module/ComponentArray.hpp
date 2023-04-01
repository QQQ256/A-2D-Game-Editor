#pragma once

#include <array>
#include <unordered_map>
#include <assert.h>

#include "Common.hpp"

using namespace std;

/// @brief Use an interface to call subclass's destroy function
class IComponentArray{
public:
    virtual void ElimiateEntity(Entity entity) = 0;
    virtual ~IComponentArray() = default;
};

/// @brief A component array only store one type of the component
template<typename T>
class ComponentArray : public IComponentArray{
public:

    /// @brief Destroy a gameObject ID
    /// @param id GameObjectID
    void ElimiateEntity(Entity entity) override{
        auto iter = m_Entity_Index_Map.find(entity);
        if(iter != m_Entity_Index_Map.end()){
            RemoveEntityFromArray(entity);
        }
    }

    /// @brief Add a entity to the same componet array
    /// @param id
    /// @param componentType 
    void AddEntityToArray(Entity entity, T componentType){
        
        assert(m_Entity_Index_Map.find(entity) == m_Entity_Index_Map.end()
                && "Component added to same entity more than once.");

        size_t newIndex = m_CurrentSize;

        m_Entity_Index_Map[entity] = newIndex;
        m_Index_Entity_Map[newIndex] = entity;
        m_ComponentArray[newIndex] = componentType;

        // cout << "ComponentArray AddComponentToArray " << endl;
        // cout << "m_CurrentSize " << m_CurrentSize << endl;
        // cout << "componentType" << componentType;

        m_CurrentSize++;
    }

    void RemoveEntityFromArray(Entity entity){

        assert(m_Entity_Index_Map.find(entity) != m_Entity_Index_Map.end()
                && "Removing non-existent component.");

        // STEP1:
        // to maintain a good array,
        // 0 1 2 3 4 say we want to remove 2
        // copy final to 2: 0 1 4 3 4

        size_t indexOfRemovedID = m_Entity_Index_Map[entity];
        size_t indexOfLastIndex = m_CurrentSize - 1;
        m_ComponentArray[indexOfRemovedID] = m_ComponentArray[indexOfLastIndex];

        // STEP2:
        // then we just need to switch reference in two maps

        // get the object ID of last element index,
        // then set map to the place where we want to delete
        Entity idOfLastElement = m_Index_Entity_Map[indexOfLastIndex];
        m_Index_Entity_Map[idOfLastElement] = indexOfRemovedID;
        m_Entity_Index_Map[indexOfRemovedID] = idOfLastElement;

        m_Entity_Index_Map.erase(entity);
        m_Index_Entity_Map.erase(idOfLastElement);

        m_CurrentSize--;
    }

    T& GetComponentData(Entity entity){
        assert(m_Entity_Index_Map.find(entity) != m_Entity_Index_Map.end()
                && "[ComponentArray.GetComponentData] Retrieving non-existent component.");
        
        // ID is in pair with {0-MAX_GameObjectCount}
        // so we use ID to find the pair, and use pair to find the position in m_ComponentArray
        return m_ComponentArray[m_Entity_Index_Map[entity]];
    }

    bool HasComponent(Entity entity){
        if(m_Entity_Index_Map.find(entity) != m_Entity_Index_Map.end()){
            return true;
        }
        return false;
    }

private:

    /// @brief array stores a component related to an ID from {0 - MAX_GameObject_Count}
    array<T, MAX_EntityCount>           m_ComponentArray {};

    /// @brief Bidirectional Map for ID and index: ID <---> Index
    unordered_map<Entity, size_t>       m_Entity_Index_Map {};
    
    /// @brief Index <---> ID
    unordered_map<size_t, Entity>       m_Index_Entity_Map {};

    size_t                              m_CurrentSize {};

};