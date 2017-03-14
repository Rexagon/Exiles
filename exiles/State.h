#pragma once

class State
{
public:
	State() {}
	virtual ~State() {}

	virtual void OnInit() {}

	virtual void OnUpdate(const float dt) {}
	virtual void OnDraw(const float dt) {}

	virtual void OnResize() {}
	virtual void OnFocusGained() {}
	virtual void OnFocusLost() {}

	virtual void OnClose() {}
};