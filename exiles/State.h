#pragma once

class State
{
public:
	State() {}
	virtual ~State() {}

	// Вызывается при создании сцены (добавлении её в стэк)
	virtual void OnInit() {}

	// Вызывается каждый кадр
	virtual void OnUpdate(const float dt) {}

	// Вызывается после OnUpdate и чистки экрана
	virtual void OnDraw(const float dt) {}

	// Вызывается при изменении размеров экрана
	virtual void OnResize() {}

	// Вызывается при переключении на окно игры
	virtual void OnFocusGained() {}

	// Вызывается при переключении на другое окно
	virtual void OnFocusLost() {}

	// Вызывается при удалении сцены
	virtual void OnClose() {}
};