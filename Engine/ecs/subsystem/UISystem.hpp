#pragma once
#include "System.hpp"
#include "Event.hpp"
#include "UIButton.hpp"

using namespace std;

class UISystem : public ISystem{
public:
	void Init() override;

	void Update() override;

	// UIButton CreateUIButton(int x, int y, int w, int h);
};