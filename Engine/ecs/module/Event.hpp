#pragma once

#include "Common.hpp"
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

class Event{
public:
    Event() = delete;

    // explicit 是一个 C++ 中的关键字，
    // 用于指定只有显示调用的构造函数才能用于类型转换。
    explicit Event(EVENT eventType) : m_Event(eventType) {

    }

    EVENT GetEventID() const {
        return m_Event;
    }

    template<typename T>
    void SetParameter(const string& key, const T& value){
        m_EventMap[key] = make_shared<T>(value);
        // m_EventMap[id] = value;
    }

    template <typename T>
    T GetParameter(const string &key) const
    {
        auto it = m_EventMap.find(key);
        if (it == m_EventMap.end())
        {
            std::cerr << "Key not found: " << key << std::endl;
        }
        assert(it != m_EventMap.end());

        return *static_cast<T *>(it->second.get());
    }

    /// @brief convert enum event id to string

    string EventIDToString(EVENT id) const{
        return std::to_string(static_cast<int>(id));
    }

private:
    EVENT                                   m_Event     = {};
    // unordered_map<EventID, any> m_EventMap  = {};
    unordered_map<string, shared_ptr<void>> m_EventMap  = {};
};