#pragma once

#include "State.h"

class MainMenu : public State
{
public:
	void OnInit() override;

	void OnUpdate(const float dt) override;
	void OnDraw(const float dt) override;
private:

};