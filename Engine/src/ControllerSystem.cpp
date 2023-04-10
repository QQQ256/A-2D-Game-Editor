#include <assert.h>

#include "ECSCoordinator.hpp"
#include "Engine.hpp"

extern ECSCoordinator coordinator;

void ControllerSystem::Init()
{

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_A, [this](const Event& event){
        OnKeyboardClicked_A(event);
    });

    coordinator.AddEventListener(EVENT::EVENT_ON_KEYBOARD_CLICKED_D, [this](const Event& event){
        OnKeyboardClicked_D(event);
    });
}

void ControllerSystem::Update()
{
    Controlling::horizontalInput = 0;
    Controlling::verticalInput = 0;
}

void ControllerSystem::OnKeyboardClicked_A(const Event &event)
{
    if (coordinator.m_State == GAME_STATE::GAME)
    {
        Controlling::horizontalInput = -1;
    }
}

void ControllerSystem::OnKeyboardClicked_D(const Event &event)
{
    if(coordinator.m_State == GAME_STATE::GAME)
    {
        Controlling::horizontalInput = 1;    
    }
}

void ControllerSystem::OnKeyboardClicked_W(const Event &event)
{
    if(coordinator.m_State == GAME_STATE::GAME)
    {
        Controlling::verticalInput = 1;    
    }
}

void ControllerSystem::OnKeyboardClicked_S(const Event &event)
{
    if(coordinator.m_State == GAME_STATE::GAME)
    {
        Controlling::verticalInput = -1;    
    }
}
