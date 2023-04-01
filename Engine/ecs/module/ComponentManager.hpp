#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <typeindex>
#include <assert.h>

#include "ComponentArray.hpp"

using namespace std;

class ComponentManager{
public:
    template<typename T>
    void RegisterComponent(){
        const char* componentName = typeid(T).name();
        assert(m_component_array_map.find(componentName) == m_component_array_map.end());

        // 1. componentName <---> component ID, componentName <---> ComponentArray pointer
        m_component_type_map[componentName] = componentType++;
        m_component_array_map.insert(make_pair(componentName, make_shared<ComponentArray<T>>()));

        cout << "m_component_type_map key, value are:" << endl;
        for(auto iter = m_component_type_map.begin(); iter != m_component_type_map.end(); iter++){
            cout << "Key: " << iter->first << ", Value: " << iter->second << endl;
        }

        cout << "m_component_array_map key, value are:" << endl;
        for(auto iter = m_component_array_map.begin(); iter != m_component_array_map.end(); iter++){
            cout << "Key: " << iter->first << ", Value: " << iter->second << endl;
        }

        // componentType++;
    }

    template<typename T>
    ComponentType GetComponentTypeUniqueIndex(){
        const char* componentName = typeid(T).name();
        // type_index type = typeid(T);
        assert(m_component_type_map.find(componentName) != m_component_type_map.end());

        return m_component_type_map[componentName];
    }

    template<typename T>
    void AddComponent(Entity id, T Component){
        GetComponentArray<T>()->AddEntityToArray(id, Component);
    }

    template<typename T>
    void RemoveComponent(Entity id){
        GetComponentArray<T>()->RemoveEntityFromArray(id);
    }

    void DestroyEntity(Entity entity){
        // for all components related to this object, call ElimiateEntity
        for(auto & iter : m_component_array_map){
            auto & component = iter.second;
            component->ElimiateEntity(entity);
        } 
    }

    template<typename T>
    T& GetComponent(Entity entity){
        return GetComponentArray<T>()->GetComponentData(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity){
        return GetComponentArray<T>()->HasComponent(entity);
    }

private:
    /// @brief A component name ---> a ComponentArray pointer, then add pointer to component array map
    // 一个组件的名称对应一个组件数组，例如所有的Transform组件都被存在ComponentArray<Transform>这个模板数组中
    // 所以每个组件对应一个指向这个ComponentArray<Transform>的智能指针
    map<const char*, shared_ptr<IComponentArray>>       m_component_array_map;  

    /// @brief A component name ---> A component's ID
    map<const char*, ComponentType>                     m_component_type_map;

    ComponentType componentType {};

    template<typename T>
    shared_ptr<ComponentArray<T>> GetComponentArray(){
        const char* componentName = typeid(T).name();
        
        // if we do not find the componentName in m_component_type_map,
        // it means that the component is not registered
        assert(m_component_type_map.find(componentName) != m_component_type_map.end()
                && "Component is not registered here!");

        // use static_pointer_cast to convert IComponentArray to ComponentArray
        return static_pointer_cast<ComponentArray<T>>(m_component_array_map[componentName]);
    }
};