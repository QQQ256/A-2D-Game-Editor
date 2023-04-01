#pragma once

#include "Event.hpp"
#include <unordered_map>
#include <list>
#include <functional>
#include <vector>

using namespace std;

class EventManager{
public:
    using EventCallback = function<void(Event& event)>;

    void AddListener(EVENT eventId, const EventCallback& callBack){
        m_EventMap[eventId].push_back(callBack);
    }   

    void RemoveListener(EVENT eventId, const EventCallback& callBack){
        auto& callBackFuncVector = m_EventMap[eventId];
        for (auto iterator = callBackFuncVector.begin(); iterator != callBackFuncVector.end(); ++iterator)
        {
            if (iterator->target_type() == callBack.target_type())
            {
                callBackFuncVector.erase(iterator);
                break;
            }
        }
    }

    void Trigger(EVENT id){
        Event event(id);

        // TODO: 不懂
        for(auto const& callBack : m_EventMap[id]){
            callBack(event);
        }
    }

    void Trigger(Event& event){
        auto eventId = event.GetEventID();

        for(auto const& callBack : m_EventMap[eventId]){
            callBack(event);
        }
    }

private:
    unordered_map<EVENT, vector<EventCallback>> m_EventMap = {};
};