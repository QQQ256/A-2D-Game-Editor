#pragma once

#include "System.hpp"
#include "Event.hpp"

class PlayerControllerSystem : public ISystem
{
public:
	void Init() override;

	void Update() override;

	void OnEventTest_NO_PARAM(const Event& event);
};
