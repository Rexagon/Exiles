#include "Core.h"

#include <SDL2\SDL_timer.h>

#include "Window.h"

std::stack<std::unique_ptr<State>> Core::m_states;
bool Core::m_isRunning = false;

void Core::Run()
{
	m_isRunning = true;
	unsigned long long lastTime = SDL_GetPerformanceCounter();
	while (m_isRunning) {
		Input::Update();

		unsigned long long currentTime = SDL_GetPerformanceCounter();
		float dt = static_cast<float>(currentTime - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		State* currentState;
		if (currentState = PeekState()) {
			currentState->OnUpdate(dt);
		}

		if (currentState = PeekState()) {
			currentState->OnDraw(dt);
		}

		Window::Display();
	}

	AssetManager::Clear();
}

void Core::Stop()
{
	m_isRunning = false;
	while (!m_states.empty()) {
		PopState();
	}
}

void Core::PopState()
{
	if (!m_states.empty()) {
		m_states.top()->OnClose();
		m_states.pop();
	}
}

State * Core::PeekState()
{
	if (!m_states.empty()) {
		return m_states.top().get();
	}
	else {
		Stop();
		return nullptr;
	}
}
