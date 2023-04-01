#include <assert.h>

#include "ECSCoordinator.hpp"
#include "Engine.hpp"

extern ECSCoordinator coordinator;

void PlayerControllerSystem::Init(){
    coordinator.AddEventListener(EVENT::EVENT_TEST_NO_PARAM, [this](const Event& event){
        OnEventTest_NO_PARAM(event);
    });

    std::cout << "Init PlayerControllerSystem" << std::endl;
}

void PlayerControllerSystem::Update(){

    for(auto& entity : m_Entities){
    
    }
}

void PlayerControllerSystem::OnEventTest_NO_PARAM(const Event& event){

    
    Debug::PrintMessage("PlayerControllerSystem::OnEventTest");
}